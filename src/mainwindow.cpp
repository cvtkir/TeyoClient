#include "mainwindow.hpp"
#include "session.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto& session = Session::instance();
    connect(&session, &Session::connectionEstablished, [&session]() {
        session.startListen();
    });

    setWindowTitle("Teyo");
    resize(800, 600);
    setMinimumSize(800, 600);
    setMaximumSize(1920, 1080);

    QStackedWidget *mainWidget = new QStackedWidget(this);
    authWidget_ = new AuthWidget(this);
    
    mainWidget->addWidget(authWidget_);
    mainWidget->setCurrentWidget(authWidget_);
    setCentralWidget(mainWidget);
    


    connect(&session, &Session::loginResult, [this](const json& j) {
        qDebug() << "Login result:" << j.value("message", "");
        QMetaObject::invokeMethod(this, [this](){
            // mainWidget->setCurrentWidget(chatWidget_);
        });
    });

    // Разобраться во всех сигналах и слотах
    // Разобраться с чтением сообщений от сервера
}

MainWindow::~MainWindow() {
}
