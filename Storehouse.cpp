#include "Storehouse.h"
#include <iostream>
#include "realCustomer.h"
#include "legalCustomer.h"

//#define SAY_DEBUG_LOUD



// --------------------------------------------------------------------------------------

Storehouse::Storehouse(const std::string& name) :
	storeName{name}
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Storehouse " << name << " created " << std::endl;
#endif
}

Storehouse::Storehouse() : Storehouse("default strorehouse")
{
}

Storehouse::~Storehouse()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Storehouse " << storeName << " killed" << std::endl;
#endif
}

void Storehouse::newCustomer(std::shared_ptr<Customer> newC)
{
	auto res = theCustomers.insert(newC);
	if (res.second)
	{
		std::cout << "successfully added new customer" << std::endl;
	}
	else
	{
		std::cout << "Duplicate customer" << std::endl;
#ifdef SAY_DEBUG_LOUD
		std::cout << "In the set there is: " << std::endl;
		std::cout <<  (  (*res.first)->printBasicInfo()  );
		std::cout << "input:\n" ;
		std::cout << (   newC->printBasicInfo()  );
		std::cout << "----------------\n";
#endif
		/*
		  for item in newC.asset
		res.first->importNewCustomer();
		*/
	}
}

// PRINTERS ------------------------------------------------
std::string Storehouse::printCustomers(void) const
{
	std::string result;
	for (auto p: theCustomers)
	{
		//p->printBasicInfo();
		RealCustomer* u = dynamic_cast<RealCustomer*> (p.get());
		if (u)
		{
			//std::cout << "Real" <<std::endl;
			result += std::string("Real: ") + u->printBasicInfo();
		}
		else
		{
			//std::cout << "Legal" << std::endl;
			result += std::string("Legal: ") + p->printBasicInfo();
		}
		result += "\n";
	}
	return result;
}
