#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Teyo");
    resize(800, 600);
    loginWidget = new LoginWidget(this);
    setCentralWidget(loginWidget);


    // Можно подключить сигнал loginAttempt для обработки входа
    connect(loginWidget, &LoginWidget::loginAttempt, [](const QString &user, const QString &pass) {
        qDebug() << "Login attempt:" << user << pass;
        // Здесь можно добавить логику проверки логина/пароля
    });
}