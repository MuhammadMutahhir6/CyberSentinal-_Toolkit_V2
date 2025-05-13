#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class CipherWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit CipherWidget(bool decrypt, QWidget* parent=nullptr);

    QString toolName() const override;
private slots:
    void browseIn();
    void browseOut();
    void run();
private:
    bool decryptMode;
    QLineEdit *inPath,*outPath,*keyEdit;
    QLabel *status;
};
