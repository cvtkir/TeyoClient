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
    m_backButton = new QPushButton("←", this);
    topLayout->addWidget(m_backButton);
    topLayout->addStretch();

    QWidget *centerWidget = new QWidget(this);
    QVBoxLayout *centerLayout = new QVBoxLayout(centerWidget);
    centerLayout->setAlignment(Qt::AlignCenter);
    
    m_usernameEdit = new QLineEdit(this);
    m_usernameEdit->setPlaceholderText("Login");
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setPlaceholderText("Password");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_passconfEdit = new QLineEdit(this);
    m_passconfEdit->setPlaceholderText("Confirm Password");
    m_passconfEdit->setEchoMode(QLineEdit::Password);
    m_signupButton = new QPushButton("Sign up", this);

    centerLayout->addWidget(m_usernameEdit);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(m_passwordEdit);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(m_passconfEdit);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(m_signupButton);

    signupLayout->addLayout(topLayout);
    signupLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    signupLayout->addWidget(centerWidget);
    signupLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    connect(m_signupButton, &QPushButton::clicked, this, [this]() {
        emit signupAttempt(m_usernameEdit->text(), m_passwordEdit->text());
    });
    connect(m_backButton, &QPushButton::clicked, this, [this]() {
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
    m_backButton->setObjectName("back");
    
    // Дополнительные эффекты
    m_signupButton->setCursor(Qt::PointingHandCursor);
}