#include "loginwidget.hpp"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Login Form", this);
    layout->addWidget(titleLabel);

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Username");
    layout->addWidget(usernameLineEdit);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLineEdit);

    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::handleLogin);
}

void LoginWidget::handleLogin() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    emit loginAttempt(username, password);
}