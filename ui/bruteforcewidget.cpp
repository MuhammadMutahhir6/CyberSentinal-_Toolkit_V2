#include "bruteforcewidget.h"
#include "bruteforce.h"
#include <QVBoxLayout>
#include <QtConcurrent>
#include <QElapsedTimer>
#include <QSet>
#include <QMessageBox>
#include <QStyle>

// ------------------------------------------------------------------
BruteForceWidget::BruteForceWidget(QWidget *parent)
    : ToolBase(parent)
{
    // big font
    QFont f = font(); f.setPointSize(f.pointSize() + 2); setFont(f);

    auto lay = new QVBoxLayout(this);

    txtTarget = new QLineEdit;
    txtTarget->setPlaceholderText("target password");
    connect(txtTarget,&QLineEdit::textChanged,
            this,&BruteForceWidget::updateLengthFromTarget);

    spnLen = new QSpinBox;
    spnLen->setRange(1, 20);                     // hard upper limit
    spnLen->setReadOnly(true);                   // user can’t edit
    spnLen->setButtonSymbols(QSpinBox::NoButtons);

    modeBox = new QComboBox;
    modeBox->addItem("Auto (Char‑set from target)");
    modeBox->addItem("Moderate (a‑z, A‑Z)");
    modeBox->addItem("Hard (a‑z, A‑Z, 0‑9)");
    modeBox->addItem("Extreme (+special)");

    btnStart = new QPushButton("Start");
    btnStop  = new QPushButton("Stop");
    btnStop->setEnabled(false);

    // stylesheet: keep blue even when disabled
    const QString css =
        "QPushButton { background:#1976d2; color:white; "
        "border-radius:6px; padding:6px 12px; }"
        "QPushButton:disabled { background:#455a64; color:#cfd8dc; }";
    btnStart->setStyleSheet(css);
    btnStop ->setStyleSheet(css);

    bar       = new QProgressBar; bar->setRange(0,100);
    lblStatus = new QLabel("Idle");
    lblResult = new QLabel;

    lay->addWidget(new QLabel("Target password:")); lay->addWidget(txtTarget);
    lay->addWidget(new QLabel("Length (auto):"));   lay->addWidget(spnLen);
    lay->addWidget(new QLabel("🔐 Attack Mode:"));  lay->addWidget(modeBox);

    auto h = new QHBoxLayout; h->addWidget(btnStart); h->addWidget(btnStop);
    lay->addLayout(h);

    lay->addWidget(bar);
    lay->addWidget(lblStatus);
    lay->addWidget(lblResult);
    lay->addStretch();

    connect(btnStart,&QPushButton::clicked,this,&BruteForceWidget::onStart);
    connect(btnStop ,&QPushButton::clicked,this,&BruteForceWidget::onStop);
}

// keep spin‑box synced with target length --------------------------
void BruteForceWidget::updateLengthFromTarget()
{
    spnLen->setValue(txtTarget->text().size());
}

// charset builders --------------------------------------------------
QString BruteForceWidget::baseCharset(int mode) const
{
    const QString lower   = "abcdefghijklmnopqrstuvwxyz";
    const QString upper   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString digits  = "0123456789";
    const QString special = "!@#$%^&*_-+=";

    switch (mode) {
    case 0: { // Auto
        QSet<QChar> set;
        for (QChar c : txtTarget->text()) set.insert(c);
        QString cs; for (QChar c : set) cs.append(c);
        return cs.isEmpty() ? lower : cs;
    }
    case 1:  return lower + upper;
    case 2:  return lower + upper + digits;
    default: return lower + upper + digits + special;
    }
}

// ensure every char in target is in charset ------------------------
bool BruteForceWidget::targetFitsCharset(const QString& target,
                                         const QString& charset) const
{
    for (QChar c : target)
        if (!charset.contains(c))
            return false;
    return true;
}

// ------------------------------------------------------------------
void BruteForceWidget::onStart()
{
    lblResult->clear(); bar->setValue(0);

    const QString target = txtTarget->text();
    if (target.isEmpty()) { lblStatus->setText("Enter a target first."); return; }

    const QString charset = baseCharset(modeBox->currentIndex());

    // validation
    if (!targetFitsCharset(target, charset)) {
        QMessageBox::warning(this, "Mode‑Target mismatch",
            "Your selected mode doesn’t cover all characters "
            "in the target password.\n\n"
            "Either choose a broader mode or use Auto.");
        return;
    }

    const int maxLen = target.size();   // auto‑length
    stopFlag = false;

    lblStatus->setText("Attempting to crack…");
    btnStart->setEnabled(false);
    btnStop ->setEnabled(true);

    auto *timer = new QElapsedTimer; timer->start();

    QtConcurrent::run([=]{
        QString found = QString::fromStdString(
            BruteForce::attack(target.toStdString(),
                               maxLen,
                               charset.toStdString(),
                               [&](double p){
                                   QMetaObject::invokeMethod(bar,"setValue",
                                       Qt::QueuedConnection,Q_ARG(int,int(p)));
                               },
                               [&](const std::string& g){
                                   double s = timer->elapsed()/1000.0;
                                   QMetaObject::invokeMethod(lblStatus,"setText",
                                       Qt::QueuedConnection,
                                       Q_ARG(QString,
                                           QString("Guess: %1  |  %2 s")
                                           .arg(QString::fromStdString(g))
                                           .arg(s,0,'f',1)));
                               },
                               stopFlag));

        double secs = timer->elapsed()/1000.0; delete timer;

        QMetaObject::invokeMethod(lblResult,"setText",Qt::QueuedConnection,
            Q_ARG(QString,
                  found.isEmpty() ? "Cancelled / Not found."
                                  : QString("Cracked: %1  (in %2 s)")
                                        .arg(found).arg(secs,0,'f',2)));
        QMetaObject::invokeMethod(lblStatus,"setText",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString,"Done."));

        QMetaObject::invokeMethod(btnStart,"setEnabled",
                                  Qt::QueuedConnection,Q_ARG(bool,true));
        QMetaObject::invokeMethod(btnStop,"setEnabled",
                                  Qt::QueuedConnection,Q_ARG(bool,false));
    });
}

// ------------------------------------------------------------------
void BruteForceWidget::onStop()
{
    stopFlag = true;
    btnStop->setEnabled(false);
    lblStatus->setText("Stopping…");
}
