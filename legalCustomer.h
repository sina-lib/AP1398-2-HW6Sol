#ifndef __LEGAL_CUSTOMER_HEADER__
#define __LEGAL_CUSTOMER_HEADER__
#include "customer.h"

class LegalCustomer : public Customer
{
private:
	std::string companyName;
	
public:
	LegalCustomer(const std::string& corrName, const std::string& compName);
	~LegalCustomer();

	//virtual void importNewGoods(std::shared_ptr<BasicGoods> newG);
	//virtual double getTotalAsset() const ;

	virtual bool operator==(const Customer& in) const;
	
	virtual bool operator< (const Customer& in) const; // it gets both Real and Legal
	virtual bool operator< (const LegalCustomer& in) const;
};

#endif //
