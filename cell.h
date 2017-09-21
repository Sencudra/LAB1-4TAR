#ifndef CELL_H
#define CELL_H

#include <string.h>

class Cell
{
public:
    Cell(); //Конструктор

    Cell(const Cell &obj); // Копирующий конструктор

    ~Cell();asdasd

    auto getData();
    int setData(string data);

private:

    int setType();
    int setString();
    int setNum();

private:
    int type;
    string text;
    double num;
};

#endif // CELL_H
