/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>
namespace sdds
{
	const int MAX_MENU_ITEMS = 20; 

	class Menu;

	class MenuItem
	{
		friend class Menu;
	private:
		MenuItem();
		MenuItem(const char* name);
		~MenuItem();
		char* m_itemName{}; 
		void setEmpty();
		operator bool()const;
		operator char* ()const; 
		std::ostream& display(std::ostream& ostr)const;
	};

	class Menu
	{
	public:
		Menu();
		Menu(const char* name);
		~Menu();
		void displayTitle(std::ostream& ostr) const;
		void displayMenu()const;
		unsigned int run() const;
		unsigned int operator~();
		Menu& operator<<(const char* menuitemConent);
		operator int();
		operator unsigned int();
		operator bool();
		const char* operator[](int num) const;
		void setName(const char* name);

	private:
		MenuItem m_name = nullptr;
		MenuItem* m_items[MAX_MENU_ITEMS]{};
		int m_numMenuItems;
	};

	std::ostream& operator<<(std::ostream& ostr, Menu& rightMenu);

}
#endif // !SDDS_MENU_H_
