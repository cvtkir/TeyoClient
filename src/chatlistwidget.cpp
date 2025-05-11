#include "chatlistwidget.hpp"
#include <QVBoxLayout>
#include <QVector>

ChatListWidget::ChatListWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    searchBar_ = new QLineEdit();
    searchBar_->setPlaceholderText("Search...");
    
    chatList_ = new QListWidget(this);

    Chat testchat;
    QListWidgetItem *item = new QListWidgetItem(testchat.title);
    item->setData(Qt::UserRole, QVariant::fromValue(testchat));

    chatList_->addItem(item);

    layout->addWidget(searchBar_);
    layout->addWidget(chatList_);

    connect(chatList_, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        Chat chat = item->data(Qt::UserRole).value<Chat>();
        emit chatSelected(chat);
        // qDebug() << "selected chat:" << item->text();
        chat.Print();
    });
}

// add setupstyles with setStyleSheet
