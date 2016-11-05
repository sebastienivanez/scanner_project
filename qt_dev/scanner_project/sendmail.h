#ifndef SENDMAIL_H
#define SENDMAIL_H

#include <string>
#include <QString>
using namespace std;

void sendMail(QString email, QString msg_subject, QString msg_body, QString msg_attachement);

#endif // SENDMAIL_H
