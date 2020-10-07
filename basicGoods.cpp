#include "basicGoods.h"
#include <iostream>

//#define SAY_DEBUG_LOUD

// Constructors and Destructors: ------------------------------------------------------
BasicGoods::BasicGoods(const std::string& name, GOODS_TYPE gt, double prc) :
	goodsType{gt}, basePrice{prc} , taxRate{INITIAL_TAX_RATE},packing{PACK_TYPE::UNKNOWN} , weight{0.1}
{
	
	auto ni = name.cbegin();
	char* u = new char[name.length()+1];
	brandName = u;
	while (ni != name.cend())
	{
		*u++ = *ni++;
	}
	*u='\0';
	originCountry = nullptr;
	//traderCompanyName = nullptr;

#ifdef SAY_DEBUG_LOUD
	std::cout << "Basic Goods created, name : " << brandName << std::endl;
#endif
}

/*BasicGoods::BasicGoods()
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Basic Goods default constructor created" << std::endl;
#endif
	brandName = nullptr;
	originCountry = nullptr;
	//traderCompanyName = nullptr;
	}*/

BasicGoods::~BasicGoods()
{
#ifdef SAY_DEBUG_LOUD
	if (brandName == nullptr || *brandName == '\0')
		std::cout << "\033[41m!!!!!!!!!! basicGodds is being killed while empty brandName!!!!!\033[m" << std::endl;
	else
		std::cout << "basicGoods " << brandName << " killed" << std::endl;
#endif
	
	delete[] brandName;
	delete[] originCountry;
	//delete[] traderCompanyName;
}

// functions ------------------------------------------------------------------------
double BasicGoods::getEndPrice(void) const
{
	return basePrice * ( (taxRate/100.0) + 1.0 );
}

// Getters: -------------------------------------------------------------------------
double BasicGoods::getTaxPrice(void) const
{
	return basePrice * (taxRate/100.0);
}

std::string BasicGoods::getBrandName() 
{
	return std::string(brandName);
}

double BasicGoods::getWeight(void) const
{
	return this->weight;
}

double BasicGoods::getVolume(void) const
{
	double volume {};
	if (approxDim)
		volume = ((*approxDim)[0])  *  ((*approxDim)[1])  *  ((*approxDim)[2]);
	return volume;
}

std::string BasicGoods::getOriginCountry(void) const
{
	if (originCountry)
		return std::string(originCountry);
	else
		return std::string("unknown country");
}
// Setters: -----------------------------------------------------------------------
/*void BasicGoods::setTraderCompanyName(const std::string& trd)
{
	char* cp;
	cp = traderCompanyName = new char[trd.length()];
	auto h = trd.cbegin();
	while (h != trd.cend()) *cp++ = *h++;
	*cp = '\0';
}*/

void BasicGoods::setOriginCountry(const std::string& country)
{
	if (originCountry) delete[] originCountry;

	char* u = originCountry = new char[(country.length()+1)];
	auto it = country.cbegin();
	while (it != country.cend())
	{
		*u++ = *it++;
	}
	*u='\0';
	std::cout << "\033[33mSETTING ORIGIN COUNTRY: " << originCountry << " @\033[m" << std::endl;
}

void BasicGoods::setNewPrice(double price)
{
	basePrice = price;
}

void BasicGoods::setAppearance(PACK_TYPE pck, std::shared_ptr< std::array<double,3> > dimen)
{
	packing = pck;
	approxDim = dimen;
}


bool BasicGoods::privOperEq(const BasicGoods& secondary) const
{
	if (  (std::string(brandName) == std::string(secondary.brandName) ) &&
		  (this->goodsType == secondary.goodsType) &&
		  (this->basePrice == secondary.basePrice)     )
		return true;
	return false;
}

// operator
bool BasicGoods::operator== (const BasicGoods& secondary) const
{
#ifdef SAY_DEBUG_LOUD
	std::cout << "Basic oper== \n\n" ;
#endif
	if (secondary.getEndPrice() != (basePrice * (taxRate/100.0 + 1.0)) ) return false;
	if (  (std::string(brandName) == std::string(secondary.brandName) ) &&
		  (this->goodsType == secondary.goodsType) &&
		  (this->basePrice == secondary.basePrice)     )
		return true;
	return false;
}

bool BasicGoods::operator< (const BasicGoods& op2) const
{
	return (this->getEndPrice()) < (op2.getEndPrice());
}


void BasicGoods::doTriv(void)
{
	std::cout << "Basic DO triv\n";
}
