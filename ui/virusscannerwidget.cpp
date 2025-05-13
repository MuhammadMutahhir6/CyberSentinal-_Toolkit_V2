#include "virusscannerwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QTextStream>

static QString toHex(const QByteArray& data)
{
    return data.toHex().toUpper();
}

VirusScannerWidget::VirusScannerWidget(QWidget *parent) : ToolBase(parent)
{
    auto lay = new QVBoxLayout(this);
    filePath = new QLineEdit;
    sigPath  = new QLineEdit("signatures.txt");
    auto b1 = new QPushButton("Browse file");
    auto b2 = new QPushButton("Browse signatures");
    auto scanBtn = new QPushButton("Scan");
    status = new QLabel;

    lay->addWidget(filePath); lay->addWidget(b1);
    lay->addWidget(sigPath); lay->addWidget(b2);
    lay->addWidget(scanBtn); lay->addWidget(status); lay->addStretch();

    connect(b1,&QPushButton::clicked,this,&VirusScannerWidget::browseFile);
    connect(b2,&QPushButton::clicked,this,&VirusScannerWidget::browseSig);
    connect(scanBtn,&QPushButton::clicked,this,&VirusScannerWidget::scan);
}

void VirusScannerWidget::browseFile()
{
    filePath->setText(QFileDialog::getOpenFileName(this));
}

void VirusScannerWidget::browseSig()
{
    sigPath->setText(QFileDialog::getOpenFileName(this));
}

void VirusScannerWidget::scan()
{
    QFile file(filePath->text());
    if (!file.open(QIODevice::ReadOnly))
    { status->setText("<font color='red'>Cannot open file.</font>"); return; }
    QString hex = toHex(file.readAll()); file.close();

    QFile sig(sigPath->text());
    if (!sig.open(QIODevice::ReadOnly|QIODevice::Text))
    { status->setText("<font color='red'>Cannot open signatures.</font>"); return; }

    QTextStream ts(&sig);
    QString line;
    while (ts.readLineInto(&line))
    {
        auto parts = line.split(':');
        if (parts.size()!=2) continue;
        QString name = parts[0], pattern = parts[1].toUpper();
        if (hex.contains(pattern))
        { status->setText("<font color='red'>Virus detected: "+name+"</font>"); return; }
    }
    status->setText("<font color='green'>No virus signatures found.</font>");
}
