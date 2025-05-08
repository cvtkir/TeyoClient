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
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QLineEdit *m_passconfEdit;
    QPushButton *m_signupButton;
    QPushButton *m_backButton;

    void setupUI();
    void setupStyles();


// private slots:
    // void handleSignup();


};

#endif 