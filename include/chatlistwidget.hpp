
#ifndef CHATLISTWIDGET_HPP
#define CHATLISTWIDGET_HPP

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>


class ChatListWidget : public QWidget {
    Q_OBJECT
public:
    ChatListWidget(QWidget *parent = nullptr);

    struct Chat {
        int id = 1;
        QString title = "test";
        QString type = "direct";
        QVector<int> members;
        void Print() const {
            qDebug() << "Chat ID:" << id << "Title:" << title << "Type:" << type;
        }
    };

signals:
    void chatSelected(const Chat& testchat);

private:
    // void setupChatList(const json& chats);
    QListWidget *chatList_;
    QLineEdit *searchBar_;
};

#endif // CHATLISTWIDGET_HPP