/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Date.h"
#include "Publication.h"
using namespace std;
namespace sdds
{
    /*Streamable::Streamable()
    {

    }*/
    Streamable::~Streamable()
    {

    }
    ostream& operator<<(ostream& ostr, const Streamable& rO)
    {   
        if (rO)
        {
            rO.write(ostr);
        }
        return ostr;
    }
    istream& operator>>(istream& istr, Streamable& rO)
    {
        rO.read(istr);
        return istr;
    }
}

