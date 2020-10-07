#ifndef __CUSTOMER_HEADER__
#define __CUSTOMER_HEADER__
#include <string>
#include <vector>
#include <memory>
#include "basicGoods.h"
#include "foodCommodity.h"
#include  <queue>
#include "SharedComps.hpp"
#include <algorithm>



class Customer
{
protected:
	std::string name;
	double totalChargedTax;
	std::deque< std::shared_ptr<BasicGoods> > assets;
	double assetValue;

public:
	explicit Customer(const std::string& name);
	virtual ~Customer();

	virtual void importNewGoods(std::shared_ptr<BasicGoods>);
	template <class ForwIT>
		void importNewGoods(ForwIT beg, ForwIT end); // be able to copy from a range
	double getTotalAsset(void) const;
	double getTotalChargedTax(void) const;
	
	virtual bool operator==(const Customer& in) const = 0;
	virtual bool operator< (const Customer& in) const = 0;

	std::string  printBasicInfo(void) const;
			

			using sharedBG = std::shared_ptr<BasicGoods>;
    template <typename T>
	bool queueGoods(
		std::priority_queue< sharedBG, std::deque<sharedBG> , Shared_less<BasicGoods> >& Q);

	template <class T>
		void findGoods( std::deque< sharedBG >& list, T comp);

	//std::deque<std::shared_ptr<BasicGoods)
};


template <class ForwIT>
void Customer::importNewGoods(ForwIT beg, ForwIT end)
{
	while ( beg != end )
	{
		assets.push_back(*beg);
		assetValue += (*beg)->getEndPrice();
		totalChargedTax += (*beg)->getTaxPrice();
		beg++;
	}
}

template <class T>
bool Customer::queueGoods(
	std::priority_queue< sharedBG , std::deque<sharedBG>, Shared_less<BasicGoods> >& Q )
{
	for (auto& item: assets)
	{
		T* u = dynamic_cast<T*> (item.get());
		if (u)
		{
			Q.push(item);
		}
	}
	return Q.empty();
}


template <class T>
void Customer::findGoods(std::deque<sharedBG>& inQ, T comp)
{
	std::copy_if(assets.begin(), assets.end(), std::back_inserter(inQ), comp);
}
#endif // __CUSTOMER_HEADER__
