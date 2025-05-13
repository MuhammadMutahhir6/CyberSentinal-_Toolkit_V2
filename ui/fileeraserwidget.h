#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

class FileEraserWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit FileEraserWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Secure File Eraser"; }

private slots:
    void browse();
    void erase();

private:
    QLineEdit  *pathEdit;
    QSpinBox   *passes;
    QLabel     *status;
};
