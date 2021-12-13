/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
	// Menu Item
	MenuItem::MenuItem()
	{

	}
	MenuItem::MenuItem(const char* name)
	{
		if (name && name[0])
		{
			delete[] m_itemName;
			m_itemName = new char[strlen(name) + 1];
			strcpy(m_itemName, name);
		}
		else
		{
			delete[] m_itemName;
			setEmpty();
		}
	}
	MenuItem::~MenuItem()
	{
		delete[] m_itemName;
	}
	// Sets to safe empty state
	void MenuItem::setEmpty()
	{
		m_itemName = nullptr;
	}
	MenuItem::operator bool()const
	{
		return (m_itemName && m_itemName[0]);
	}
	MenuItem::operator char* ()const
	{
		return m_itemName;
	}
	std::ostream& MenuItem::display(std::ostream& ostr)const
	{
		if (this)
		{
			ostr << m_itemName;
		}
		return ostr;
	}

	// Menu
	Menu::Menu()
	{
		m_numMenuItems = 0;
	}
	Menu::Menu(const char* name)
	{
		m_numMenuItems = 0;
		if (name)
		{
			delete[] m_name.m_itemName;
			m_name.m_itemName = new char[strlen(name) + 1];
			strcpy(m_name.m_itemName, name);
		}
		else
		{
			delete[] m_name.m_itemName;
			m_name.m_itemName = nullptr;
		}
	}
	Menu::~Menu()
	{
		for (int i = 0; i < m_numMenuItems; i++)
		{
			delete m_items[i];
		}
	}
	void Menu::displayTitle(std::ostream& ostr) const
	{
		if (m_name.m_itemName && m_name.m_itemName[0])
		{
			ostr << m_name.m_itemName;
		}
	}
	void Menu::displayMenu()const
	{
		displayTitle(cout);
		/*if (m_name.m_itemName && m_name.m_itemName[0])
		{
			cout << ":" << endl;
		}*/
		cout << endl;
		cout.setf(ios::right);
		for (int i = 0; i < m_numMenuItems; i++)
		{
			cout.width(2);
			cout << (i + 1) << "- " << m_items[i]->m_itemName << endl;
		}
		cout.width(2);
		cout << " 0- Exit" << endl;
		cout.unsetf(ios::right);
	}
	unsigned int Menu::run()const
	{
		unsigned int userSelection = 0;
		if (!cin)
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		displayMenu();
		cout << "> ";
		cin >> userSelection;
		while (!cin || (userSelection < 0 || userSelection >(unsigned)m_numMenuItems))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Selection, try again: ";
			cin >> userSelection;
		}
		cin.ignore(1000, '\n'); // May not need
		return userSelection;
	}
	unsigned int Menu::operator~()
	{
		unsigned int userSelection = 0;
		if (!cin)
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		displayMenu();
		cout << "> ";
		cin >> userSelection;
		while (userSelection < 0 || userSelection >(unsigned)m_numMenuItems)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Selection, try again: ";
			cin >> userSelection;
		}
		return userSelection;
	}
	Menu& Menu::operator<<(const char* menuitemConent)
	{
		if (m_numMenuItems < MAX_MENU_ITEMS)
		{
			MenuItem* newItem = new MenuItem(menuitemConent);
			m_items[m_numMenuItems++] = newItem;
		}
		return *this;
	}
	Menu::operator int()
	{
		return m_numMenuItems;
	}
	Menu::operator unsigned int()
	{
		return m_numMenuItems;
	}
	Menu::operator bool()
	{
		return m_numMenuItems > 0;
	}
	const char* Menu::operator[] (int num) const
	{
		return m_items[num % m_numMenuItems]->m_itemName;
	}
	void Menu::setName(const char* name)
	{
		if (name && name[0])
		{
			delete[] m_name.m_itemName;
			m_name.m_itemName = new char[strlen(name) + 1];
			strcpy(m_name.m_itemName, name);
		}
		else
		{
			delete[] m_name.m_itemName;
			m_name.m_itemName = nullptr;
		}
	}
	std::ostream& operator<<(std::ostream& ostr, Menu& rightMenu)
	{
		rightMenu.displayTitle(ostr);
		return ostr;
	}

}