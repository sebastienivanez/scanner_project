#include <sendmail.h>
#include <iostream>
using namespace std;

void sendMail(QString email, QString msg_subject, QString msg_body, QString msg_attachement)
{
    //system(("echo " + msg_body + " | mailx -s " + msg_subject + " -a " + msg_attachement + email).c_str());
    cout << "email = " << qPrintable(email) << "msg_subject = " << qPrintable(msg_subject) << "msg_body = " << qPrintable(msg_body) << "msg_attachement" << qPrintable(msg_attachement) << endl;
    system(qPrintable("echo " + msg_body + " | mailx -s " + msg_subject + " -a " + msg_attachement + email));
}
