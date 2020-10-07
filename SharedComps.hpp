#ifndef SHARED_COMPARISON
#define SHARED_COMPARISON

#include <iostream>

template <class T>
struct Shared_less
{
	bool operator() (const std::shared_ptr<T>& a, const std::shared_ptr<T>& b)
		{
			if ( (typeid(*a) == typeid(Food)) && (typeid(*b) == typeid(Food)) )
			{
				std::cout << "comparing two food" <<std::endl;
				if ( (! (a->operator<(*b)) ) && (! (b->operator<(*a))) )
				{
					std::cout << "compating two food with same exp Time" << std::endl;
					return a->getEndPrice() < b->getEndPrice();
				}
				std::cout << "two food with different exp TIme" << std::endl;
			}
			
				return a->operator< ( *b );
		}
};


	
#endif
