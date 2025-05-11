#include "session.hpp"
#include <iostream>
#include <fstream>
#include <QDebug>

Session::Session(QObject* parent)
    : QObject(parent),
    work_(net::make_work_guard(ioc_)),
    ws_(net::make_strand(ioc_)) 
    {
        ioc_thread_ = std::thread([this]() {
            try {
                ioc_.run();
            } catch (const std::exception& e) {
                qDebug() << "Error in IO context thread:" << e.what();
            }
        });
    }


Session::~Session() {
    if (connected_) {
        beast::error_code ec;
        ws_.close(websocket::close_code::normal, ec);
        work_.reset();
        ioc_.stop();
        if (ioc_thread_.joinable()) {
            ioc_thread_.join();
        }
    }
}


Session& Session::instance() {
    static Session instance;
    return instance;
}


void Session::connect(const std::string& host, const std::string& port) {
    host_ = host;
    port_ = port;
    // Resolve the host and port
    net::ip::tcp::resolver resolver(ioc_);
    auto endpoints = resolver.resolve(host_, port_);

    beast::get_lowest_layer(ws_).async_connect(
        endpoints,
        [this](beast::error_code ec, net::ip::tcp::endpoint) {
            if (ec) {
                qDebug() << "Connection error:" << ec.message().c_str();
                emit connectionFailed(QString::fromStdString(ec.message()));
                return;
            }
            ws_.async_handshake(host_, "/",
                [this](beast::error_code ec) {
                    if (ec) {
                        qDebug() << "Handshake error:" << ec.message().c_str();
                        emit connectionFailed(QString::fromStdString(ec.message()));
                        return;
                    }
                    connected_ = true;
                    qDebug() << "connected_ = true";
                    emit connectionEstablished();
                });
        });
}

bool Session::isConnected() {
    return connected_;
}

void Session::writeToken(const std::string& token) {
    json j;
    j["token"] = token;
    std::ofstream file("token.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        qDebug() << "Token written to token.json";
    } else {
        qDebug() << "Failed to open token.json for writing";
    }
} 



void Session::doWrite(const json& j) {
    if (!isConnected()) {
        qDebug() << "Not connected, cannot send message";
        return;
    }
    try{
        // qDebug() << "in doWrite";
        std::string message = j.dump();
        // qDebug() << message;
        ws_.async_write(
            net::buffer(message),
            [this](beast::error_code ec, std::size_t) {
                if (ec) {
                    // qDebug() << "Write error:" << ec.message().c_str();
                    qDebug() << "Write error:";
                    connected_ = false;
                    emit connectionFailed(QString::fromStdString(ec.message()));
                } else {
                    qDebug() << "Message sent successfully";
                }
            });
        }
    catch (const std::exception& e) {
        qDebug() << "Exception during write:" << e.what();
        // connected_ = false;
        // emit connectionFailed(QString::fromStdString(e.what()));
    }
}


void Session::startListen() {
    if (ws_.is_open()) {
        readNextMessage();
    } 
}


void Session::readNextMessage() {
    ws_.async_read(
        buffer_,
        [this](beast::error_code ec, std::size_t bytes_read) {
            if (ec) {
                qDebug() << "Read error:" << ec.message().c_str();
                // connected_ = false;
                emit connectionFailed(QString::fromStdString(ec.message()));
                return;
            }
            std::string message(beast::buffers_to_string(buffer_.data()));
            buffer_.consume(bytes_read);

            // emit messageReceived(QString::fromStdString(message));
            processMessage(message);
            if (ws_.is_open()) {
                readNextMessage(); // Continue reading messages
            }
        }
    );
}    


void Session::processMessage(const std::string& msg) {
    try {
        json j = json::parse(msg);
        std::string type = j.value("type", "");
        if (type == "login_success") {
            writeToken(j.value("token", ""));
            emit loginResult(j);
        } else if (type == "signup_success") {
            emit signupResult(j);
        } else if (type == "auth_failed") {
            emit authFailed(j);       

        } else if (type == "direct") {
            // Handle direct message
        } else if (type == "group") {
            // Handle group message
        } else if (type == "sync") {
            // Handle sync
        }
    }
    catch (const json::parse_error& e) {
        qDebug() << "Parse error:" << e.what();
    }
}

