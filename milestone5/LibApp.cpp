/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "LibApp.h"
#include "Book.h"
#include "Menu.h"
#include "PublicationSelector.h"
#include <iomanip>
using namespace std;
namespace sdds
{
	// Public Methods
	LibApp::LibApp(const char* name):
		m_pubTypeMenu("Choose the type of publication:"),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_changed = false;
		strcpy(m_dataFileName, name);
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		m_pubTypeMenu << "Book" << "Publication";
		m_LLRN = 0;
		m_NOLP = 0;
		load(m_dataFileName);
	}
	LibApp::~LibApp()
	{
		for (int i = 0; i < m_NOLP; i++)
		{
			delete m_PPA[i];
		}
	}
	void LibApp::run()
	{
		unsigned int userSelection = 0;
		do
		{
			userSelection = m_mainMenu.run();
			switch (userSelection)
			{
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			case 0:
				if (m_changed)
				{
					userSelection = m_exitMenu.run();
					switch (userSelection)
					{
					case 1:
						save(m_dataFileName);
						userSelection = 0;
						cout << endl << "-------------------------------------------" << endl;
						cout << "Thanks for using Seneca Library Application";
						break;
					case 2:
						userSelection = 1;
						break;
					case 0:
						if (confirm("This will discard all the changes are you sure?"))
						{
							cout << endl << "-------------------------------------------" << endl;
							cout << "Thanks for using Seneca Library Application";
							break;
						}
						else
							userSelection = 1;
					default:
						break;
					}
				}
				else
				{
					cout << "\n-------------------------------------------" << endl;
					cout << "Thanks for using Seneca Library Application" << endl;
				}
			}
			cout << endl;
		} while (userSelection);

	};

	Publication* LibApp::getPub(int libRef)
	{
		Publication* reference{};
		for (int i = 0; !reference && i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() == libRef)
				reference = m_PPA[i];
		}
		return reference;
	}

	// Private Methods
	bool LibApp::confirm(const char* message)
	{
		Menu newMenu(message);
		newMenu << "Yes";
		return newMenu.run() == 1;
	}
	void LibApp::load(const char* filename)
	{
		cout << "Loading Data" << endl;
		ifstream fileIn(filename); // Switch to m_dataFileName
		int i;
		// Holds the type of the Publication 'P' or 'B'
		char type{};
		// Read file
		for (i = 0; fileIn; i++)
		{
			fileIn >> type;
			fileIn.ignore();
			if (type == 'P')
				m_PPA[i] = new Publication;
			else if (type == 'B')
				m_PPA[i] = new Book;
			if (type == 'P' || type == 'B')
			{
				fileIn >> *m_PPA[i];
				m_LLRN = m_PPA[i]->getRef();
				m_NOLP++;
				type = {};
			}
		}
	}
	void LibApp::save(const char* filename)
	{
		cout << "Saving Data" << endl;
		ofstream file(filename);
		for (int i = 0; i < m_NOLP; i++)
		{
			if (m_PPA[i]->getRef() != 0)
			{
				file << *m_PPA[i] << endl;
			}
		}
		file.close();
	}
	int LibApp::search(bool checkedOut, bool onLoan)
	{
		// Make a temp PubSel to collect search matches and user selection and other temp variables
		PublicationSelector results("Select one of the following found matches:");
		char title[256]{};
		int choice = 0;
		char type{};
		//Run menu and get user selection
		choice = m_pubTypeMenu.run();
		choice == 1 ? type = 'B' : type = 'P';
		if (choice)
		{
			// Get title to search for from user
			cout << "Publication Title: ";
			cin.getline(title, 256, '\n');
			// 1. Show all
			if (checkedOut && onLoan)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					// if correct type and contains title, add to results
					if (m_PPA[i]->type() == type && strstr(*m_PPA[i], title))
						results << m_PPA[i];
				}
				if (results)
				{
					// Sort by date and title
					results.sort();
					int pubSelect = results.run();
					if (pubSelect)
						return pubSelect;
					else
						cout << "Aborted!" << endl;
				}
				else
				{
					cout << "No matches found!" << endl;
				}
			}
			// 2. Show all available
			else if (checkedOut)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (m_PPA[i]->type() == type && strstr(*m_PPA[i], title))
					{
						// Check if available in the library
						if (!(m_PPA[i]->onLoan()))
							results << m_PPA[i];
					}
				}
				if (results)
				{
					// Sort by date and title
					results.sort();
					int pubSelect = results.run();
					if (pubSelect)
						return pubSelect;
					else
						cout << "Aborted!" << endl;
				}
				else
				{
					cout << "No matches found!" << endl;
				}
			}
			// Show everything on Loan or unavailable
			else if (onLoan)
			{
				for (int i = 0; i < m_NOLP; i++)
				{
					if (m_PPA[i]->type() == type && strstr(*m_PPA[i], title))
					{
						// Check if available in the library
						if (m_PPA[i]->onLoan())
							results << m_PPA[i];
					}
				}
				if (results)
				{
					// Sort by date and title
					results.sort();
					int pubSelect = results.run();
					if (pubSelect)
						return pubSelect;
					else
						cout << "Aborted!" << endl;
				}
				else
				{
					cout << "No matches found!" << endl;
				}
			}
		}
		return 0;
	}
	void LibApp::returnPub()
	{
		int selection;
		cout << "Return publication to the library" << endl;
		// Search pubs on loan
		selection = search(false, true);
		if (selection)
		{
			cout << *getPub(selection) << endl;
			if (confirm("Return Publication?"))
			{
				Date today;
				double amountDue;
				int days = (today - getPub(selection)->checkoutDate());
				// If more than 15 days on loan, calculate late fee
				if (days > 15)
				{
					amountDue = (days - 15) * 0.5;
					cout << "Please pay $" << setprecision(2) << fixed << amountDue << " penalty for being " << (days - 15) << " days late!" << endl;
				}
				// set membership number to 0
				getPub(selection)->set(0);
			}
			cout << "Publication returned" << endl;
			m_changed = true;
		}
	}
	void LibApp::newPublication()
	{
		if (m_NOLP == SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl;
			return;
		}
		else
		{
			cout << "Adding new publication to the library" << endl;
			int type = m_pubTypeMenu.run();
			// if user wants to add a Book
			if (type)
			{
				// Make a new Publication
				Publication* newPub{};
				if (type == 1)
					newPub = new Book;
				else if (type == 2)
					newPub = new Publication;
				else if (type == 0)
					return;
				// Read data in to newPub
				cin >> *newPub;
				// If cin fails, flush keyboard
				if (!cin)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Aborted!" << endl;
					return;
				}
				else
				{
					if (confirm("Add this publication to the library?"))
					{
						if (*newPub)
						{
							newPub->setRef(++m_LLRN);
							m_PPA[m_NOLP] = newPub;
							m_NOLP++;
							m_changed = true;
							cout << "Publication added" << endl;
						}
						else
						{
							delete newPub;
							cout << "Failed to add publication!" << endl;
						}
					}
					else
					{
						cout << "Aborted!" << endl;
					}
				}
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
	};

	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		//search all the publications to be added
		int selection = search(true, true);
		if (selection)
		{
			cout << *getPub(selection) << endl;
			if (confirm("Remove this publication from the library?"))
			{
				// Set ref of pub to 0
				getPub(selection)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
	}
	void LibApp::checkOutPub()
	{
		int selection;
		cout << "Checkout publication from the library" << endl;
		// Search available publications only
		selection = search(true, false);
		if (selection)
		{
			// Get a 5 digit number
			cout << *getPub(selection) << endl;
			if (confirm("Check out publication?"))
			{
				int memberNum;
				cout << "Enter Membership number: ";
				cin >> memberNum;
				while (!cin || (memberNum < 10000 || memberNum > 99999))
				{
					if (!cin)
					{
						cin.clear();
						cin.ignore(1000, '\n');
					}
					cout << "Invalid membership number, try again: ";
					cin >> memberNum;
					cin.ignore();
				}
				// Set memberNum
				getPub(selection)->set(memberNum);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
	}
}