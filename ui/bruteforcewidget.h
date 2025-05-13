#pragma once
#include "toolbase.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <atomic>

class BruteForceWidget : public ToolBase
{
    Q_OBJECT
public:
    explicit BruteForceWidget(QWidget* parent = nullptr);
    QString toolName() const override { return "Brute‑Force"; }

private slots:
    void onStart();
    void onStop();
    void updateLengthFromTarget();          // NEW

private:
    QLineEdit    *txtTarget;
    QSpinBox     *spnLen;
    QComboBox    *modeBox;
    QProgressBar *bar;
    QLabel       *lblStatus;
    QLabel       *lblResult;
    QPushButton  *btnStart;
    QPushButton  *btnStop;

    std::atomic_bool stopFlag {false};

    // helpers
    QString baseCharset(int mode) const;
    bool targetFitsCharset(const QString& target, const QString& charset) const;
};
