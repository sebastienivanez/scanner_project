#ifndef SENDMAIL_H
#define SENDMAIL_H

void sendMail(string email, string msg_subject, string msg_body, string msg_attachement)
{
    system(("echo " + msg_body + " | mailx -s " + msg_subject + " -a " + msg_attachement + email).c_str());
}
#endif // SENDMAIL_H
