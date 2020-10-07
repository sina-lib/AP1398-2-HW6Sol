#include "foodCommodity.h"
#include <iostream>

//#define SAY_DEBUG_LOUD

// Constructors and Destructors --------------------------------------------------------------
Food::Food(const std::string& name, double price, double w, FOOD_MODE md) :
	BasicGoods(name, GOODS_TYPE::CONSUMABLE, price) , mode{md} , netWeight{w}
{
//	maximumTemp = 10.0;

	// setup the packing and give an appropirate Volume corresponding to the given weight
	auto dim = std::make_shared< std::array<double,3> > ();
	PACK_TYPE pck;
	switch (mode)
	{
	case FOOD_MODE::LIQUID:
	{
		pck = PACK_TYPE::CAN;
		(*dim) = std::array<double,3>( {0.3, 0.4, 0.2*netWeight} ) ;
		break;
	}
	case FOOD_MODE::CREAM:
	{
		pck = PACK_TYPE::BARREL;
		(*dim) = std::array<double,3>( {0.3, 0.4, 0.3*netWeight} );
		break;
	}
	case FOOD_MODE::SOLID:
	{
		pck = PACK_TYPE::NYLON;
		(*dim) = std::array<double,3> ( {0.3, 0.4, 0.7*netWeight}  );
		break;
	}
	}
	setAppearance(pck, dim);

	std::time_t h;
	std::time(&h);
	h += 14 * 24 * 3600;

	expirationTime = h;
	
#ifdef SAY_DEBUG_LOUD
	std::cout << "FoodCommo " << BasicGoods::getBrandName() << " created" << std::endl;
#endif
}

Food::Food(const std::string& name, double price, double Wei) :
	Food(name, price, Wei, FOOD_MODE::SOLID)
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Food Como delegated." << std::endl;
#endif
}

Food::~Food()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << this->getBrandName() << " which is a food killed" << std::endl;
#endif
}


// Operators ------------------------------------------------------------------------------
bool Food::operator< (const Food& op2)
{
	//std::cout << "Food <\n";
	std::time_t rightNow {std::time(nullptr)};

	std::time_t thisRemaining{this->expirationTime - rightNow};
	std::time_t thatRemainig{op2.expirationTime - rightNow};
	
	return (thisRemaining < thatRemainig) ? true : false;
}

bool Food::operator< (const BasicGoods& op2) const
{
	//std::cout << "food < BG\n";
	//std::cout << "pass1\n";
	const Food* u= dynamic_cast<const Food*> ( &op2);
	if (u)
	{
		//std::cout << "pass5\n";
		std::time_t rightNow {std::time(nullptr)};

		std::time_t thisRemaining{this->expirationTime - rightNow};
		std::time_t thatRemainig{u->expirationTime - rightNow};
		
		return (thisRemaining < thatRemainig) ? true : false;
	}
	return BasicGoods::operator<(op2);
}

bool Food::operator== (const BasicGoods& op2) const
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Food oper==" << std::endl;
#endif
	
	const Food* u = dynamic_cast<const Food*>(&op2);
	if (u)
	{
		// u is actually a FoodCommodity
		std::cout << "pass2\n";
		//return this->operator==(*u); //THIS WILL NOT WORK
		if (BasicGoods::privOperEq(*u))
		{
			return (this->mode == u->mode);
		}
		return false;
	}
	else
		return false; // a Bsic is not equal to a 
}

bool Food::operator== (const Food& op2)
{
	std::cout << "pass3\n";
	if (BasicGoods::privOperEq (op2))
	{
		if (this->mode == op2.mode)
			return true;
	}
	return false;
}


// Getters and Setters ---------------------------------------------------------------------
double Food::getEndPrice(void) const
{
	return basePrice * (1.0 + (taxRate-FOOD_TAX_SUBSIDE)/100.0);
}

double Food::getTaxPrice(void) const
{
	return basePrice * ( (taxRate - FOOD_TAX_SUBSIDE) / 100.0 );
}

double Food::getWeight(void) const
{
	return BasicGoods::weight +  this->netWeight;
}

void Food::setExpiration(std::time_t newT)
{
	std::time_t k = std::time(nullptr);
	if (newT >= k) expirationTime = newT;
}

std::time_t Food::getRemainingExp(void) const
{
	std::time_t now;
	std::time(&now);
	return expirationTime - now;
}

void Food::setFoodMode(FOOD_MODE md)
{
	mode = md;
}
