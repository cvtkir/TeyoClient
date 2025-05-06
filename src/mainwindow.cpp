#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_loginWidget = new LoginWidget(this);
    setCentralWidget(m_loginWidget);
    
    setWindowTitle("Teyo");
    resize(800, 600);

    // Можно подключить сигнал loginAttempt для обработки входа
    connect(m_loginWidget, &LoginWidget::loginAttempt, [](const QString &user, const QString &pass) {
        qDebug() << "Login attempt:" << user << pass;
        // Здесь можно добавить логику проверки логина/пароля
    });
}