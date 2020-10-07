#ifndef __FOOD_COMMODITY_HEADER__
#define __FOOD_COMMODITY_HEADER__
#include "basicGoods.h"
#include <ctime>



enum class FOOD_MODE
{
	LIQUID, CREAM, SOLID, 
};
	
class Food: public BasicGoods
{
private:
	FOOD_MODE mode;
	double netWeight;
	std::time_t expirationTime;
	
public:
	constexpr static double FOOD_TAX_SUBSIDE = 3;

	
	Food(const std::string& name, double price, double Wei); // mode is SOLID
	Food(const std::string& name, double price, double Wei, FOOD_MODE md);
	~Food();


    // getters
	double getEndPrice(void) const;
	double getTaxPrice(void) const override;
	double getWeight(void) const;
	std::time_t getRemainingExp(void) const;

	// setters
	void setExpiration(std::time_t t);
	void setFoodMode(FOOD_MODE md);

	// operators
	bool operator< (const Food& op2);
	bool operator< (const BasicGoods& op2) const override;
	bool operator== (const Food& op2); // Base + FoodMode + 
	bool operator== (const BasicGoods& op2) const override;
};

#endif // __FOOD_COMMODITY_HEADER__
