#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class VirusCreatorWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit VirusCreatorWidget(QWidget* parent=nullptr);
    QString toolName() const override { return "Mock Virus Creator"; }

private slots:
    void browseOut();
    void create();

private:
    QLineEdit *outPath;
    QLabel    *status;
};
