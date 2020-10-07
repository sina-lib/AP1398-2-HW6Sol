#ifndef __PRODUCT_HEADER__
#define __PRODUCT_HEADER__

#include "material.h"
#include "applianceCommodity.h"
#include "productID.h"
#include <string>
#include <memory>

using shared_str = std::shared_ptr<std::string>;


class Product: public Material, public Appliance, public productID
{
private:
	double taxRate;
	
	
public:
	Product(const std::string& brandName, double price, double matWei, shared_str confirmation);
	~Product();

	constexpr static double TYPICAL_TAX_RATE = 23;
	//void setFeatures(ENERGY_COST ec, MAT_TYPE mt, double appWei);
	
	double getWeight(void) const;
	double getEndPrice(void) const override final;
	//using namespace Appliance;// getEndPrice ;
	//using Material::getEndPrice;
	double getTaxPrice(void) const override final;
	void setTaxRate(double newTax);

	void setOriginCountry(const std::string& cnt);


	// misc
	//void doTriv(void) final;
	void doTriv() final;// : Appliance::doTriv() { ; };
	//using doTrive = Appliance::doTriv();
};

#endif // __PRODUCT_HEADER__
