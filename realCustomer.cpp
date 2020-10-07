#include "realCustomer.h"
#include <iostream>


//#define SAY_DEBUG_LOUD

RealCustomer::RealCustomer(const std::string& name) :
	Customer(name)
{
	nationalID = 0;
#ifdef SAY_DEBUG_LOUD
	std::cout << "creating a real customer " << name << std::endl;
#endif
}

RealCustomer::RealCustomer(const std::string& name, long int nid):
	RealCustomer(name)
{
	nationalID = nid;
#ifdef SAY_DEBUG_LOUD
	std::cout << name << " >> NatID: " << nid << std::endl;
#endif
}

RealCustomer::~RealCustomer()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "a real customer " << name << " killed" << std::endl;
#endif
}


// =======================================================================================

/*void RealCustomer::importNewGoods(std::shared_ptr<BasicGoods> gd)
{
	assets.push_back(gd);
	assetValue += gd->getEndPrice();
	}*/

 //double RealCustomer::getTotalAsset(void) const
 //{
	//double res{};
	//for (auto h: assets) res+=h->getEndPrice();

 //	return assetValue;
 //}

bool RealCustomer::operator== (const Customer& in ) const
{
	if (this == &in) return true;
	
	const RealCustomer* u = dynamic_cast<const RealCustomer*> (&in);
	if (u)
	{
		if ( (u->name == this->name) && (u->nationalID == this->nationalID) )
		{
			// maybe check the assets too?
			return true;
		}
	}
	
	return false;
}

bool RealCustomer::operator< (const Customer& in) const
{
	// given input can be  a LegalCustomer
	if (this->operator== (in))
		return false;
	else
	{
		const RealCustomer* u = dynamic_cast<const RealCustomer*> (&in);
		if (u)
			return this->name < u->name;
		else
			return true;
	}
}

bool RealCustomer::operator< (const RealCustomer& in) const
{
	if (this->operator== (in) )
		return false;
	return this->name < in.name;
}
