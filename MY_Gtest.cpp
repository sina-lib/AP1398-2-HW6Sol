namespace
{
	TEST (MMath, Basics)
	{
		EXPECT_EQ(3,3) << "Math is going Wrong here!!!" << std::endl;
	}
	
	TEST (MGoods, BasicGoods)
	{
		BasicGoods g1 {"armchair" , GOODS_TYPE::OBJECT, 30};
		g1.setOriginCountry("Italy");
		BasicGoods g2 {"armchair" , GOODS_TYPE::OBJECT, 30};
		g2.setOriginCountry("China");

		auto armBoxes{ std::make_shared< std::array<double,3> > () };
		(*armBoxes) = std::array<double,3>( {0.85,1.2,2} ) ;

		
		
		g1.setAppearance(PACK_TYPE::CARTON, armBoxes);
		g2.setAppearance(PACK_TYPE::CARTON, armBoxes);


		double Vol1 {1};
		for (auto i: *armBoxes) Vol1 *= i;
		
		EXPECT_EQ(g1.getVolume(), Vol1) << "BasicGoods Volume is not working" ;


		BasicGoods g3 {"Tablet", GOODS_TYPE::OBJECT, 450};
		g3.setOriginCountry("Taiwan");

		EXPECT_EQ (true, g1 == g2) << "How can two same armChairs be different?";
		EXPECT_EQ (false, g1 == g3) << g3.getBrandName() << " is not equal to " << g1.getBrandName() << " but program sees them as if they are equal"  ;

		EXPECT_EQ ( (1.05*450) , g3.getEndPrice()) << "tax rate is not correctly applied to " << g3.getBrandName() << std::endl ;
	}
	TEST (MGoods, FoodCommodity)
	{
		std::time_t now = std::time(nullptr);
		const long int oneDaySeconds = 24*3600;
		
		Food fg1{"Tunna Fish", 12, 0.18};
		fg1.setExpiration( now + oneDaySeconds);
		
		Food fg2{"Canny Carrot", 4, 1.2};
		fg2.setExpiration( now + oneDaySeconds*2 );

		EXPECT_EQ (true, fg1 < fg2) << "the food with earlier expiration should be lower!";

		Food fg3{"Tunna Fish", 12, 0.25};
		fg3.setExpiration( now + oneDaySeconds*2 );

		

		//EXPECT_EQ (false, fg3 == fg1) << "how cane " << fg1.getBrandName() << " be equal to " << fg3.getBrandName() << std::endl;
	    EXPECT_EQ (false, fg1 == fg2) << "cannot differ between " << fg1.getBrandName() << " and " << fg2.getBrandName() << std::endl;

		BasicGoods bg1 {"Tunna Fish", GOODS_TYPE::CONSUMABLE, 12};
		EXPECT_EQ (false, fg1 == bg1) << " cannot differ a Food and a BasicG" << std::endl;

		fg3.setFoodMode (FOOD_MODE::CREAM);
		EXPECT_EQ (false, fg1 == fg3) << "two Foods has different Modes!" << std::endl;

		// note : Food Subside is 3%
		BasicGoods* ptrFG1 {&fg1};
		EXPECT_EQ (ptrFG1->getEndPrice() , 12*1.02) << " virtual getEndPrice not working" << std::endl;
		EXPECT_EQ (fg1.getEndPrice() , ptrFG1->getEndPrice()) << "virtual getEndPrice not working" << std::endl;
	}

	TEST (MGoods, Appliance)
	{
		Appliance ag1 {"VaccumCleaner", 300, 4.4};
		ag1.setEnergyGrade(ENERGY_COST::MEDIUM);

		Appliance ag2 {"VaccumCleaner", 350, 4.5};
		ag2.setEnergyGrade(ENERGY_COST::LOW);
		
		Appliance ag3 {"VaccumCleaner", 300, 4.4};
		
		EXPECT_EQ (4.5, ag1.getWeight() ) << "problem calculation weight of" << ag1.getBrandName() << std::endl;

		EXPECT_EQ (false, ag3==ag1) << "ag3 is not equal to ag1 haaa!" << std::endl; 
	}
	TEST (MGoods, Material)
	{
		Material mg1 {"cement" , 80, 50, MAT_TYPE::NORMAL};
		Material mg2 {"Plaster", 55, 35};
		Material mg3 {"Dye"    , 22, 15};
		std::cout << mg1.getBrandName() << std::endl;
	}
	TEST (MGoods, prod)
	{
		auto myState = std::make_shared<std::string>( std::string("this product is registerd and Legal.") );
		Product H{"Benz", 3000, 150, myState};
		std::cout << "\033[36mFaranak !!! \033[m" << std::endl;
		//int l;
		//std::cin >>l; 
		productID* pid = &H;
		pid->printStatement();
		std::cout << *pid ;
		std::cout << H;
	}
	TEST (MCustomer, Reals)
	{
		RealCustomer Jim{"Jimmy Kuberg"};

		auto g1 = std::make_shared<Food> ("Potato",1.2,3);
		auto g2 = std::make_shared<Material> ("Wood",100,100);
		auto g3 = std::make_shared<Material> ("Suger", 25, 30);
		auto g4 = std::make_shared<Food> ("Banana", 5,6);
		
		Jim.importNewGoods(g1);
		Jim.importNewGoods(g2);
		Jim.importNewGoods(g3);
		Jim.importNewGoods(g4);

		double price{};
		
		price += g1->getEndPrice();
		price += g2->getEndPrice();
		price += g3->getEndPrice();
		price += g4->getEndPrice();
		
		
		std::cout << "Jims total asset price: " << Jim.getTotalAsset() << std::endl;
		EXPECT_EQ (price , Jim.getTotalAsset()) << "RealCustomer Jim total assest price is not equal to sum of its assets!" << std::endl;;
		EXPECT_EQ (true, Jim==Jim) << "one real customer is equal to him/her-self !" << std::endl;
	}
	TEST (MCustomer, Legal)
	{
		std::shared_ptr<std::string> FaraLicense = std::make_shared<std::string>("Faratabir is a Registered Company, IR.");
		
		LegalCustomer FaraTadbir{"MasoudMirzaei","FaraTadbir"};

		auto g1 = std::make_shared<Product> ("AirConditioner",700,15,FaraLicense);
		auto g2 = std::make_shared<Product> ("Piano",1250, 6, FaraLicense);
		auto g3 = std::make_shared<Appliance> ("SamTV", 250, 5.5);
		auto g4 = std::make_shared<Appliance> ("LG_TV", 230, 4.5);
		auto g5 = std::make_shared<Appliance> ("SamTV", 280, 5.0);
		auto g6 = std::make_shared<BasicGoods> ("CietraMask", GOODS_TYPE::DISPOSABLE, 1.2);

		FaraTadbir.importNewGoods(g1);
		FaraTadbir.importNewGoods(g2);
		FaraTadbir.importNewGoods(g3);
		FaraTadbir.importNewGoods(g4);
		FaraTadbir.importNewGoods(g5);
		for (size_t i{}; i<10; i++)
			FaraTadbir.importNewGoods(std::make_shared<BasicGoods>("CietraMask", GOODS_TYPE::DISPOSABLE, 1.2));
	}

	TEST (MCustomer, STLs)
	{
		std::shared_ptr<std::string> Pish_LIC = std::make_shared<std::string> ("Pishgaman is a registered Co.");

		LegalCustomer Pishgam{"SamanK","PISHGAMAN"};

		auto g1 = std::make_shared<Product> ("Radiator", 40, 15, Pish_LIC);
		g1->setOriginCountry("Taiwan");
		g1->setEnergyGrade(ENERGY_COST::HIGH);
		
		auto g2 = std::make_shared<Product> ("Toyota", 1000, 200, Pish_LIC);
		g2->setOriginCountry("Japan");
		g2->setEnergyGrade(ENERGY_COST::MEDIUM);

		auto g3 = std::make_shared<Product> ("GSM_repeater", 400, 3, Pish_LIC);
		g3->setEnergyGrade(ENERGY_COST::MEDIUM);
		
		auto g4 = std::make_shared<Product> ("PS4", 300, 0.3, Pish_LIC);
		g4->setOriginCountry("China");
		
		auto g5 = std::make_shared<Appliance> ("AC_Fan", 140, 3);
		g5->setOriginCountry("China");
		
		auto g6 = std::make_shared<Appliance> ("Crusher", 100, 10);
		g6->setOriginCountry("China");
		
		auto g7 = std::make_shared<Material> ("Paper", 20, 10);
		g7->setOriginCountry("Japan");
		g7->setAppearance(PACK_TYPE::CARTON, std::make_shared<std::array<double,3>>( std::array<double,3>( {0.5,0.2,0.7} ) ));

		
		auto g8 = std::make_shared<Material> ("Alchol", 5, 1, MAT_TYPE::FLAMABLE);
		g8->setOriginCountry("Japan");
		g8->setAppearance(PACK_TYPE::CAN, std::make_shared<std::array<double,3>>( std::array<double,3>( {0.5,0.2,0.7} ) ));
		
		/*Pishgam.importNewGoods(g1);
		Pishgam.importNewGoods(g2);
		Pishgam.importNewGoods(g3);
		Pishgam.importNewGoods(g4);
		Pishgam.importNewGoods(g5);
		Pishgam.importNewGoods(g6);
		Pishgam.importNewGoods(g7);
		Pishgam.importNewGoods(g8);*/

		std::vector<std::shared_ptr<BasicGoods>> testGoods{};
		testGoods.push_back(g1);
		testGoods.push_back(g2);
		testGoods.push_back(g3);
		testGoods.push_back(g4);
		testGoods.push_back(g5);
		testGoods.push_back(g6);
		testGoods.push_back(g7);
		testGoods.push_back(g8);

		Pishgam.importNewGoods(testGoods.begin(), testGoods.end());

		auto oCJ = [] ( std::shared_ptr<BasicGoods>& g ) -> bool
	    { return (g->getOriginCountry() == "Japan"); };

		std::deque<Customer::sharedBG> jps{};
		Pishgam.findGoods(jps, oCJ);
		
		for (auto& it : jps)
		{
			std::cout << it->getBrandName() << "  ::  " << it->getOriginCountry() << std::endl;
		}
	}

	TEST (MSTOREHOUSE, store)
	{
		auto MCI_LIC = std::make_shared<std::string>("MCI is a registered Co.");
		auto PayamCommerce_LIC = std::make_shared<std::string> ("Payam is a registered Co");
		auto NIOC_LIC = std::make_shared<std::string> ("NIOC is a national ORG.");

		auto Taheri = std::make_shared<RealCustomer> ( "Taheri", 451311 );
		Taheri->importNewGoods( std::make_shared<Food> ("Notella", 8, 0.45, FOOD_MODE::CREAM) );
		Taheri->importNewGoods( std::make_shared<Food> ("Cheese", 3.5, 0.8 ) );
		Taheri->importNewGoods( std::make_shared<Food> ("Orange", 40, 40) );
		Taheri->importNewGoods( std::make_shared<Material> ("Rice", 25, 5) );
		Taheri->importNewGoods( std::make_shared<Material> ("Salt", 45, 100) );

		// fake Taheri
		auto Taheri2 = std::make_shared<RealCustomer> ("Taheri", 451311 );
		Taheri2->importNewGoods( std::make_shared<Appliance> ("Flash" ,17, 0.3 ) );

		
		auto Karimi = std::make_shared<RealCustomer> ("Karimi", 827342);
		Karimi->importNewGoods( std::make_shared<Appliance> ("DVD", 20, 1.5) );
		Karimi->importNewGoods( std::make_shared<Appliance> ("Laptop", 670, 2.2) );
		Karimi->importNewGoods( std::make_shared<Appliance> ("Laptop", 550, 2.3) );
		Karimi->importNewGoods( std::make_shared<Appliance> ("PowerSupply", 3, 0.5) );
		// Laptop Egg ipad HC06 Raspberry AMD Ryzen 7PRO Mobile
		
		auto MCI = std::make_shared<LegalCustomer> ("MehdiAkhavan","MCI");

		MCI->importNewGoods( std::make_shared<Appliance> ("RNC_4G", 30000, 50) );
		MCI->importNewGoods( std::make_shared<Product>   ("BTS", 42000, 350, MCI_LIC) );
		MCI->importNewGoods( std::make_shared<Product>   ("4G_PACKET_GTW", 1500, 0, MCI_LIC) );
		MCI->importNewGoods( std::make_shared<Appliance> ("MODEM_4G", 200, 0.3) );
		MCI->importNewGoods( std::make_shared<Product>   ("Mobile", 100, 0.4, MCI_LIC) );
		


		auto NIOC = std::make_shared<LegalCustomer> ("RoknoddinJavadi","NIOC");
		NIOC->importNewGoods( std::make_shared<Product> ("PIPE_40INCH"   , 2000, 5000, NIOC_LIC) );
		NIOC->importNewGoods( std::make_shared<Product> ("COOPER_FLENCH" ,  500, 1000, NIOC_LIC) );
		for (size_t i{}; i<150 ; i++)
			NIOC->importNewGoods( std::make_shared<BasicGoods> ("Mask" , GOODS_TYPE::DISPOSABLE , 0.5) );
		
		// ======================================================================================================
		Storehouse BAport {"Bandar Abbas Customs"};

		BAport.newCustomer(Taheri);
		BAport.newCustomer(Karimi);
		BAport.newCustomer(MCI);
		BAport.newCustomer(NIOC);

		
		BAport.newCustomer(Taheri2);
		
		BAport.printCustomers();


		std::cout << "\033[35mNext, using p_que:\033[m\n";
					 
		std::priority_queue< std::shared_ptr<BasicGoods> , std::deque< std::shared_ptr<BasicGoods> > , Shared_less<BasicGoods> > mQ;

		Taheri->queueGoods<Material>(mQ);

					 while (!mQ.empty())
					 {
						 std::shared_ptr< BasicGoods > a = mQ.top();
						 
						 std::cout << "Item: " << a->getBrandName() << std::endl;
																	   mQ.pop();
					 }
		}

	TEST (MhGoods, pq)
	{
		auto g1 = std::make_shared<BasicGoods> ("Glass", GOODS_TYPE::OBJECT, 15.0);
		auto g2 = std::make_shared<BasicGoods> ("Paper", GOODS_TYPE::OBJECT, 5.0);
		auto g3 = std::make_shared<Material>   ("Wood", 20.0, 25.0, MAT_TYPE::FLAMABLE);

		std::shared_ptr<BasicGoods> pg = g3;
		std::cout << pg->getBrandName() << "[" << pg->getEndPrice() << "] - " << g2->getBrandName() << " [" << g2->getEndPrice() << "] >>> " << (pg->operator<(*g2)) << std::endl;
		std::cout << pg->getBrandName() << "[" << pg->getEndPrice() << "] - " << g2->getBrandName() << " [" << g2->getEndPrice() << "] <<< " << (g2->operator<(*pg)) << std::endl;

		//(*pg) = *g2; // what the fuck!
		//std::cout << pg->getBrandName() << " - " << g2->getBrandName() << "  >>>  "<< (pg->operator==(*g2)) << std::endl;

		std::deque< std::shared_ptr<BasicGoods> > assets;
		
		
		assets.push_back(g1);
		assets.push_front(g2);
		assets.push_back(g3);

		//std::sort(assets.begin(), assets.end(), Shared_less<BasicGoods>() );
		
		for (auto item: assets)
		{
			std::cout << item->getBrandName() << " price: " << item->getEndPrice() << std::endl;
		}
	}

} 
 
