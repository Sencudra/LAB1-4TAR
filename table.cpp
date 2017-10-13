#include "table.h"
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <iomanip>


Table::Table()
{
    std::cout <<"("<<this<<")"<< "Creating object...type: "<< typeid(this).name() << std::endl;

    m_rows = 1;
    m_columns = 1;

    // dynamic allocation
    m_root = createTable(m_rows,m_columns);

}

Cell*** Table::createTable(int rows,int columns)
{
    // dynamic allocation
    Cell*** root = new Cell**[rows];
    for(int i = 0; i < rows; ++i)
          root[i] = new Cell*[columns];

    for(int i = 0; i < rows;++i)
        for(int j = 0; j < columns; ++j)
            root[i][j] = NULL;
    return root;
}

int Table::deleteTable(Cell ***root, int rows, int columns)
{
    for(int i = 0; i < rows; ++i){
        delete [] root[i];
    }
    delete [] root;

    return 0;
}

Table::Table(const Table &obj)
{
    m_columns = obj.m_columns;
    m_rows = obj.m_rows;

    m_root = new Cell**[m_rows];
    for(int i = 0; i < m_rows; ++i)
          m_root[i] = new Cell*[m_columns];

    for(int i = 0; i < m_rows;i++)
        for(int j = 0; j < m_columns; j++)
            m_root[i][j] = obj.m_root[i][j];

    std::cout <<"("<<this<<")"<< "Coping object - "<< &obj << std::endl;
}

Table::~Table()
{
    for(int i = 0; i < m_rows; ++i){
        for(int j = 0;j < m_columns; ++j)
            delete m_root[i][j];
        delete [] m_root[i];
    }
    delete [] m_root;
    std::cout <<"("<<this<<")"<< "Deleting object...type: "<< typeid(this).name() << std::endl;
}

