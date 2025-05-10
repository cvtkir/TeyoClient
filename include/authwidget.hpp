#ifndef AUTHWIDGET_HPP
#define AUTHWIDGET_HPP

#include "startwidget.hpp"
#include "loginwidget.hpp"
#include "signupwidget.hpp"
#include "session.hpp"
#include <QStackedWidget>
#include <QMessageBox>
#include <nlohmann/json.hpp>

using json = nlohmann::json; // from <nlohmann/json.hpp>


class AuthWidget : public QWidget {
    Q_OBJECT
public:
    explicit AuthWidget(QWidget *parent = nullptr);


private:
    QStackedWidget *authStack_;
    StartWidget *startWidget_;
    LoginWidget *loginWidget_;
    SignupWidget *signupWidget_;


};

#endif