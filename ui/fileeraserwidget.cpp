#include "fileeraserwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QRandomGenerator>

FileEraserWidget::FileEraserWidget(QWidget *parent) : ToolBase(parent)
{
    auto lay = new QVBoxLayout(this);
    pathEdit = new QLineEdit;
    passes   = new QSpinBox; passes->setRange(1,10); passes->setValue(3);
    auto browseBtn = new QPushButton("Browse");
    auto eraseBtn  = new QPushButton("Erase");
    status  = new QLabel;

    lay->addWidget(pathEdit); lay->addWidget(browseBtn);
    lay->addWidget(new QLabel("Passes:")); lay->addWidget(passes);
    lay->addWidget(eraseBtn); lay->addWidget(status); lay->addStretch();

    connect(browseBtn,&QPushButton::clicked,this,&FileEraserWidget::browse);
    connect(eraseBtn ,&QPushButton::clicked,this,&FileEraserWidget::erase);
}

void FileEraserWidget::browse()
{
    pathEdit->setText(QFileDialog::getOpenFileName(this));
}

void FileEraserWidget::erase()
{
    QFile f(pathEdit->text());
    if (!f.open(QIODevice::ReadWrite))
    { status->setText("<font color='red'>Cannot open file.</font>"); return; }

    QByteArray buf(f.size(), 0);
    for (int p=0;p<passes->value();++p)
    {
        QRandomGenerator::global()->fillRange(reinterpret_cast<quint32*>(buf.data()),
                                              buf.size()/4);
        f.seek(0);
        f.write(buf);
        f.flush();
    }
    f.close();
    if (QFile::remove(pathEdit->text()))
        status->setText("<font color='green'>File securely erased.</font>");
    else
        status->setText("<font color='red'>Delete failed.</font>");
}
