#ifndef REDCAPELLA_H
#define REDCAPELLA_H

#include "chartable.h"

#include <QDebug>
#include <chartable.h>
#include <QTextCodec>
#include <QString>
#include <iostream>


class RedCapella
{
public:
    RedCapella();
    QString capellaEncode(QString toCode);

private:
    QList<CharTable> generateAlp(QString key);
    QList<int> phraseEncode(QString phrase);

    QList<int> firstEncode(QString toCode);
    QList<int> secondEncode(QList<int> first);

    QList<QString> listEngl = QList<QString>({"A", "a", "B", "b", "C", "c", "D", "d", "E", "e", "F", "f", "G", "g", "H", "h",
                         "I", "i", "J", "j", "K", "k", "L", "l", "M", "m", "N", "n", "O", "o", "P", "p",
                         "Q", "q", "R", "r", "S", "s", "T", "t", "U", "u", "V", "v", "W", "w", "X", "x", "Y", "y","Z", "z"});

    QList<QString> listRus = QList<QString>({"А", "а", "Б", "б", "В", "в", "Г", "г", "Д", "д", "Е", "е", "Ё", "ё", "Ж", "ж",
                         "З", "з", "И", "и", "Й", "й", "К", "к", "Л", "л", "М", "м", "Н", "н", "О", "о",
                         "П", "п", "Р", "р", "С", "с", "Т", "т", "У", "у", "Ф", "ф", "Х", "х", "Ц", "ц", "Ч",
                         "ч","Ш", "ш", "Щ", "щ", "ъ", "ы", "ь", "Э", "э", "Ю", "ю", "Я", "я"});

    QList<QString> listSP = QList<QString>({"\"", ":", " ", "{", "}", ",", ".", "@"});

    QList<QString> fullAlph;

    QList<CharTable> indexTable;

    QList<int> phraseEncoded;
};

#endif // REDCAPELLA_H
