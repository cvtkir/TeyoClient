#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>
#include <memory>
#include <string>
#include <QObject>
#include <iostream>


namespace net = boost::asio; // from <boost/asio.hpp>
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
using json = nlohmann::json; // from <nlohmann/json.hpp>

class Session : public QObject{
    Q_OBJECT
public:
    // static Session& instance(net::io_context& ioc);
    static Session& instance(); 

    void connect(const std::string& host, const std::string& port);
    bool isConnected();
	void set_user_id(int userId) { userId_ = userId; }

    void doWrite(const json& j);
    void startListen();


signals:
    void connectionEstablished();
    void connectionFailed(const QString& error);

    // void messageReceived(const QString& msg);

    void loginResult(const json& j);
    void signupResult(const json& j);
    void authFailed(const json& j);


private:
    Session(QObject* parent = nullptr);
    ~Session();
    void run_ioc();

    void readNextMessage();
    void processMessage(const std::string& msg);

    void writeToken(const std::string& token);
    // void onConnect(beast::error_code& ec);
    // void onRead(beast::error_code& ec, std::size_t bytes_read); 

    net::io_context ioc_;
    net::executor_work_guard<net::io_context::executor_type> work_;
    std::thread ioc_thread_;
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::string host_;
    std::string port_;
    bool connected_ = false;
    int userId_ = -1;
};

#endif