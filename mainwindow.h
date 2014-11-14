#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "meaningobject.h"
#include <QHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    public slots:
        void searchButtonClicked();

private:
    Ui::MainWindow *ui;
    QHash<QString, MeaningObject *> dictionary;
    void readFile();
};

#endif // MAINWINDOW_H
