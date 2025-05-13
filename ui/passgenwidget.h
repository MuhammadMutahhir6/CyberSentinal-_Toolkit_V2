#pragma once
#include "toolbase.h"
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>

class PassGenWidget : public ToolBase
{
    Q_OBJECT
public:
    PassGenWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Password Generator"; }
private slots:
    void generate();
private:
    QSpinBox *len;
    QLineEdit *out;
};
