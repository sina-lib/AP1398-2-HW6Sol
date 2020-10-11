#include <iostream>
#include "foodCommodity.h"
#include "applianceCommodity.h"
#include "material.h"
#include "productID.h"
#include "product.h"
#include "gtest/gtest.h"
#include "realCustomer.h"
#include "legalCustomer.h"
#include "Storehouse.h"
#include <queue>
#include <sstream>


#include "ST_GTest.cpp"
#include "MY_Gtest.cpp"
#include "CO_GTest.cpp"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	std::cout << "\033[45m" << "<<<<<<<<<<<< SINA >>>>>>>>>>>>>>"  << "\033[m" << std::endl;
	
	return RUN_ALL_TESTS();
}
