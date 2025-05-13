#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class LoginWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Login System"; }

private slots:
    void tryLogin();
    void tickLockout();
signals:
    void loginSucceeded();
private:
    QLineEdit *pwdEdit;
    QLabel    *status;
    QPushButton *btn;
    QTimer    lockTimer;
    int       remaining{0};

    const QString correct = "password123";
    const int maxAttempts = 3;
    const int lockSeconds = 10;
    int attempts{0};


};
