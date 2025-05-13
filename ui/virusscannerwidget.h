#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class VirusScannerWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit VirusScannerWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Virus Scanner"; }

private slots:
    void browseFile();
    void browseSig();
    void scan();

private:
    QLineEdit *filePath;
    QLineEdit *sigPath;
    QLabel    *status;
};
