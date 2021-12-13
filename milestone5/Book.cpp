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
#include "Book.h"
using namespace std;
namespace sdds
{
	Book::Book() : Publication()
	{

	}
	Book::~Book()
	{
		delete[] m_name;
	}
	Book::Book(const Book& rO)
	{
		if (rO)
			operator=(rO);
	}
	Book& Book::operator=(const Book& rO)
	{
		if (this != &rO && rO)
		{
			Publication::operator=(rO);
			delete[] m_name;
			m_name = new char[strlen(rO.m_name) + 1];
			strcpy(m_name, rO.m_name);
		}
		return *this;
	}
	char Book::type()const
	{
		return 'B';
	}
	std::ostream& Book::write(std::ostream& os) const
	{
		char name[MAX_NAME_LENGTH]{};
		strcpy(name, m_name);
		Publication::write(os);
		if (conIO(os))
		{
			os << ' ';
			
			// If name is longer than set width, print only until width
			if (strlen(m_name) > SDDS_AUTHOR_WIDTH)
			{
				os.setf(ios::left);
				for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++)
					os << name[i];
			}
			// otherwise print full name
			else
			{
				os.setf(ios::left);
				os.width(SDDS_AUTHOR_WIDTH);
				os << name;
			}
			os << " |";
		}
		else
			os << '\t' << m_name;
		return os;
	}
	std::istream& Book::read(std::istream& istr)
	{
		char name[MAX_NAME_LENGTH + 1]{};
		Publication::read(istr);
		delete[] m_name;
		if (conIO(istr))
		{
			istr.ignore();
			cout << "Author: ";
			istr.getline(name, MAX_NAME_LENGTH + 1);
		}
		else
		{
			istr.ignore();
			istr.get(name, MAX_NAME_LENGTH + 1);
		}
		if (strlen(name) > MAX_NAME_LENGTH)
			istr.setstate(ios::failbit);
		if (istr)
		{
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
		}
		name[0] = '\0';
		return istr;
	}
	void Book::set(int member_id)
	{
		Publication::set(member_id);
		resetDate();
	}
	Book::operator bool() const
	{
		return Publication::operator bool() && m_name;
	}
}