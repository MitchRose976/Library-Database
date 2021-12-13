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
#include "Streamable.h"
using namespace std;
namespace sdds
{
	Publication::Publication() : Streamable()
	{
		
	}
	// Rule of Three
	Publication::~Publication()
	{
		delete[] m_title;
	}
	Publication::Publication(const Publication& rO)
	{
		if (rO)
		{
			*this = rO;
		}
	}
	Publication& Publication::operator=(const Publication& rO)
	{
		if ((this != &rO) && rO)
		{
			m_date = rO.m_date;
			setRef(rO.m_libRef);
			Publication::set(rO.m_membership);
			strcpy(m_shelfId, rO.m_shelfId);
			delete[] m_title;
			m_title = new char[strlen(rO.m_title) + 1];
			strcpy(m_title, rO.m_title);
		}
		return *this;
	}
	// Rule of Three End
	void Publication::set(int member_id)
	{
		if (member_id < 10000 || member_id > 99999)
			m_membership = 0;
		else
			m_membership = member_id;
	}
	void Publication::setRef(int value)
	{
		m_libRef = value;
	}
	void Publication::resetDate()
	{
		m_date = Date();	
	}
	char  Publication::type()const
	{
		return 'P';
	}
	bool Publication::onLoan()const
	{
		return m_membership != 0;
	}
	Date Publication::checkoutDate()const
	{
		return m_date;
	}
	bool Publication::operator==(const char* title)const
	{
		return strstr(m_title, title);
	}
	Publication::operator const char* ()const
	{
		return m_title;
	}
	int Publication::getRef()const
	{
		return m_libRef;
	}
	bool Publication::conIO(ios& io)const
	{
		return (&io == &cout || &io == &cin); 
	}
	ostream& Publication::write(ostream& os) const
	{
		char title[TITLE_MAX]{};
		strcpy(title, m_title);
		if (conIO(os))
		{
			os << "| " << m_shelfId << " | ";
			os.setf(ios::left);
			// If string is longer than width, print up to title width
			if (strlen(m_title) > SDDS_TITLE_WIDTH)
				for (int i = 0; i < SDDS_TITLE_WIDTH; i++)
					os << title[i];
			// If not, print normally
			else
			{
				os.width(SDDS_TITLE_WIDTH);
				os.fill('.');
				os << m_title;
			}
			os.unsetf(ios::left);
			os.fill(' ');
			if (m_membership == 0)
			{
				os << " | " << " N/A " << " | ";
			}
			else
			{
				os << " | " << m_membership << " | ";
			}

			m_date.write(os);
			os << " |";
		}
		else
		{
			os << type() << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t' << m_membership << '\t';
			m_date.write(os);
			
		}
		title[0] = '\0';
		return os;
	}
	istream& Publication::read(istream& istr)
	{
		// new local variables
		char title[TITLE_MAX + 1]{};
		char shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int membership = 0;
		int libRef = 0;
		Date date;
		// check for io object
		if (conIO(istr))
		{
			cout << "Shelf No: ";
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\n');
			if (strlen(shelfId) < SDDS_SHELF_ID_LEN)
			{
				istr.setstate(ios::failbit);
			}
			cout << "Title: ";
			istr.getline(title, TITLE_MAX + 1, '\n');
			cout << "Date: ";
			istr >> date;
		}
		else
		{
			istr >> libRef;
			istr.ignore();
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.getline(title, TITLE_MAX + 1, '\t');
			istr >> membership;
			istr.ignore();
			istr >> date;
		}
		// Check for a valid Date
		if (!date)
			istr.setstate(ios::failbit);
		// Assign all values
		if (istr)
		{
			delete[] m_title;
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			strcpy(m_shelfId, shelfId);
			Publication::set(membership);
			m_date = date;
			m_libRef = libRef;
		}
		return istr;
	}
	Publication::operator bool() const
	{
		return (m_title || m_shelfId[0]);
	}
}