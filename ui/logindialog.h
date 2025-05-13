#pragma once
#include <QDialog>
#include "loginwidget.h"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget* parent=nullptr);
private slots:
    void acceptLogin();   // forwarded from embedded widget
};
