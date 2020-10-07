#include "applianceCommodity.h"
#include <iostream>

//#define SAY_DEBUG_LOUD


Appliance::Appliance(const std::string& name, double price, double Wei) :
	BasicGoods(name,GOODS_TYPE::OBJECT, price), weight{Wei}
{
#ifdef SAY_DEBUG_LOUD
	std::cout << name << " appliance made." << std::endl;
#endif
	energyGrade = ENERGY_COST::LOW;
}

Appliance::~Appliance()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "an appliance killed" << std::endl;
#endif
}



// Getters and setters -------------------------------------------------
double Appliance::getEndPrice(void) const
{
	if (energyGrade == ENERGY_COST::HIGH)
		return (basePrice * ( 1.0 + (taxRate+APPLIANCE_EXTRA_TAX_HIGH) / 100.0));
	else
		return basePrice * (1.0 + (taxRate+APPLIANCE_EXTRA_TAX_MEDIUM)/100.0);
}

double Appliance::getWeight(void) const
{
	return BasicGoods::weight + this->weight;
}

double Appliance::getTaxPrice(void) const
{
	if (energyGrade == ENERGY_COST::HIGH)
		return (basePrice * (  (taxRate+APPLIANCE_EXTRA_TAX_HIGH) / 100.0));
	else
		return basePrice * ( (taxRate+APPLIANCE_EXTRA_TAX_MEDIUM)/100.0);
}

void Appliance::setWeight(double w)
{
	weight = w;
}

void Appliance::setEnergyGrade(ENERGY_COST e)
{
	energyGrade = e;
}

bool Appliance::operator== (const Appliance& sec) const
{
	if (BasicGoods::privOperEq(sec))
	{
		if ( (this->energyGrade == sec.energyGrade) &&
			 (this->weight == sec.weight)                     )
			return true;
	}
	
	return false;
}

void Appliance::doTriv(void)
{
	std::cout << "APPLIANCE DO triv\n" ;
}
