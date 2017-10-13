//Тарасевич Владислав Сергеевич БИВ-164 ВАРИАНТ 18
//
//Некоторых бухгалтеров отталкивает сложность современных электронных таблиц. Разработайте для них программу с
//минимальным функционалом: хранение числовых и текстовых данных в таблице с изменяемым размером.
//Задание Лабораторной работы:
//1. Ячейка электронной таблицы: числовое или текстовое значение, может быть пустой.
//2. Таблица (двухмерный массив): хранение ячеек, вычисление суммы и среднего арифметического
//   всех числовых данных

#include <QCoreApplication>

#include "cell.h"
#include "table.h"

// Memory leaks detector
//#ifdef _DEBUG
//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC
//#endif


// (Temp) Prototypes of interface
bool continueProcess();
int help();
int loadFile(Table &obj);
int saveFile(Table &obj);
int isEmpty(Table &obj);
int edit(Table &obj);       // Edit table
int sum(Table &obj);        // Sum of all digit elements
int average(Table &obj);    // Average sum of all digit elements
int delCol(Table &obj);
int delRow(Table &obj);


// Main
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    {
        std::cout << "To see available commands type 'help'." << std::endl;

        std::string inputData;
        std::cout << "Enter value('quit' to quit the program): ";

        std::getline(std::cin,inputData);

        Table table = Table();

        while(inputData != "quit")
        {
            table.showTable();
            if (inputData == "help")            help();
            else if(inputData == "loadfile")    loadFile(table);
            else if(inputData == "savefile")    saveFile(table);
            else if(inputData == "empty")       isEmpty(table);
            else if(inputData == "edit")        edit(table);
            else if(inputData == "sum")         sum(table);
            else if(inputData == "average")     average(table);
            else if(inputData == "delrow")      delRow(table);
            else if(inputData == "delcolumn")   delCol(table);
            else std::cout << "Input command:" << std::endl;

            std::getline(std::cin,inputData);
        }
    }
    return a.exec();
}

bool continueProcess()
{
    std::string input;
    std::cout << " CONTINUE?  y/n: ";
    std::cin >> input;
    if( input == "y")
        return true;
    else{
        std::cout << " N " << std::endl;
        return false;
    }
}


int help()
{
    std::cout<<"help - to see available commands."<<std::endl;
    std::cout<<"empty - to check whether the table is empty or not(if false return number of elements)."<<std::endl;
    std::cout<<"loadfile - to load table from file."<<std::endl;
    std::cout<<"savefile - to save table into the file."<<std::endl;
    std::cout<<"quit - to quit program."<<std::endl;
    std::cout<<"edit - to edit cell."<<std::endl;
    std::cout<<"sum - to get sum of integer elemets in table."<<std::endl;
    std::cout<<"average - to get average sum of integer elemnts in table."<<std::endl;
    return 0;
}

int loadFile(Table &obj)
{
    std::cout << "Loading table from file." << std::endl;
    if(continueProcess())
    {
        obj.loadTableFromFile();
    }
    return 0;
}
int saveFile(Table &obj)
{
    std::cout << "Loading table in file." << std::endl;
    if(continueProcess())
    {
        obj.saveTableInFile();
    }
    return 0;
}

int isEmpty(Table &obj)
{
    if(obj.isEmpty())
        std::cout << "Table is Empty!"<< std::endl;
    else
        std::cout << "Table size (number of elements): "<< obj.size()  << std::endl;
    return 0;
}

int edit(Table &obj)
{
     std::cout << "Input address and value:"<< std::endl;
     std::string address;
     std::string value;
     std::cin >> address >> value;
     obj.editCell(address,value);
    return 0;
}

int sum(Table &obj)
{
    std::cout << "Sum of elements: " << obj.getSum()<<std::endl;
    return 0;
}

int average(Table &obj)
{
    std::cout << "Average sum of elements: " << obj.getAveSum()<<std::endl;
    return 0;
}

int delCol(Table &obj)
{

    std::cout << "Input index:"<< std::endl;
    int index;
    std::cin >> index;
    if(index > 0 && index <= obj.getColumn())
        obj.delColumn(index);
    else
        std::cout << "Wrong input" << std::endl;
    return 0;
}

int delRow(Table &obj)
{
    std::cout << "Input index"<< std::endl;
    int index;
    std::cin >> index;
    if(index > 0 && index <= obj.getRow())
        obj.delRow(index);
    else
        std::cout << "Wrong input" << std::endl;
    return 0;
}
