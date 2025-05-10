#include "loginwidget.hpp"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupStyles();
}

void LoginWidget::setupUI() {
    QVBoxLayout *loginLayout = new QVBoxLayout(this);
    loginLayout->setAlignment(Qt::AlignCenter);
    
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    backButton_ = new QPushButton("←", this);
    topLayout->addWidget(backButton_);
    topLayout->addStretch();

    QWidget *centerWidget = new QWidget(this);
    QVBoxLayout *centerLayout = new QVBoxLayout(centerWidget);
    centerLayout->setAlignment(Qt::AlignCenter);
    
    usernameEdit_ = new QLineEdit(this);
    usernameEdit_->setPlaceholderText("Login");
    passwordEdit_ = new QLineEdit(this);
    passwordEdit_->setPlaceholderText("Password");
    passwordEdit_->setEchoMode(QLineEdit::Password);
    loginButton_ = new QPushButton("Log in", this);

    centerLayout->addWidget(usernameEdit_);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(passwordEdit_);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(loginButton_);

    loginLayout->addLayout(topLayout);
    loginLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    loginLayout->addWidget(centerWidget, 0, Qt::AlignCenter);
    loginLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    // Сигналы
    connect(backButton_, &QPushButton::clicked, this, [this]() {
        emit backRequested();
    });

    connect(loginButton_, &QPushButton::clicked, this, [this]() {
        emit loginAttempt(usernameEdit_->text(), passwordEdit_->text());
    });
}


void LoginWidget::setupStyles() {
    // Установка стилей для элементов
    setStyleSheet(R"(
        QWidget {
            background-color: rgb(43, 41, 46);
            font-family: Arial;
        }
        QLineEdit {
            min-width: 200px;
            max-width: 200px;
            color: white;
            background-color: rgb(96, 81, 119);
            padding: 12px;
            border: 8px;
            border-radius: 6px;
            font-size: 20px;
        }
        QPushButton {
            min-width: 200px;
            max-width: 200px;
            color: white;
            background-color: rgb(143, 121, 177);
            border: 8px;
            padding: 12px;
            border-radius: 6px;
            font-size: 20px;
        }
        QPushButton:hover {
            background-color: rgb(96, 81, 119);
        }
        QPushButton#back {
            min-width: 30px;
            max-width: 30px;
            min-height: 30px;
            max-height: 30px;
            padding: 10px;
            color: white;
            background: transparent;
            border: none;
            border-radius: 14px;
            font-size: 24px;
        }
        QPushButton#back:hover {
            background-color: rgba(96, 81, 119, 0.8);
        }
    )");
    backButton_->setObjectName("back");
    
    // Дополнительные эффекты
    loginButton_->setCursor(Qt::PointingHandCursor);
}

