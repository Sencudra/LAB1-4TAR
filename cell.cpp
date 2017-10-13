#include "cell.h"
#include <typeinfo>

// Secondary functions

bool isDouble(std::string inputString, double &result) {
    char* end;
    result = strtod(inputString.c_str(), &end);
    if (end == inputString.c_str() || *end != '\0') return false;
    return true;
}

// Class methods

Cell::Cell()
{
    std::cout <<"("<<this<<")"<< "Creating object...type: "<< typeid(this).name() << std::endl;
    m_type = 0;
}

Cell::~Cell()
{
    std::cout <<"("<<this<<")"<< "Deleting object...type: "<< typeid(this).name() << std::endl;
}

Cell::Cell(const Cell &obj)
{
    m_type = obj.m_type;
    m_text = obj.m_text;
    m_num = obj.m_num;
    std::cout <<"("<<this<<")"<< "Coping object - "<< &obj << std::endl;
}

std::string Cell::getData()
{
    if (m_type == 1){
        //std::cout <<"("<<this<<")"<< "Data saved("<<m_type<<"): " << m_text << std::endl;
        return m_text;
    }
    else if(m_type == 0)
    {
        return "Object is empty!";
    }
    else
    {
        //std::cout <<"("<<this<<")"<< "Data saved("<<m_type<<"): " << m_num << std::endl;
        return std::to_string(m_num);
    }
}



int Cell::setData(std::string input)
{
    std::cout <<"("<<this<<")"<< "Setting value '"<< input << "' to object."<< std::endl;

    if(input.length() == 0)
    {
        setType(0);
    }
    else
    {

        double value;
        if(isDouble(input, value))
        {
            double value = std::stod(input);
            setType(2);
            setNum(value);
        }
        else
        {
            setType(1);
            setString(input);
        }
    }
    return 0;
}




