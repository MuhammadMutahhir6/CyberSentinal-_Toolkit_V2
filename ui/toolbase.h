#pragma once
#include <QWidget>

class ToolBase : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBase(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual QString toolName() const = 0;
public slots:
    virtual void resetFields() {}
};
