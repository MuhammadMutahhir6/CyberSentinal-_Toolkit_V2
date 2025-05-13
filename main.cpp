#include <QApplication>
#include "ui/logindialog.h"   // NEW – the modal login dialog
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /* 1. show the Secure‑Login dialog */
    LoginDialog dlg;                 // requires logindialog.h / .cpp
    if (dlg.exec() != QDialog::Accepted)
        return 0;                    // user closed dialog or failed login

    /* 2. launch the main GUI after successful login */
    MainWindow w;
    w.show();
    return a.exec();
}
