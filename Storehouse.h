#ifndef __STOREHOUSE_HEADER__
#define __STOREHOUSE_HEADER__
#include <vector>
#include "basicGoods.h"
#include <set>
#include "customer.h"
#include <string>
#include "SharedComps.hpp"

template <>
struct Shared_less<Customer>
{
	bool operator() (const std::shared_ptr<Customer>& a, const std::shared_ptr<Customer>& b)
	{
		return a->operator< ( *b );
	}
};

class Storehouse
{
private:
	std::string storeName;

	//std::set< std::shared_ptr<Customer> > theCustomers;
	std::set< std::shared_ptr<Customer> , Shared_less<Customer> > theCustomers;
	
public:
	explicit Storehouse(const std::string& name);
	Storehouse();
	~Storehouse();

	void newCustomer(std::shared_ptr<Customer> newC);
	std::string printCustomers(void) const;
};



#endif // __STOREHOUSE_HEADER__
