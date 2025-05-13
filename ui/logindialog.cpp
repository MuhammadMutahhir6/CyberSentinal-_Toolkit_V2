#include "logindialog.h"
#include <QVBoxLayout>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Secure Login");
    auto lay = new QVBoxLayout(this);
    auto *widget = new LoginWidget;
    widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    lay->addWidget(widget);
    resize(400,150);

    // when LoginWidget emits success, close dialog with Accepted
    connect(widget, &LoginWidget::loginSucceeded,
            this,   &LoginDialog::acceptLogin);
}

void LoginDialog::acceptLogin()
{
    accept();   // QDialog::accept() –> returns QDialog::Accepted
}