int Table::showTable()
{
    std::cout << std::endl;
    for(int i = 0;i < m_rows; ++i){
        for( int j = 0; j < m_columns; ++j)
             m_root[i][j] != NULL ? std::cout << std::fixed << std::setw(11) <<  m_root[i][j]->getData() << "  " : std::cout << "      X      ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

bool Table::isEmpty()
{
    bool flag = true;
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
        {
            if(m_root[i][j] != NULL)
                flag = false;
        }
    return flag;
}

int Table::size()
{
    int elements = 0;
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
        {
            if(m_root[i][j] != NULL)
                ++elements;
        }
    return elements;
}

double Table::getAveSum()
{
    int elements = 0;
    double sum = 0;
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
        {
            if(m_root[i][j] != NULL && m_root[i][j]->getType() == 2)
            {
                ++elements;
                sum += std::stod(m_root[i][j]->getData());
            }
        }
    double result = sum/elements;
    return result;
}

double Table::getSum()
{
    double sum = 0;
    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < m_columns; ++j)
        {
            if(m_root[i][j] != NULL && m_root[i][j]->getType() == 2)
            {
                sum += std::stod(m_root[i][j]->getData());
            }
        }
    return sum;
}

int Table::addRow(int rowPosition)
{
    int rows = m_rows;
    int columns = m_columns;

    if(rowPosition <= m_rows)
    {
        ++m_rows;
        Cell*** new_root = createTable(m_rows,m_columns);
        // Copying before rowPosition
        for(int i = 0; i < rowPosition-1; ++i)
            for(int j = 0; j < m_columns;++j)
                new_root[i][j] = m_root[i][j];

        // Filling with NULL added row
            for(int j = 0; j < columns;++j)
                new_root[rowPosition-1][j] = NULL;

            // Copying the other part of table
        for(int i = rowPosition-1;i < rows;++i)
            for(int j = 0; j < m_columns;++j)
                new_root[i+1][j] = m_root[i][j];

        deleteTable(m_root,rows,columns);
        m_root = new_root;
    }
    else
    {
        m_rows += rowPosition - m_rows;
        Cell*** new_root = createTable(m_rows,m_columns);
        // Copying table
        for(int i = 0; i < rows; ++i)
            for(int j = 0; j < m_columns;++j)
                new_root[i][j] = m_root[i][j];
        for(int i = rows; i < rowPosition; ++i)
            for(int j = 0; j < m_columns;++j)
                new_root[i][j] = NULL;

        deleteTable(m_root,rows,columns);
        m_root = new_root;
    }


    return 0;
}

int Table::delRow(int rowPosition)
{
    int rows = m_rows;
    int columns = m_columns;

    --m_rows;
    Cell*** new_root = createTable(m_rows,m_columns);

    for(int i = 0; i < rowPosition-1; ++i)
        for(int j = 0; j < m_columns;++j)
            new_root[i][j] = m_root[i][j];

    for(int i = 0; i < m_columns;++i)
        if (m_root[rowPosition-1][i] != NULL)
            delete m_root[rowPosition-1][i];

    for(int i = rowPosition; i < rows; ++i)
        for(int j = 0; j < m_columns;++j)
            new_root[i-1][j] = m_root[i][j];

    deleteTable(m_root,rows,columns);
    m_root = new_root;

    return 0;
}

int Table::addColumn(int colPosition)
{
    int rows = m_rows;
    int columns = m_columns;

    if(colPosition <= m_columns)
    {
        ++m_columns;
        Cell*** new_root = createTable(m_rows,m_columns);
        // Copying before colPosition
        for(int i = 0; i < m_rows; ++i)
            for(int j = 0; j < colPosition-1;++j)
                new_root[i][j] = m_root[i][j];

        // Filling with NULL added row
            for(int j = 0; j < m_rows;++j)
                new_root[j][colPosition-1] = NULL;

            // Copying the other part of table
        for(int i = 0;i < m_rows;++i)
            for(int j = colPosition-1; j < columns;++j)
                new_root[i][j+1] = m_root[i][j];

        deleteTable(m_root,rows,columns);
        m_root = new_root;
    }
    else
    {
        m_columns += colPosition-m_columns;
        Cell*** new_root = createTable(m_rows,m_columns);
        // Copying table
        for(int i = 0; i < m_rows; ++i)
            for(int j = 0; j < columns;++j)
                new_root[i][j] = m_root[i][j];
        for(int i = 0; i < m_rows; ++i)
            for(int j = columns; j < colPosition;++j)
                new_root[i][j] = NULL;

        deleteTable(m_root,rows,columns);
        m_root = new_root;

    }
    return 0;
}

int Table::delColumn(int colPosition)
{
    int rows = m_rows;
    int columns = m_columns;

    --m_columns;
    Cell*** new_root = createTable(m_rows,m_columns);

    for(int i = 0; i < m_rows; ++i)
        for(int j = 0; j < colPosition-1;++j)
            new_root[i][j] = m_root[i][j];

    for(int i = 0; i < m_rows;++i)
        if (m_root[i][colPosition-1] != NULL)
        {
            delete m_root[i][colPosition-1];
        }

    for(int i = 0; i < m_rows; ++i)
        for(int j = colPosition; j < columns;++j)
            new_root[i][j-1] = m_root[i][j];

    deleteTable(m_root,rows,columns);
    m_root = new_root;

    return 0;;
}


int Table::editCell(std::string address, std::string text)
{
    int row = 0;
    int column = 0;

    // Verifing required cell
    for(unsigned int i = 0; i < address.length();++i)
    {
        if(std::isalpha(address[i]))
            column += int(std::tolower(address[i]))-96;
        else if(std::isdigit(address[i])){
            unsigned int j = i;
            while(std::isdigit(address[j]) && j < address.length())
            {
                j++;
            }
            row += std::stoi(address.substr(i,j));
        }
    }

    if(row != 0 && column != 0)
    {
        if(row > m_rows)
            addRow(row);
        if(column > m_columns)
            addColumn(column);
        if(m_root[row-1][column-1] == NULL)
        {
            m_root[row-1][column-1] = new Cell();
        }
        m_root[row-1][column-1]->setData(text);
    }
    else
    {
        std::cout << "Wrong address: " << address << std::endl;
        return 1;
    }

    return 0;
}


int Table::saveTableInFile()
{
    std::ofstream fout;
    fout.open("C:\\Users\\vladt\\Documents\\Qt Projects\\Lab1\\LAB1-4TAR\\input2.txt");
    if(!fout)
        std::cout << "Cannot open file.\n";
    else
    {
        for(int i = 0; i < m_rows; ++i)
            for(int j = 0; j < m_columns; ++j)
            {
                if(m_root[i][j] != NULL)
                    fout <<  char(j+97) << int(i+1) << " " << m_root[i][j]->getData() << std::endl;
            }
    }

}

int Table::loadTableFromFile()
{
    std::ifstream fin;
    //std::cout << " Input full file address" << std::endl;
    //std::string fAddress;
    //std::cin >> fAddress;
    fin.open("C:\\Users\\vladt\\Documents\\Qt Projects\\Lab1\\LAB1-4TAR\\input.txt");
    if(!fin)
        std::cout << "Cannot open file.\n";
    else
    {
        std::string cellAddress;
        std::string cellData;
        while(fin >> cellAddress >> cellData)
        {
            editCell(cellAddress,cellData);
        }
    }
    fin.close();
    return 0;

}
