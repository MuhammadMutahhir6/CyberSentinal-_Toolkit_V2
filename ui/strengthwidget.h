#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

class StrengthWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit StrengthWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Password Strength"; }

private slots:
    void check();
    void toggleEcho();

private:
    QLineEdit   *inp;
    QLabel      *res;
    QPushButton *eyeBtn;
    QComboBox   *sensBox;      // NEW

    bool isCommon (const QString& pwd) const;
    bool hasSequential(const QString& pwd, int run) const;
};
