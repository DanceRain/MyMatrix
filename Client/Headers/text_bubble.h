#ifndef TEXT_BUBBLE_H
#define TEXT_BUBBLE_H

#include <QTextEdit>
#include "bubble_frame.h"
#include <QHBoxLayout>

class TextBubble : public BubbleFrame
{
    Q_OBJECT
public:
    TextBubble(ChatRole role, const QString &text, QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *o, QEvent *e);
private:
    void adjustTextHeight();
    void setPlainText(const QString &text);
    void initStyleSheet();
private:
    QTextEdit *m_pTextEdit;
};

#endif // TEXT_BUBBLE_H
