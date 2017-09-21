#include <QCoreApplication>

#include "cell.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string inputData;
    std::cout << "Input Data for cell1!";
    std::sin >> inputData;

    Cell* cell1  = new Cell();
    cell1->setData(inputData);

    return a.exec();
}
