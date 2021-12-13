/*
Name: Mitchell Rose
Student #: 018733147
Section: NBB
Email: mjrose1@myseneca.ca
*/
#ifndef SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_
#include <iostream>
namespace sdds
{
	class Streamable
	{
	public:
		//Streamable();
		virtual ~Streamable() = 0;
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual bool conIO(std::ios& obj) const = 0;
		virtual operator bool() const = 0;

	private:

	};
	std::ostream& operator<<(std::ostream& ostr, const Streamable& rO);
	std::istream& operator>>(std::istream& istr, Streamable& rO);
}
#endif // !SDDS_STREAMABLE_H_