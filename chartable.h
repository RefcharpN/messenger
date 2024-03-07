#ifndef CHARTABLE_H
#define CHARTABLE_H
#include <QString>


class CharTable
{
//private:
    //    int pos_up;
    //    int pos_down = -1;

    //    QString chr;


public:
    CharTable();
    CharTable(QString chr, int pos_up, int pos_down);
    CharTable(QString chr, int pos_up);

    int pos_up;
    int pos_down = -1;

    QString chr;
};

#endif // CHARTABLE_H
