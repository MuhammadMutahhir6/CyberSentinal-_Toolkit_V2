#include "dictattackwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QtConcurrent>
#include <QThread>

// helper to load file into QStringList
static QStringList readWords(const QString& file)
{
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly|QIODevice::Text)) return {};
    QTextStream ts(&f);
    QStringList list;
    QString w;
    while (ts.readLineInto(&w)) list << w.trimmed();
    return list;
}

DictAttackWidget::DictAttackWidget(QWidget *parent) : ToolBase(parent)
{
    auto lay = new QVBoxLayout(this);
    dictPath = new QLineEdit("dictionary.txt");
    auto btnBrowse = new QPushButton("Browse dictionary");
    targetEdit = new QLineEdit; targetEdit->setPlaceholderText("target password");
    auto btnRun = new QPushButton("Run");
    bar    = new QProgressBar; bar->setRange(0,100);
    status = new QLabel;

    lay->addWidget(dictPath); lay->addWidget(btnBrowse);
    lay->addWidget(targetEdit); lay->addWidget(btnRun);
    lay->addWidget(bar); lay->addWidget(status); lay->addStretch();

    connect(btnBrowse,&QPushButton::clicked,this,&DictAttackWidget::browseDict);
    connect(btnRun,&QPushButton::clicked,this,&DictAttackWidget::runAttack);
}

void DictAttackWidget::browseDict()
{
    dictPath->setText(QFileDialog::getOpenFileName(this));
}

void DictAttackWidget::runAttack()
{
    status->clear(); bar->setValue(0);

    const QStringList words = readWords(dictPath->text());
    const QString target    = targetEdit->text();
    if (words.isEmpty() || target.isEmpty())
    { status->setText("<font color='red'>Missing dictionary or target.</font>"); return; }

    QtConcurrent::run([=]{
        const int total = words.size();
        int i = 0;
        for (const QString& word : words)
        {
            // live red label
            QMetaObject::invokeMethod(status, "setText", Qt::QueuedConnection,
                                      Q_ARG(QString,
                                            "<font color='red'>Trying: " + word + "</font>"));
            QMetaObject::invokeMethod(bar, "setValue", Qt::QueuedConnection,
                                      Q_ARG(int, (100 * i) / total));

            if (word == target) {
                QMetaObject::invokeMethod(status, "setText", Qt::QueuedConnection,
                                          Q_ARG(QString,
                                                "<font color='green'>Found: " + word + "</font>"));
                QMetaObject::invokeMethod(bar, "setValue", Qt::QueuedConnection,
                                          Q_ARG(int, 100));
                return;
            }
            ++i;

            QThread::msleep(30);   //  <<< slow it down ~33 words per second
        }
        QMetaObject::invokeMethod(status, "setText", Qt::QueuedConnection,
                                  Q_ARG(QString,
                                        "<font color='orange'>Not in dictionary.</font>"));
    }); }
