#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
    connect(ui->enterWordEdit, SIGNAL(returnPressed()), this, SLOT(searchButtonClicked()));

    readFile();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::searchButtonClicked(){
    QString word = ui->enterWordEdit->text();
    if(dictionary.contains(word)) {
        ui->englishTextEdit->setText(dictionary[word]->getMeaningEnDescription());
        ui->tamilTextEdit->setText(dictionary[word]->getMeaningTaDescription());
        ui->synonymList->setText(dictionary[word]->getSynonymsList());
    }
    else {
        ui->englishTextEdit->setText("No such word available in dictionary");
        ui->tamilTextEdit->setText("No such word available in dictionary");
        ui->synonymList->setText("");
    }
}


void MainWindow::readFile() {
    QFile file(":/Dictionary.txt");
    QString meaning;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setAutoDetectUnicode(true);
        in.setCodec("UTF-8");

        while(!in.atEnd()) {
            MeaningObject *dictionaryEntry = new MeaningObject();
            QJsonDocument dictionaryEntryJson = QJsonDocument::fromJson(in.readLine().toUtf8());
            dictionaryEntry->read(dictionaryEntryJson.object());
            dictionary.insert(dictionaryEntry->getWord(), dictionaryEntry);
        }
    }
}
