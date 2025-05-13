#include "aboutdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("About");
    auto lay = new QVBoxLayout(this);
    lay->addWidget(new QLabel("Team Members"));
    lay->addWidget(new QLabel("Name   : Muhammad Hasnain Memon"));
    lay->addWidget(new QLabel("Name   : Muhammad Mutahir"));
    lay->addWidget(new QLabel("Name   : Ali Safir Qadir"));
    lay->addWidget(new QLabel("Course : OOPS"));
    lay->addWidget(new QLabel("Project : CyberSential ToolKit V2"));
    lay->addWidget(new QLabel("Teacher : Sir Waseem Rauf"));
    auto ok = new QPushButton("Close"); lay->addWidget(ok);
    connect(ok,&QPushButton::clicked,this,&QDialog::accept);
}
