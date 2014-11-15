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
    if( ui->synonymList->hasFocus()){
        QString synonym = ui->synonymList->currentItem()->text();
         ui->enterWordEdit->setText(synonym);
        searchButtonClicked();
    }
}

void MainWindow::searchButtonClicked(){
    QString word = ui->enterWordEdit->text();
    currentWord = word;
    if(dictionary.contains(word)) {

        populateEnglishMeaningList();
        populateTamilMeaningList();
        tabChanged();
        populateSynonyms(word);
    }
    else {
        ui->englishMeaningListWidget->clear();
        ui->tamilMeaningsListWidget->clear();
        QListWidgetItem *item = new QListWidgetItem;
        item->setText("No such word available in dictionary");
        ui->englishMeaningListWidget->insertItem(0, item);
        QListWidgetItem *item1 = new QListWidgetItem;
        item1->setText("No such word available in dictionary");
        ui->tamilMeaningsListWidget->insertItem(0, item1);
        tabChanged();
        ui->synonymList->clear();

    }
}

void MainWindow::populateEnglishMeaningList() {
    ui->englishMeaningListWidget->clear();
    int count = 1;
    QString meaningEnDescription;
    QHash<QString, QString> meaningEn = dictionary[currentWord]->getMeaningEn();
    foreach (const QString &key, meaningEn.keys()) {
        meaningEnDescription = QString::number(count) + ". " + key + ":" + meaningEn[key] + "\n";
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(meaningEnDescription);
        ui->englishMeaningListWidget->insertItem(count-1, item);
        count++;
    }
}

void MainWindow::populateTamilMeaningList() {
    ui->tamilMeaningsListWidget->clear();
    int count = 1;
    QString meaningTaDescription;
    QHash<QString, QString> meaningTa = dictionary[currentWord]->getMeaningTa();
    foreach (const QString &key, meaningTa.keys()) {
        meaningTaDescription = QString::number(count) + ". " + key + ":" + meaningTa[key] + "\n";
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(meaningTaDescription);
        ui->tamilMeaningsListWidget->insertItem(count-1, item);
        count++;
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
