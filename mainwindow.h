#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void showAbout();
private:
    QListWidget   *sidebar;
    QStackedWidget* stack;
};
