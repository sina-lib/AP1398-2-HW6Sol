#include "legalCustomer.h"
#include <iostream>


//#define SAY_DEBUG_LOUD

LegalCustomer::LegalCustomer(const std::string& corrName, const std::string& compName) :
	Customer(corrName) , companyName(compName)
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Legal Customer " << name << " created " << std::endl;
#endif
}

LegalCustomer::~LegalCustomer()
{
#ifdef SAY_DEBIG_LOUD
	std::cout << "Legal Customer " << name << " killed" << std::endl;
#endif
}


/*void LegalCustomer::importNewGoods(std::shared_ptr<BasicGoods> newGoods)
{
	assets.push_back(newGoods);
	assetValue += newGoods->getEndPrice();
}*/


 /*double LegalCustomer::getTotalAsset() const
{
	return assetValue;
	}*/

bool LegalCustomer::operator==(const Customer& in) const
{
	if (this == &in) return true;

	const LegalCustomer* u = dynamic_cast<const LegalCustomer*> (&in);
	if (u)
	{
		if ( (this->name == u->name) && (this->companyName == u->companyName) )
			return true;
	}
	return false;
}

bool LegalCustomer::operator< (const Customer& in) const
{
	// given input can be a RealCustomer
	
	if (this->operator== (in) )
		return false;
	else
	{
		const LegalCustomer* u = dynamic_cast<const LegalCustomer*> (&in);
		if (u)
		{
			return this->name < u->name;
		}
		else
			return true;
	}
}

bool LegalCustomer::operator< ( const LegalCustomer& op2) const
{
	// given input is LegalCustomer
	if ( this->operator== (op2))
		 return false;
	
	 return this->name < op2.name;
}
