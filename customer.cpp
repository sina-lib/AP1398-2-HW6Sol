#include "customer.h"
#include <iostream>
#include <sstream>

//#define SAY_DEBUG_LOUD

Customer::Customer(const std::string& n):
	name{n} , totalChargedTax{0}, assetValue{0}
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Customer " << n << " created"  << std::endl;
#endif
}

Customer::~Customer()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Customer " << name << " killed" << std::endl;
#endif
}


/*bool Customer::operator< (const Customer& op2)
{
	if (this->operator==(op2)) return false;
	//if (this->assetValue != op2.assetValue)
	//	return this->assetValue < op2.assetValue;
	//else
		return this->name < op2.name;
		}*/

std::string Customer::printBasicInfo(void) const
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "\033[33m" << name << " total asset: " << assetValue << "\033[m" << std::endl;
#endif
	std::ostringstream k{};
	k << name << " >> No of assets: " << assets.size() << ", Total Asset: " << assetValue << ", Charged Tax: " << totalChargedTax;
	return std::string(k.str());
}

void Customer::importNewGoods(std::shared_ptr<BasicGoods> ng)
{
	assets.push_back(ng);
	assetValue += ng->getEndPrice();
	totalChargedTax += ng->getTaxPrice();
}

double Customer::getTotalAsset(void) const
{
	return assetValue;
}

double Customer::getTotalChargedTax(void) const
{
	return totalChargedTax;
}
