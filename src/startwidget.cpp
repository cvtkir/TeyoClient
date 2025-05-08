#include "startwidget.hpp"

StartWidget::StartWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupStyles();
}

void StartWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // Title
    m_titleLabel = new QLabel("Teyo", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);

    // Subtitle
    m_subtitleLabel = new QLabel("Welcome to Teyo desktop app", this);
    m_subtitleLabel->setAlignment(Qt::AlignCenter);

    // Buttons
    m_loginButton = new QPushButton("Log in", this);
    m_signupButton = new QPushButton("Sign up", this);

    //button layout
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(m_loginButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(m_signupButton);

    // Add widgets to layout
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addWidget(m_subtitleLabel);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    
    // Connect signals
    connect(m_loginButton, &QPushButton::clicked, this, &StartWidget::loginRequested);
    connect(m_signupButton, &QPushButton::clicked, this, &StartWidget::signupRequested);
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
    m_titleLabel->setObjectName("title");
    m_subtitleLabel->setObjectName("subtitle");
    m_loginButton->setObjectName("login");
    m_signupButton->setObjectName("signup");

    // Cursors
    m_loginButton->setCursor(Qt::PointingHandCursor);
    m_signupButton->setCursor(Qt::PointingHandCursor);
}