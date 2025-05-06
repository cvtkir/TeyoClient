#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class LoginWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    
private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;

signals:
    void loginAttempt(const QString &username, const QString &password);

private slots:
    void handleLogin();


};

#endif 