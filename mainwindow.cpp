#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QShortcut>
#include<QUrl>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
    connect(ui->enterWordEdit, SIGNAL(returnPressed()), this, SLOT(searchButtonClicked()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged()));
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Space), ui->synonymList);
    connect(shortcut, SIGNAL(activated()), this, SLOT(synonymPressed()));
    readFile();
}

void MainWindow::setupTabWidget(){

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tabChanged() {
    if(ui->tabWidget->currentIndex() == 2) {
        ui->wikipediaWebView->load(QUrl("http://en.wikipedia.org/wiki/"+currentWord));
    }
}

void MainWindow::synonymPressed() {
    QString synonym = ui->synonymList->currentItem()->text();
    ui->enterWordEdit->setText(synonym);
    searchButtonClicked();
}

void MainWindow::searchButtonClicked(){
    QString word = ui->enterWordEdit->text();
    currentWord = word;
    if(dictionary.contains(word)) {
        ui->englishPlainTextEdit->setPlainText(dictionary[word]->getMeaningEnDescription());
        ui->tamilTextEdit->setText(dictionary[word]->getMeaningTaDescription());
        tabChanged();
        populateSynonyms(word);
    }
    else {
        ui->englishPlainTextEdit->setPlainText("No such word available in dictionary");
        ui->tamilTextEdit->setText("No such word available in dictionary");
        tabChanged();
        ui->synonymList->clear();
    }
}
void MainWindow::populateSynonyms(QString word){
    QList<QString> synonyms = dictionary[word]->getSynonymEn();
    for(int i =0;i < synonyms.size();i++) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(synonyms[i]);
        ui->synonymList->insertItem(i, item);

    }
}

void MainWindow::removeSynonyms() {
    for(int i = 0; i < ui->synonymList->count(); ++i)
    {
        ui->synonymList->takeItem(i);
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
