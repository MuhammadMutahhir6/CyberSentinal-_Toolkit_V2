#include "loginwidget.h"
#include <QVBoxLayout>

LoginWidget::LoginWidget(QWidget *parent) : ToolBase(parent)
{
    auto lay = new QVBoxLayout(this);
    pwdEdit = new QLineEdit;  pwdEdit->setEchoMode(QLineEdit::Password);
    btn     = new QPushButton("Login");
    status  = new QLabel("Enter password");

    lay->addWidget(pwdEdit); lay->addWidget(btn); lay->addWidget(status); lay->addStretch();

    connect(btn,&QPushButton::clicked,this,&LoginWidget::tryLogin);
    connect(&lockTimer,&QTimer::timeout,this,&LoginWidget::tickLockout);
}

void LoginWidget::tryLogin()
{
    if (pwdEdit->text() == correct)
    {
        status->setText("<font color='green'>Login successful!</font>");
        attempts = 0;
        emit loginSucceeded();
    }
    else
    {
        attempts++;
        status->setText(
            QString("<font color='red'>Incorrect (%1/%2)</font>")
                .arg(attempts).arg(maxAttempts));

        if (attempts >= maxAttempts)
        {
            remaining = lockSeconds;
            btn->setEnabled(false);
            lockTimer.start(1000);
        }
    }
}

void LoginWidget::tickLockout()
{
    if (--remaining <= 0)
    {
        lockTimer.stop();
        btn->setEnabled(true);
        status->setText("<font color='green'>Lockout over, try again.</font>");
        attempts = 0;
    }
    else
    {
        status->setText(
            QString("<font color='red'>Locked out – %1 s</font>").arg(remaining));
    }
}
