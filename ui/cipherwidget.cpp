#include "cipherwidget.h"
#include "xorcipher.h"
#include <QVBoxLayout>
#include <QFileDialog>

CipherWidget::CipherWidget(bool decrypt, QWidget *parent)
    : ToolBase(parent), decryptMode(decrypt)
{
    auto lay = new QVBoxLayout(this);
    inPath  = new QLineEdit;  outPath = new QLineEdit;  keyEdit = new QLineEdit;
    auto btnIn  = new QPushButton("Browse input");  connect(btnIn,&QPushButton::clicked,this,&CipherWidget::browseIn);
    auto btnOut = new QPushButton("Browse output"); connect(btnOut,&QPushButton::clicked,this,&CipherWidget::browseOut);
    auto runBtn = new QPushButton(decryptMode? "Decrypt":"Encrypt"); connect(runBtn,&QPushButton::clicked,this,&CipherWidget::run);

    status = new QLabel("—");

    lay->addWidget(btnIn);  lay->addWidget(inPath);
    lay->addWidget(btnOut); lay->addWidget(outPath);
    lay->addWidget(new QLabel("Key:")); lay->addWidget(keyEdit);
    lay->addWidget(runBtn); lay->addWidget(status); lay->addStretch();
}

QString CipherWidget::toolName() const { return decryptMode ? "Decrypt File" : "Encrypt File"; }
void CipherWidget::browseIn(){ inPath->setText(QFileDialog::getOpenFileName(this)); }
void CipherWidget::browseOut(){ outPath->setText(QFileDialog::getSaveFileName(this)); }

void CipherWidget::run()
{
    bool ok = XorCipher::transformFile(inPath->text().toStdString(),
                                       outPath->text().toStdString(),
                                       keyEdit->text().toStdString());
    status->setText(ok ? "Success ✅" : "Failed ❌");
}
