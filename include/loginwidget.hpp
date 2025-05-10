#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    
signals:
    void loginAttempt(const QString &username, const QString &password);
    void backRequested();

private:
    QLineEdit *usernameEdit_;
    QLineEdit *passwordEdit_;
    QPushButton *loginButton_;
    QPushButton *backButton_;

    void setupUI();
    void setupStyles();


// private slots:
//     void handleLogin();


};

#endif 