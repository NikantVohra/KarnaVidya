#ifndef MEANINGOBJECT_H
#define MEANINGOBJECT_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <orderedmap.h>

class MeaningObject : public QObject
{
    Q_OBJECT
public:
    explicit MeaningObject(QObject *parent = 0);


    QString getWord() const;
    void setWord(const QString &value);

    QString getWordTamil() const;
    void setWordTamil(const QString &value);

    QString getPartOfSpeech() const;
    void setPartOfSpeech(const QString &value);

    QList<QString> getSynonymEn() const;
    void setSynonymEn(const QList<QString> &value);

    OrderedMap<QString, QString> getMeaningEn() const;
    void setMeaningEn(const OrderedMap<QString, QString> &value);

    OrderedMap<QString, QString> getMeaningTa() const;
    void setMeaningTa(const OrderedMap<QString, QString> &value);

    void read(const QJsonObject &json);

    QString getMeaningEnDescription() const;
    void setMeaningEnDescription(const QString &value);

    QString getMeaningTaDescription() const;
    void setMeaningTaDescription(const QString &value);

    QString getSynonymsList() const;
    void setSynonymsList(const QString &value);



signals:

public slots:

private:
    QString word;
    QString wordTamil;
    QString partOfSpeech;
    QList<QString> synonymEn;
    OrderedMap<QString, QString> meaningEn;
    OrderedMap<QString, QString> meaningTa;

    QString meaningEnDescription;
    QString meaningTaDescription;
    QString synonymsList;

};



#endif // MEANINGOBJECT_H
