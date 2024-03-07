#include "redcapella.h"

#include <QDebug>
#include <chartable.h>

RedCapella::RedCapella()
{
    for(int i = 0; i < this->listRus.length(); i++)
    {
        if(!(i >= this->listEngl.length()))
        {
            this->fullAlph.append(this->listEngl.at(i));
        }

        this->fullAlph.append(this->listRus.at(i));

        if(!(i >= this->listSP.length()))
        {
            this->fullAlph.append(this->listSP.at(i));
        }
    }

    QString word = "A\"aа:BБ bб{CВcв,D.dг";//TODO: динамический выбор слова
    QString phrase = "DOKUMENTARFILMESINDBELEGTWERDENABERRASCHWIEDERFREI";//получение при успешной аутентификации

    this->indexTable = generateAlp(word);
    this->phraseEncoded = this->phraseEncode(phrase);
}

QString RedCapella::capellaEncode(QString toCode)
{

    QList<int> firstEncode = this->firstEncode(toCode);
    QList<int> secondEncode = this->secondEncode(firstEncode);

    QString s = "";

    for (auto &value : secondEncode)
    {
        s += QString("%1").arg(value);
    }

    qWarning() << s;
    return s;
}

QList<CharTable> RedCapella::generateAlp(QString key)
{
    QList<CharTable> table;

    QList<QString> l;
    for(int i = 0; i < key.length(); i++)
    {
        l.append(key.mid(i,1));
    }

    //первая строка алфавита
    for(auto item : l)
    {
        int currentIndex = this->fullAlph.indexOf(QString(item));
        for(int findIndex = currentIndex - 1; findIndex >= 0; findIndex--)
        {
            if(l.indexOf(this->fullAlph.at(findIndex)) == -1)
            {
                currentIndex--;
            }
        }
        if(currentIndex == 19)
        {
            table.append(CharTable(QString(item), 0, (this->fullAlph.indexOf(QString(l.at(0))) + 1) >= 10 ? (this->fullAlph.indexOf(QString(l.at(0))) + 1) % 10 : this->fullAlph.indexOf(QString(l.at(0))) + 1));
            continue;
        }
        table.append(CharTable(QString(item), currentIndex+1, (this->fullAlph.indexOf(QString(l.at(0))) + 1) >= 10 ? (this->fullAlph.indexOf(QString(l.at(0))) + 1) % 10 : this->fullAlph.indexOf(QString(l.at(0))) + 1));
    }

    //заполнение всего алфавита
    for(auto item: this->fullAlph)
    {
        auto itObj = std::find_if(table.begin(), table.end(),[item](CharTable o) { return o.chr == item; });
        if (itObj == table.end())
        {


            if(table.length() % 20 == 0)
            {
                int posDown = this->fullAlph.indexOf(table[(table.length()/20 - 1) * 20].chr)/10 + this->fullAlph.indexOf(item)%10 + 2;
                table.append(CharTable(QString(item), table[table.length() % 20].pos_up, posDown));
                continue;
            }

            int posDown = this->fullAlph.indexOf(table[(table.length()/20 - 1) * 20].chr)/10 + this->fullAlph.indexOf(table[table.length()/20 * 20].chr)%10 + 2;
            table.append(CharTable(QString(item), table[table.length() % 20].pos_up, posDown));
        }
    }
    //вывод всей таблицы символов с индексами
    for(int i = 0; i < table.count(); i++)
    {
        qWarning() << table[i].chr << " " << table[i].pos_up << table[i].pos_down;

    }

    return table;
}

//перевод кодовой фразы в цифры
QList<int> RedCapella::phraseEncode(QString phrase)
{

    QList<QString> phrasedBa;
    for(int i = 0; i < phrase.length(); i++)
    {
        phrasedBa.append(phrase.mid(i,1));
    }

    QList<int> exitPhrase;

    for(auto item: phrasedBa)
    {
        auto itObj = std::find_if(this->indexTable.begin(), this->indexTable.end(),[item](CharTable o) { return o.chr == QString(item); });
        if (itObj != this->indexTable.end())
        {
            if(itObj->pos_up >= 10)
            {
                exitPhrase.append(itObj->pos_up / 10);
                exitPhrase.append(itObj->pos_up % 10);
            }
            else
            {
                exitPhrase.append(0);
                exitPhrase.append(itObj->pos_up);
            }
        }
    }
    qWarning()<< "кодовая фраза - " << exitPhrase;
    return exitPhrase;
}

//первый слой шифра
QList<int> RedCapella::firstEncode(QString toCode)
{
    QList<QString> l;
    for(int i = 0; i < toCode.length(); i++)
    {
        l.append(toCode.mid(i,1));
    }

    QList<int> exitBa;

    for(auto item: l)
    {
        auto itObj = std::find_if(this->indexTable.begin(), this->indexTable.end(),[item](CharTable o) { return o.chr == QString(item); });
        if (itObj != this->indexTable.end())
        {
            if(itObj->pos_up >= 10)
            {
                exitBa.append(itObj->pos_up / 10);
                exitBa.append(itObj->pos_up % 10);
            }
            else
            {
                exitBa.append(0);
                exitBa.append(itObj->pos_up);
            }

            if(itObj->pos_down >= 10)
            {
                exitBa.append(itObj->pos_down / 10);
                exitBa.append(itObj->pos_down % 10);
            }
            else
            {
                exitBa.append(0);
                exitBa.append(itObj->pos_down);
            }
        }

    }
    qWarning() << exitBa << "исходное сообщение";
    return exitBa;
}

//второй слой шифра
QList<int> RedCapella::secondEncode(QList<int> first)
{
        QList<int> finalCode;
        int count = 0;

        for(auto item: first)
        {
            if(count == this->phraseEncoded.length())
            {
                count = 0;
            }
            finalCode.append((item + this->phraseEncoded.at(count)) % 10);
            count++;

        }
        qWarning() << finalCode << "результат шифра";
        return finalCode;
}
