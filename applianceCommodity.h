#ifndef __APPLIANCE_COMMODITY_HEADER__
#define __APPLIANCE_COMMODITY_HEADER__
#include "basicGoods.h"

enum class ENERGY_COST
{ IRRELEVANT, LOW, MEDIUM, HIGH };


//class Appliance : protected virtual BasicGoods
class Appliance : public virtual BasicGoods
{
protected:
	double weight;
	ENERGY_COST energyGrade;
	double getEndPrice(void) const override;
	
public:
	
	Appliance(const std::string& name, double price, double Wei);
	~Appliance();


	constexpr static double APPLIANCE_EXTRA_TAX_HIGH = 17;
	constexpr static double APPLIANCE_EXTRA_TAX_MEDIUM = 7;
	// functions

	using BasicGoods::setNewPrice;
	using BasicGoods::approxDim;
	
    // getter and setters
	double getWeight() const override;
	double getTaxPrice() const;
	void setWeight(double w);
	void setEnergyGrade(ENERGY_COST ec);

	// operators
	bool operator== (const Appliance& in) const;

	// misc
	virtual void doTriv(void) override;
};


#endif // __APPLIANCE_COMMODITY_HEADER__
