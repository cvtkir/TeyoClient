#include <QApplication>
#include <QDebug>
#include <iostream>
#include "mainwindow.hpp"
#include "session.hpp"

const std::string host = "192.168.0.107";
const std::string port = "42001";
const std::string target = "/";


int main(int argc, char *argv[]) {
    try{
        QApplication a(argc, argv);
        QApplication::setStyle("Fusion");
        a.setStyleSheet(R"(
            QWidget {
                background-color:rgb(43, 41, 46);
            }
        )");
        
        // net::io_context ioc;
        // std::thread t([&ioc](){
        //     net::executor_work_guard<net::io_context::executor_type> work =
        //         net::make_work_guard(ioc);
        //     ioc.run();
        // });
        auto& session = Session::instance();
        session.connect(host, port);
        
        // if (!session.isConnected()) {
        //     std::cerr << "Failed to connect to server." << std::endl;
        //     return 1;
        // }

        MainWindow mainWindow;
        mainWindow.show();

        int result = a.exec();
        // ioc.stop();
        // if (t.joinable()) {
        //     t.join();
        // }

        return result;
    } catch (const std::exception& e) {
        std::cerr << "Fatal: " << e.what() << std::endl;
    }
}