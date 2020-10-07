#ifndef __MATERIAL_HEADER__
#define __MATERIAL_HEADER__

#include "basicGoods.h"

enum class MAT_TYPE
{ NORMAL, FLAMABLE, HAZARDOUS };


class Material : public virtual BasicGoods
{
protected:
	MAT_TYPE matType;
	double weight;
	
public:
	Material(const std::string& name, double price , double weight, MAT_TYPE mt);
	Material(const std::string& name, double price , double weight);
	~Material();

	constexpr static double MATERIAL_TAX = 1.5;
	
	// getters
	double getWeight(void) const;
	double getEndPrice(void) const;
	double getTaxPrice(void) const;

	// operators
	bool operator== (const Material& in);
	bool operator== (const BasicGoods& in);
	
	// misc
	virtual void doTriv(void) ;
};

#endif // __MATERIAL_HEADER__
