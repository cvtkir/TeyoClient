#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Teyo");
    resize(800, 600);
    setMinimumSize(800, 600);
    setMaximumSize(1920, 1080);

    QStackedWidget *authWidget = new QStackedWidget(this);
    m_startWidget = new StartWidget(this);
    m_loginWidget = new LoginWidget(this);
    m_signupWidget = new SignupWidget(this);
    authWidget->addWidget(m_startWidget);
    authWidget->addWidget(m_loginWidget);
    authWidget->addWidget(m_signupWidget);
    authWidget->setCurrentWidget(m_startWidget);
    setCentralWidget(authWidget);
    
    // Connect signals
    connect(m_loginWidget, &LoginWidget::loginAttempt, [](const QString &user, const QString &pass){});
    
    connect(m_startWidget, &StartWidget::loginRequested, [authWidget, this](){
        authWidget->setCurrentWidget(m_loginWidget);
    });

    connect(m_loginWidget, &LoginWidget::backRequested, [authWidget, this](){
        authWidget->setCurrentWidget(m_startWidget);
    });

    connect(m_startWidget, &StartWidget::signupRequested, [authWidget, this](){
        authWidget->setCurrentWidget(m_signupWidget);
    });

    connect(m_signupWidget, &SignupWidget::backRequested, [authWidget, this](){
        authWidget->setCurrentWidget(m_startWidget);
    });
}

MainWindow::~MainWindow() {
}

// void MainWindow::showStartWidget() {
//     qDebug() << "showStartWidget";
//     if(m_startWidget) {
//         m_startWidget->show();
//         m_startWidget->setParent(nullptr);
//         setCentralWidget(m_startWidget);
//     }
// }

// void MainWindow::showLoginWidget() {
//     if (m_loginWidget) {
//         m_loginWidget->setParent(nullptr);
//         m_loginWidget->show();
//         setCentralWidget(m_loginWidget);
//     }
// }