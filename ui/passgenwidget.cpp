#include "passgenwidget.h"
#include "passwordutils.h"
#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>
#include <QLabel>

PassGenWidget::PassGenWidget(QWidget *parent)
    : ToolBase(parent)
{
    auto lay = new QVBoxLayout(this);
    len = new QSpinBox; len->setRange(4, 64); len->setValue(12);
    out = new QLineEdit; out->setReadOnly(true);
    auto btn = new QPushButton("Generate"); connect(btn,&QPushButton::clicked,this,&PassGenWidget::generate);
    lay->addWidget(new QLabel("Length:")); lay->addWidget(len);
    lay->addWidget(btn); lay->addWidget(out); lay->addStretch();
}

void PassGenWidget::generate()
{
    QString pwd = QString::fromStdString(PasswordUtils::generate(len->value()));
    out->setText(pwd);
    QApplication::clipboard()->setText(pwd);
}
