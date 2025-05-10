#ifndef SIGNUPWIDGET_HPP
#define SIGNUPWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>

class SignupWidget : public QWidget {
    Q_OBJECT

public:
    explicit SignupWidget(QWidget *parent = nullptr);
    
signals:
    void signupAttempt(const QString &username, const QString &password);
    void backRequested();

private:
    QLineEdit *usernameEdit_;
    QLineEdit *passwordEdit_;
    QLineEdit *passconfEdit_;
    QPushButton *signupButton_;
    QPushButton *backButton_;

    void setupUI();
    void setupStyles();


// private slots:
    // void handleSignup();


};

#endif 