#ifndef LOCAL_MSG_H
#define LOCAL_MSG_H

#include <QString>

class LocalMsg
{
public:
    explicit LocalMsg(int _msg_id, int _msg_type, int _msg_ros, const QString& _msg_content):
        msg_id(_msg_id),
        msg_type(_msg_type),
        msg_ros(_msg_ros),
        msg_content(_msg_content)
    {

    }

    int getMsgId() const
    {
        return msg_id;
    }

    int getMsgType() const
    {
        return msg_type;
    }

    int getMsgRos() const
    {
        return msg_ros;
    }

    QString getMsgContent() const
    {
        return msg_content;
    }

private:
    int msg_id;
    int msg_type;
    int msg_ros;
    QString msg_content;
};


#endif // LOCAL_MSG_H


