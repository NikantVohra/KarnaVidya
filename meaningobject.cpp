#include "meaningobject.h"
#include <QStringList>

MeaningObject::MeaningObject(QObject *parent) :
    QObject(parent)
{\



}

QString MeaningObject::getWord() const
{
    return word;
}

void MeaningObject::setWord(const QString &value)
{
    word = value;
}


QString MeaningObject::getWordTamil() const
{
    return wordTamil;
}

void MeaningObject::setWordTamil(const QString &value)
{
    wordTamil = value;
}

QString MeaningObject::getPartOfSpeech() const
{
    return partOfSpeech;
}

void MeaningObject::setPartOfSpeech(const QString &value)
{
    partOfSpeech = value;
}
QList<QString> MeaningObject::getSynonymEn() const
{
    return synonymEn;
}

void MeaningObject::setSynonymEn(const QList<QString> &value)
{
    synonymEn = value;
}
OrderedMap<QString, QString> MeaningObject::getMeaningEn() const
{
    return meaningEn;
}

void MeaningObject::setMeaningEn(const OrderedMap<QString, QString> &value)
{
    meaningEn = value;
}

OrderedMap<QString, QString> MeaningObject::getMeaningTa() const
{
    return meaningTa;
}

void MeaningObject::setMeaningTa(const OrderedMap<QString, QString> &value)
{
    meaningTa = value;
}



void MeaningObject::read(const QJsonObject &json) {
    word = json["word"].toString();
    wordTamil = json["word_tamil"].toString();
    partOfSpeech = json["Part_of_speech"].toString();
    synonymEn.clear();
    QJsonArray synonymEnArray = json["synonym_en"].toArray();

    for(int synonymEnIndex = 0;synonymEnIndex < synonymEnArray.size(); ++synonymEnIndex) {
        QString synonymEnWord = synonymEnArray[synonymEnIndex].toString();
        synonymEn.append(synonymEnWord);
    }
    meaningEn.clear();
    meaningTa.clear();

    QJsonArray meaningEnList = json["meaning_en"].toArray();
    for(int i = 0;i < meaningEnList.size();i++) {
        QStringList splitted = meaningEnList[i].toString().split("&&");
        if(splitted.count() == 2) {
            meaningEn.insert(splitted[0], splitted[1]);
        }
        else if(splitted.count() == 1) {
            meaningEn.insert(splitted[0], "");
        }
    }

    QJsonArray meaningTaList = json["meaning_ta"].toArray();
    for(int i = 0;i < meaningTaList.size();i++) {
        QStringList splitted = meaningTaList[i].toString().split("&&");
        if(splitted.count() == 2) {
            meaningTa.insert(splitted[0], splitted[1]);
        }
        else if(splitted.count() == 1) {
            meaningTa.insert(splitted[0], "");
        }
    }


//    QJsonObject meaningEnHash = json["meaning_en"].toObject();
//    for(QJsonObject::iterator it=meaningEnHash.begin(); it!= meaningEnHash.end(); it++) {
//        meaningEn.insert(it.key(), it.value().toString());
//    }

//    QJsonObject meaningTaHash = json["meaning_ta"].toObject();
//    for(QJsonObject::iterator it=meaningTaHash.begin(); it!= meaningTaHash.end(); it++) {
//        meaningTa.insert(it.key(), it.value().toString());
//    }

    int count = 1;
    foreach (const QString &key, meaningEn.keys()) {
        meaningEnDescription += QString::number(count) + ". " + key + ":" + meaningEn[key] + "\n";
        count++;
    }

    count = 1;
    foreach (const QString &key, meaningTa.keys()) {
        meaningTaDescription += QString::number(count) + ". " + key + ":" + meaningTa[key] + "\n";
        count++;
    }

    count = 1;
    for(int i = 0;i < synonymEn.size(); i++) {
        synonymsList += QString::number(count) + ". " + synonymEn[i] + "\n";
        count++;
    }


}
QString MeaningObject::getMeaningEnDescription() const
{
    return meaningEnDescription;
}

void MeaningObject::setMeaningEnDescription(const QString &value)
{
    meaningEnDescription = value;
}
QString MeaningObject::getMeaningTaDescription() const
{
    return meaningTaDescription;
}

void MeaningObject::setMeaningTaDescription(const QString &value)
{
    meaningTaDescription = value;
}
QString MeaningObject::getSynonymsList() const
{
    return synonymsList;
}

void MeaningObject::setSynonymsList(const QString &value)
{
    synonymsList = value;
}











