#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>

class DictAttackWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit DictAttackWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Dictionary Attack"; }

private slots:
    void browseDict();
    void runAttack();

private:
    QLineEdit    *dictPath;
    QLineEdit    *targetEdit;
    QLabel       *status;
    QProgressBar *bar;          // NEW
};
