#include "product.h"
#include <iostream>

//#define SAY_DEBUG_LOUD

// Constructors -------------------------------------------------------------------------------
Product::Product(const std::string& bn, double price, double matWei, shared_str confir):
	BasicGoods(bn, GOODS_TYPE::OBJECT, price), Material(bn, price, matWei), Appliance(bn, price, 0.3) ,
	productID(confir), taxRate{TYPICAL_TAX_RATE} 
{
	countryName = getOriginCountry();
	std::array<double,3> V { 0.5, 0.8, 1.2 * (1+matWei)};
	approxDim = std::make_shared<std::array<double,3>>(V);
	packing = PACK_TYPE::CARTON;
#ifdef SAY_DEBUG_LOUD
	std::cout << "product successfuly create " << bn << std::endl;
#endif
}

// Destructors --------------------------------------------------------------------------------
Product::~Product()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Product destructed " << std::endl;
#endif
}


// Getteres and Setters -----------------------------------------------------------------------
double Product::getWeight(void) const
{
	return Appliance::weight + BasicGoods::weight + Material::weight;
}

double Product::getEndPrice(void) const
{
	if (energyGrade == ENERGY_COST::HIGH) 
		return basePrice * (1.0 + (taxRate + APPLIANCE_EXTRA_TAX_HIGH)/100);
	else
		return basePrice * (1.0 + (taxRate + APPLIANCE_EXTRA_TAX_MEDIUM)/100);
		}

void Product::setTaxRate(double tr)
{
	taxRate = tr;
}

	
double Product::getTaxPrice(void) const
{
	if (energyGrade == ENERGY_COST::HIGH)
		return basePrice * ( (taxRate + APPLIANCE_EXTRA_TAX_HIGH) / 100.0 );
	else
		return basePrice * ( (taxRate + APPLIANCE_EXTRA_TAX_MEDIUM) / 100.0);
}


void Product::setOriginCountry(const std::string& cnt)
{
	BasicGoods::setOriginCountry(cnt);
	countryName = cnt;
}

void Product::doTriv(void)// : Appliance::doTriv()
//{ std::cout << "PRODU do triv\n" ; }
{
	Appliance::doTriv();
}
