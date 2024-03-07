#include "chartable.h"

CharTable::CharTable()
{

}

CharTable::CharTable(QString chr, int pos_up, int pos_down)
{
    this->chr  = chr;
    this->pos_up = pos_up;
    this->pos_down = pos_down;
}

CharTable::CharTable(QString chr, int pos)
{
    this->chr  = chr;
    this->pos_up = pos;
}

