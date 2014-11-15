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
        void synonymPressed();
        void tabChanged();

private:
    Ui::MainWindow *ui;
    QHash<QString, MeaningObject *> dictionary;
    QString currentWord;
    void populateSynonyms(QString word);
    void readFile();
    void removeSynonyms();
    void setupTabWidget();
    void populateEnglishMeaningList();
    void populateTamilMeaningList();
};

#endif // MAINWINDOW_H
