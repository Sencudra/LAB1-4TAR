// Class Cell is a description of properties of table's cell
// used to store string or numerical data.


#ifndef CELL_H
#define CELL_H

#include <string.h>
#include <iostream>

class Cell
{
public:
    Cell();                 //Default Constructor
    Cell(const Cell &obj);  //Copy constructor
    ~Cell();                //Destructor

    std::string getData();
    int setData(std::string data); // Cell edit
    int getType(){return m_type;}

private:
    // Methods for changing private variables
    void setType(int i){m_type = i;}
    void setString(const std::string value){m_text = value;}
    void setNum(const double i){m_num = i;}



private:

    //m_type stores type of a cell (ex. Numerical)
    // 0 - empty
    // 1 - string
    // 2 - numerical

    int m_type;
    std::string m_text;
    double m_num;
};

#endif // CELL_H
