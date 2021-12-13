/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#ifndef SDDS_LIBAPP_H_
#define SDDS_LIBAPP_H_
#include "Menu.h"
#include "Publication.h"
namespace sdds
{
	const int DATA_FILENAME_MAX = 256;

	class LibApp
	{
	public:
		LibApp(const char* name);
		~LibApp();
		void run();

	private:
		bool m_changed{};
		Menu m_pubTypeMenu;
		Menu m_mainMenu;
		Menu m_exitMenu;
		char m_dataFileName[DATA_FILENAME_MAX]{}; // Can use as filename in load
		Publication* m_PPA[SDDS_LIBRARY_CAPACITY]{}; // Instantiate with all records of publication data file 
		int m_NOLP{}; // Holds size of m_PA
		int m_LLRN{}; // Add +1 every time pub is added so they all have unique ref. nums

		bool confirm(const char* message);
		void load(const char* filename);  // prints: "Loading Data"<NEWLINE>
		void save(const char* filename);  // prints: "Saving Data"<NEWLINE>
		int search(bool checkedOut = false, bool onLoan = false);  // prints: "Searching for publication"<NEWLINE>

		void returnPub();  /*  Calls the search() method.
							   prints "Returning publication"<NEWLINE>
							   prints "Publication returned"<NEWLINE>
							   sets m_changed to true;
						   */
		void newPublication();
		void removePublication();
		void checkOutPub();
		Publication* getPub(int libRef);

	};
}
#endif // !SDDS_LIBAPP_H_

