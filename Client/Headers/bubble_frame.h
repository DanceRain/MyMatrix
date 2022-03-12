#ifndef BUBBLE_FRAME_H
#define BUBBLE_FRAME_H

#include <QFrame>
#include "Headers/chat_role.h"
#include <QHBoxLayout>

class BubbleFrame : public QFrame
{
    Q_OBJECT
public:
    BubbleFrame(ChatRole role, QWidget *parent = nullptr);
    void setMargin(int margin);
    //inline int margin(){return margin;}
    void setWidget(QWidget *w);
protected:
    void paintEvent(QPaintEvent *e);
private:
    int      m_margin;
    ChatRole m_role;
    QHBoxLayout *m_pHLayout;
};

#endif
