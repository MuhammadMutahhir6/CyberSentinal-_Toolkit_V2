#include "viruscreatorwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>

VirusCreatorWidget::VirusCreatorWidget(QWidget *parent) : ToolBase(parent)
{
    auto lay = new QVBoxLayout(this);
    outPath = new QLineEdit("testfile.exe");
    auto browseBtn = new QPushButton("Browse output");
    auto createBtn = new QPushButton("Create");
    status = new QLabel;

    lay->addWidget(outPath); lay->addWidget(browseBtn);
    lay->addWidget(createBtn); lay->addWidget(status); lay->addStretch();

    connect(browseBtn,&QPushButton::clicked,this,&VirusCreatorWidget::browseOut);
    connect(createBtn,&QPushButton::clicked,this,&VirusCreatorWidget::create);
}

void VirusCreatorWidget::browseOut()
{
    outPath->setText(QFileDialog::getSaveFileName(this));
}

void VirusCreatorWidget::create()
{
    static const unsigned char sig[] = {0xBA,0xDC,0x0F,0xFE,0xE0,0xDD,0xF0,0x0D};
    QFile f(outPath->text());
    if (!f.open(QIODevice::WriteOnly))
    { status->setText("<font color='red'>Cannot create file.</font>"); return; }
    f.write(reinterpret_cast<const char*>(sig), sizeof(sig));
    f.close();
    status->setText("<font color='green'>Mock virus file created.</font>");
}
