#include "authwidget.hpp"

AuthWidget::AuthWidget(QWidget *parent) : QWidget(parent) {
    authStack_ = new QStackedWidget(this);
    startWidget_ = new StartWidget(this);
    loginWidget_ = new LoginWidget(this);
    signupWidget_ = new SignupWidget(this);

    authStack_->addWidget(startWidget_);
    authStack_->addWidget(loginWidget_);
    authStack_->addWidget(signupWidget_);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(authStack_);
    setLayout(mainLayout);

    connect(startWidget_, &StartWidget::loginRequested, [this]() {
        authStack_->setCurrentWidget(loginWidget_);
    });

    connect(startWidget_, &StartWidget::signupRequested, [this]() {
        authStack_->setCurrentWidget(signupWidget_);
    });

    connect(loginWidget_, &LoginWidget::backRequested, [this]() {
        authStack_->setCurrentWidget(startWidget_);
    });

    connect(signupWidget_, &SignupWidget::backRequested, [this]() {
        authStack_->setCurrentWidget(startWidget_);
    });

    // loginattempt and signupattempt signals
    connect(loginWidget_, &LoginWidget::loginAttempt, 
        [](const QString &user, const QString &pass){
            json auth_request = {
                {"type", "login"},
                {"login", user.toStdString()},
                {"password", pass.toStdString()}
            };
            Session::instance().doWrite(auth_request);
        });

    connect(signupWidget_, &SignupWidget::signupAttempt, 
        [this](const QString &user, const QString &pass){
            json auth_request = {
                {"type", "signup"},
                {"login", user.toStdString()},
                {"password", pass.toStdString()}
            };
            Session::instance().doWrite(auth_request);
        });

    // connect login and signup result signals
    connect(&Session::instance(), &Session::signupResult, [this](const json& j) {
        qDebug() << "Signup result:" << j.value("message", "");
        QMetaObject::invokeMethod(this, [this](){
            authStack_->setCurrentWidget(loginWidget_);
        });
    });

    connect(&Session::instance(), &Session::authFailed, [this](const json& j) {
        qDebug() << "Auth failed:" << j.value("message", "");
        // QMessageBox::warning(this, "Error", j.value("message", "").c_str());
    });
}
