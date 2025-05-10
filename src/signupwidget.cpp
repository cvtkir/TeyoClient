#include "signupwidget.hpp"

SignupWidget::SignupWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupStyles();
}

void SignupWidget::setupUI() {
    QVBoxLayout *signupLayout = new QVBoxLayout(this);
    signupLayout->setAlignment(Qt::AlignCenter);
    
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
    passconfEdit_ = new QLineEdit(this);
    passconfEdit_->setPlaceholderText("Confirm Password");
    passconfEdit_->setEchoMode(QLineEdit::Password);
    signupButton_ = new QPushButton("Sign up", this);

    centerLayout->addWidget(usernameEdit_);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(passwordEdit_);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(passconfEdit_);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(signupButton_);

    signupLayout->addLayout(topLayout);
    signupLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    signupLayout->addWidget(centerWidget);
    signupLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    connect(signupButton_, &QPushButton::clicked, this, [this]() {
        emit signupAttempt(usernameEdit_->text(), passwordEdit_->text());
    });
    connect(backButton_, &QPushButton::clicked, this, [this]() {
        emit backRequested();
    });
}


void SignupWidget::setupStyles() {
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
    signupButton_->setCursor(Qt::PointingHandCursor);
}