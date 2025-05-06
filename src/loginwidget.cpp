#include "loginwidget.hpp"

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupStyles();
}

void LoginWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Заголовок с тенью
    QLabel *titleLabel = new QLabel("Вход в систему", this);
    titleLabel->setAlignment(Qt::AlignCenter);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setColor(Qt::darkGray);
    shadow->setOffset(2, 2);
    titleLabel->setGraphicsEffect(shadow);

    // Поля ввода
    m_usernameEdit = new QLineEdit(this);
    m_usernameEdit->setPlaceholderText("Логин");

    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setPlaceholderText("Пароль");
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    // Кнопка
    m_loginButton = new QPushButton("Войти", this);

    // Добавляем элементы в layout
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(m_usernameEdit);
    mainLayout->addWidget(m_passwordEdit);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_loginButton);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Сигналы
    connect(m_loginButton, &QPushButton::clicked, [this]() {
        emit loginAttempt(m_usernameEdit->text(), m_passwordEdit->text());
    });
}


void LoginWidget::setupStyles() {
    // Установка стилей для элементов
    setStyleSheet(R"(
        QWidget {
            background-color: #f5f5f5;
            font-family: Arial;
        }
        QLabel {
            font-size: 20px;
            color: #333;
        }
        QLineEdit {
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
            font-size: 14px;
        }
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px;
            border-radius: 4px;
            font-size: 16px;
        }
        QPushButton:hover {
            background-color: #45a049;
        }
    )");

    // Дополнительные эффекты
    m_loginButton->setCursor(Qt::PointingHandCursor);
}

void LoginWidget::handleLogin() {
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();

    emit loginAttempt(username, password);
}