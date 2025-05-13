#include "mainwindow.h"

#include "bruteforcewidget.h"
#include "cipherwidget.h"
#include "passgenwidget.h"
#include "strengthwidget.h"
//#include "loginwidget.h"           // new
#include "fileeraserwidget.h"      // new
#include "dictattackwidget.h"      // new
#include "virusscannerwidget.h"    // new
#include "viruscreatorwidget.h"    // new
#include "aboutdialog.h"

#include <QMenuBar>
#include <QApplication>
#include <QFile>
#include <QHBoxLayout>

MainWindow::MainWindow()
{
    resize(1000, 700);                     // a bit wider/taller for the extra pages
    sidebar = new QListWidget;
    sidebar->setFixedWidth(180);
    stack   = new QStackedWidget;

    std::vector<ToolBase*> tools = {
        new BruteForceWidget,
        new CipherWidget(false),
        new CipherWidget(true),
        new PassGenWidget,
        new StrengthWidget,
        //new LoginWidget,           // ← added
        new FileEraserWidget,      // ← added
        new DictAttackWidget,      // ← added
        new VirusScannerWidget,    // ← added
        new VirusCreatorWidget     // ← added
    };

    for (ToolBase* t : tools) {
        stack->addWidget(t);
        sidebar->addItem(t->toolName());
    }
    sidebar->setCurrentRow(0);

    auto central = new QWidget;
    auto lay = new QHBoxLayout(central);
    lay->addWidget(sidebar);
    lay->addWidget(stack);
    setCentralWidget(central);

    connect(sidebar, &QListWidget::currentRowChanged,
            stack,   &QStackedWidget::setCurrentIndex);

    auto aboutAct = menuBar()->addMenu("&Help")->addAction("About");
    connect(aboutAct, &QAction::triggered, this, &MainWindow::showAbout);

    QApplication::setStyle("fusion");
}

void MainWindow::showAbout()
{
    AboutDialog(this).exec();
}
