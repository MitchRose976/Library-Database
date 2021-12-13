/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#ifndef SDDS_BOOK_H_
#define SDDS_BOOK_H_
#include <iostream>
#include "Publication.h"
namespace sdds
{
	const int MAX_NAME_LENGTH = 256;

	class Book : public Publication
	{
	public:
		Book();
		~Book();
		Book(const Book& rO);
		Book& operator=(const Book& rO);
		char type()const;
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr);
		void set(int member_id);
		operator bool() const;


	private:
		char* m_name{};
	};

}
#endif // !SDDS_BOOK_H_

