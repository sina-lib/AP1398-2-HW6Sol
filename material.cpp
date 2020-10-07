#include "material.h"
#include <iostream>


//#define SAY_DEBUG_LOUD


// Constrcutors and destructors -------------------------------------------
Material::Material(const std::string& name, double price, double wei, MAT_TYPE mt) :
	BasicGoods(name, GOODS_TYPE::CONSUMABLE, price) , matType{mt}
{
	Material::weight = wei;
	//std::cout << "Material weight: " << Material::weight<<std::endl; 
#ifdef SAY_DEBUG_LOUD
	std::cout << "Material created : " << name << std::endl;
#endif	
}

Material::Material(const std::string& name, double price, double weight):
	Material(name, price, weight, MAT_TYPE::NORMAL)
{
	;
};


Material::~Material()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Material killed" << std::endl;
#endif
}

// Getters -----------------------------------

double Material::getWeight(void) const
{
	return Material::weight + BasicGoods::weight;
}

double Material::getEndPrice(void) const
{
	return basePrice * ( 1.0 +  (taxRate + MATERIAL_TAX)/100.0 ) ;
}

double Material::getTaxPrice(void) const
{
	return basePrice * ( (taxRate + MATERIAL_TAX)/100.0 ) ;
}

bool Material::operator== (const Material& op)
{
	if (BasicGoods::privOperEq(op) && this->weight == op.weight)
	{
		std::cout << "This : " << Material::weight << " That : " << op.weight << std::endl;
		return true;
	}
	return false;
}

bool Material::operator== (const BasicGoods& op)
{
	const Material* u = dynamic_cast<const Material*>(&op);
	if (u)
	{
		if (BasicGoods::privOperEq(op) && u->weight == this->weight)
			return true;
	}
	return false;
}

void Material::doTriv(void)
{
	std::cout << "MATERIAL do triv\n" ;
}
