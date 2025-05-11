#include "chatwidget.hpp"
#include <QVBoxLayout>
#include "session.hpp"



ChatWidget::ChatWidget(QWidget *parent) : QWidget(parent) {
    auto& session = Session::instance();
    splitter_ = new QSplitter(Qt::Horizontal, this);  
    chatList_ = new ChatListWidget();
    messageArea_ = new MessageWidget(this);

    splitter_->addWidget(chatList_);
    splitter_->addWidget(messageArea_);
    splitter_->setStretchFactor(1, 3);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter_);

    connect(chatList_, &ChatListWidget::chatSelected, messageArea_, &MessageWidget::setCurrentChat);
    
    // переделать передавая сюда json
    connect(messageArea_, &MessageWidget::msgSend, [](const QString &text) {
        json message = {
            {"type", "login"},
            {"login", text.toStdString()}
        };
        Session::instance().doWrite(message);
        qDebug() << "Message sent:" << text;
    });
}
