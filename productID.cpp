#include "productID.h"
#include <iostream>

//#define SAY_DEBUG_LOUD

productID::productID(std::shared_ptr< std::string >& conf , const std::string& ss) :
	standardSerial{ss}, confirmStatement{conf}, countryName{}
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "created a proID with statement: " << *conf << std::endl;
#endif
}


productID::~productID()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "kiling a product ID" << std::endl;
#endif
}

void productID::printStatement(void) const
{
	std::cout << "\033[35mLegal Confirmation Statement: [";
	std::cout << *confirmStatement << "] ";
	std::cout << "producer country: " << countryName;
	std::cout << "\033[m\n";
}


std::ostream& operator<< (std::ostream& os, const productID& i)
{
	//os << "\033[35mLegal Confirmation Statement : [" << *(i.confirmStatement) << "]\n"
	os << "Legal Confirmation Statement: [" << *(i.confirmStatement) << "]" << std::endl;
	os << "producer country: " << i.countryName << " , serial number: " << i.standardSerial << std::endl;
	
	return os;
}
