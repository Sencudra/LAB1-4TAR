#ifndef TABLE_H
#define TABLE_H

#include <string.h>
#include <iostream>
#include "cell.h"

class Table
{
public:
    Table();
    Table(const Table &obj);
    ~Table();

    int addRow(int rowPosition);
    int delRow(int rowPosition);

    int addColumn(int rowPosition);
    int delColumn(int rowPosition);

    int showTable();                    //writing table to console

    int saveTableInFile();              //saving table to file
    int loadTableFromFile();            //loading table from file
    int editCell(std::string address, std::string text);

    bool isEmpty();
    int size();                         //Table size
    double getSum();
    double getAveSum();

    int getColumn(){return m_columns;}
    int getRow(){return m_rows;}

private:
    Cell*** createTable(int rows,int columns);
    int deleteTable(Cell*** root, int rows, int columns);
    //int deleteTableWithObj(Cell*** root, int rows, int columns);

private:
    // 2D dinamic array of pointers type Cell
    Cell*** m_root;

    //dimensions
    int m_rows;
    int m_columns;


};

#endif // TABLE_H
