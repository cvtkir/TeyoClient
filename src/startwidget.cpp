#include "startwidget.hpp"

StartWidget::StartWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupStyles();
}

void StartWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Title
    titleLabel_ = new QLabel("Teyo", this);
    titleLabel_->setAlignment(Qt::AlignCenter);

    // Subtitle
    subtitleLabel_ = new QLabel("Welcome to Teyo desktop app", this);
    subtitleLabel_->setAlignment(Qt::AlignCenter);

    // Buttons
    loginButton_ = new QPushButton("Log in", this);
    signupButton_ = new QPushButton("Sign up", this);

    //button layout
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(loginButton_);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(signupButton_);

    // Add widgets to layout
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(titleLabel_);
    mainLayout->addWidget(subtitleLabel_);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    
    // Connect signals
    connect(loginButton_, &QPushButton::clicked, this, &StartWidget::loginRequested);
    connect(signupButton_, &QPushButton::clicked, this, &StartWidget::signupRequested);
}



void StartWidget::setupStyles() {
    setStyleSheet(R"(
        QWidget {
            background-color: rgb(43, 41, 46);
            font-family: Arial;
        }
        QLabel#title {
            font-size: 40px;
            font-weight: bold;
            color:rgb(230, 230, 230);
        }
        QLabel#subtitle {
            font-size: 20px;
            color:rgb(200, 200, 200);
        }
        QPushButton {
            min-width: 200px;
            max-width: 200px;
            font-size: 20px;
            padding: 12px;
            border: 8px;
            border-radius: 6px;
            background-color: rgb(143, 121, 177);
            color: white;
        }
        QPushButton:hover {
            background-color: rgb(96, 81, 119);
        }
        )");


    // separate style for buttons
    // QPushButton#login {
    //     background-color: rgb(143, 121, 177);
    //     color: white;
    // }
    // QPushButton#login:hover {
    //     background-color: rgb(96, 81, 119);
    // }
    // QPushButton#signup {
    //     background-color: rgb(143, 121, 177);
    //     color: white;
    // }
    // QPushButton#signup:hover {
    //     background-color: rgb(96, 81, 119);
    // }


    // Apply object names for specific styling
    titleLabel_->setObjectName("title");
    subtitleLabel_->setObjectName("subtitle");
    loginButton_->setObjectName("login");
    signupButton_->setObjectName("signup");

    // Cursors
    loginButton_->setCursor(Qt::PointingHandCursor);
    signupButton_->setCursor(Qt::PointingHandCursor);
}