

bool eq(double a, double b)
{ return std::abs(a-b) < 0.0001; }

std::vector<double> extractNumbers(std::string INP)
{
	std::vector<double> res;
	std::istringstream ss{INP};
	std::string buf;
	
	while (! ss.eof())
	{
		ss >> buf;
		double a;
		if (std::stringstream(buf) >> a)
		{
			//std::cout << "number: " << a << std::endl;
			res.push_back(a);
		}
	}
	return res;
}

namespace
{
	TEST (CO, check)
	{
		double A{0.3};
		A += A*(1.0001*A - 0.0001);
		A *= 0.021;
		
		EXPECT_EQ (eq(A, 0.008189), true) << std::setw(120) << "****** CHECK COMPILER!" ;
	}

	
	TEST (CO_Goods, Basic) // 20
	{
		std::string fxName{"Reg"};
		const double Price1 {3.045};
		
		BasicGoods bg1 { fxName+"ulator" , GOODS_TYPE::DISPOSABLE, Price1};
		BasicGoods bg2 { "Regulator"     , GOODS_TYPE::DISPOSABLE, Price1}; // ! 2 points here
		bg1.setOriginCountry(std::string("China"));

		fxName = "RR"; // some arbitrary change to avoid address copy
		
		std::shared_ptr< std::array<double,3> > pV { new std::array<double,3>( {0.77, 2.4, 1.11} ) };
		bg2.setAppearance(PACK_TYPE::NYLON, pV);
		
		
		double tx = BasicGoods::INITIAL_TAX_RATE / 100.0;
		EXPECT_EQ ( eq(bg1.getEndPrice() , (1+tx)*Price1 ) , true)  << std::setw(110) << "********** minus 2 points";
		EXPECT_EQ ( eq(bg2.getVolume(), 0.77*2.4*1.11 ) , true) << std::setw(110) << "***************** minus 2 points";
		EXPECT_EQ ( bg1.getOriginCountry() , std::string("China") ) << std::setw(110) << "***************** minus 2 points";
		EXPECT_EQ ( bg1.getBrandName() , bg2.getBrandName() ) << std::setw(110) << "***************** minus 2 points";
		EXPECT_EQ ( eq(bg2.getTaxPrice(), Price1 * tx ) , true) << std::setw(110) << "***************** minus 2 points";
		EXPECT_EQ ( bg1 == bg2 , true) << std::setw(110) << "***************** minus 2 points";

		BasicGoods bg3 {"Reg", GOODS_TYPE::OBJECT, 34};
		
		EXPECT_EQ ( bg3 < bg1 , false) << std::setw(110) << "***************** minus 3 points";;
		EXPECT_EQ ( bg1 < bg3 , true) << std::setw(110) << "***************** minus 3 points";
	}
	TEST (CO_Goods, Food_Basic) // 15
	{
		const double ftx = (BasicGoods::INITIAL_TAX_RATE - Food::FOOD_TAX_SUBSIDE) / 100.0;
		const double Price1 = 12.3;
		const double Wei1 = 50;
		
		Food fg1 {"Potato", Price1, Wei1, FOOD_MODE::LIQUID};
		Food fg2 {"Potato", Price1, Wei1, FOOD_MODE::LIQUID}; // 2 points here

		EXPECT_EQ ( eq(fg1.getEndPrice(), (1+ftx) * Price1) , true) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( eq(fg1.getVolume(), 0.3*0.4*0.2*Wei1 ) , true) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( eq(fg1.getWeight(), Wei1+0.1) , true) << std::setw(110) << "***************** minus 1 points";
		
		fg1.setExpiration(std::time(nullptr) - 100);
		std::time_t remTime = fg1.getRemainingExp();
		EXPECT_EQ ( std::abs(remTime - 14 * 24 * 3600) < 2 , true) << std::setw(110) << "***************** minus 1 points";
		
		std::time_t tim = std::time(nullptr) + 3600 * 24 * 2;
		fg1.setExpiration(tim);
		EXPECT_EQ ( std::abs(fg1.getRemainingExp() - 3600 * 24 * 2) < 3 , true) << std::setw(110) << "***************** minus 2 points";

		BasicGoods abg{"Potato", GOODS_TYPE::CONSUMABLE, Price1};
		
		EXPECT_EQ ( fg1==fg2 , true) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( fg1==abg , false) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( abg==fg1 , false) << std::setw(110) << "***************** minus 1 points";

		BasicGoods& Rbg = fg2;
		EXPECT_EQ ( fg1==Rbg , true) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( Rbg==fg1 , true) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( fg1==abg , false) << std::setw(110) << "***************** minus 1 points";
		fg2.setFoodMode(FOOD_MODE::SOLID);
		EXPECT_EQ ( fg1==fg2, false ) << std::setw(110) << "***************** minus 1 points";
	}
	TEST (CO_Goods, Mat_Ap) // 15
	{
		const double mtx  = (BasicGoods::INITIAL_TAX_RATE + Material::MATERIAL_TAX) / 100.0;
		const double atxH = (BasicGoods::INITIAL_TAX_RATE + Appliance::APPLIANCE_EXTRA_TAX_HIGH) / 100.0;
		const double atxM = (BasicGoods::INITIAL_TAX_RATE + Appliance::APPLIANCE_EXTRA_TAX_MEDIUM) / 100.0;

		const double MPrice = 44.23;
		const double MW = 23;
		Material mg1 {"Plaster", MPrice, MW};
		Material mg2 {"Plaster", MPrice, MW+2};
		Material mg3 {"Plaster", MPrice, MW}; // 3 points for constructors

		EXPECT_EQ ( eq(mg1.getEndPrice(), MPrice * (1+mtx)), true ) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( mg1==mg3, true) << std::setw(110) << "***************** minus 1 points";
		BasicGoods& RB1 = mg1;
		BasicGoods& RB2 = mg2;
		
		EXPECT_EQ ( RB1==RB2 , false ) << std::setw(110) << "***************** minus 3 points";
		EXPECT_EQ ( mg1==RB1 , true ) << std::setw(110) << "***************** minus 2 points";

		const double APrice = 555.5;
		const double AW = 120.12;
		Appliance ag1 {"TV", APrice, AW};

		EXPECT_EQ ( eq(ag1.getTaxPrice() , APrice * atxM), true) << std::setw(110) << "***************** minus 1 points";
		BasicGoods& RB3 = ag1;
		EXPECT_EQ ( eq(RB3.getEndPrice(), APrice*(1+atxM)) , true ) << std::setw(110) << "***************** minus 2 points";
		ag1.setEnergyGrade(ENERGY_COST::HIGH);
		EXPECT_EQ ( eq(RB3.getEndPrice(), APrice * (1+atxH)) , true ) << std::setw(110) << "***************** minus 1 points";

		ag1.setNewPrice( mg1.getEndPrice() / (1+mtx)  / (1+atxH));
		EXPECT_EQ ( mg1<ag1 , false) << std::setw(110) << "***************** minus 1 points";
		
	}
	TEST (CO_Goods, Product) // 8
	{
		auto NIOC_LIC = std::make_shared<std::string> ("NIOC is a national ORG.");

		auto pg1 = std::make_shared<Product> ("PIPE_40INCH"   , 2000, 5000, NIOC_LIC); // name price matWei Licen

		EXPECT_EQ ( eq(pg1->getEndPrice(),2600) , true) << std::setw(110) << "***************** minus 1 points";
		EXPECT_EQ ( eq(pg1->getVolume(),2400.48) , true ) << std::setw(110) << "***************** minus 2 points";
		EXPECT_EQ ( eq(pg1->getWeight(), 5000.4) , true) << std::setw(110) << "***************** minus 1 points";
		pg1->setTaxRate(77);
		EXPECT_EQ ( eq(pg1->getEndPrice(),3680), true) << std::setw(110) << "***************** minus 2 points";
		
		productID* pid = pg1.get();
		pg1->setOriginCountry("Korea");
		std::ostringstream ss;
		ss << *pid;
		std::string buf = ss.str();
		buf.erase(buf.begin()+95, buf.end());
		
		EXPECT_EQ ( buf , "Legal Confirmation Statement: [NIOC is a national ORG.]\nproducer country: Korea , serial number" ) << std::setw(110) << "***************** minus 2 points";
		
	}
	TEST (CO_Customer, Real_Legal) // 28
	{
		RealCustomer A{"Jane", 124};
		std::vector<std::shared_ptr<BasicGoods>> Gs{};

		Gs.push_back(std::make_shared<BasicGoods>("BF494",GOODS_TYPE::OBJECT,2.5)); // 0
		Gs.push_back(std::make_shared<Food> ("Potato",1.2,3) ); // 1
		Gs.push_back(std::make_shared<Material> ("Wood",100,100)); // 2
		Gs.push_back(std::make_shared<Material> ("Suger", 25, 30) ); // 3
		Gs.push_back(std::make_shared<Food> ("Banana", 5,6)); // 4
		Gs.push_back(std::make_shared<Appliance> ("Suger", 100,25) ); // 5
		Gs.push_back(std::make_shared<Food> ("Fish", 3, 1.2)); // 6
		Gs.push_back(std::make_shared<Food> ("Pasta" , 4, 1.5) ); // 7


		// setting up expirations
		std::time_t now = std::time(nullptr);
		std::time_t oneDaySeconds = 24*3600;
		
		Food* ptrF = reinterpret_cast<Food*>(Gs[1].get());
		ptrF->setExpiration(now+4*oneDaySeconds);
		ptrF = reinterpret_cast<Food*>(Gs[4].get());
		ptrF->setExpiration(now+oneDaySeconds);
		ptrF = reinterpret_cast<Food*>(Gs[6].get());
		ptrF->setExpiration(now+3*oneDaySeconds);
		ptrF = reinterpret_cast<Food*>(Gs[7].get());
		ptrF->setExpiration(now+3*oneDaySeconds+5);
		
		// IMPORTs

		A.importNewGoods(Gs[0]);
		A.importNewGoods(Gs[5]);
	    EXPECT_EQ(  eq( A.getTotalAsset() - Gs[0]->getEndPrice() - Gs[5]->getEndPrice() , 0) , true) << std::setw(110) << "***************** minus 3 points";

		A.importNewGoods(Gs.begin()+1,Gs.end());

		double a{};
		for (auto item: Gs) a+=item->getEndPrice();
		a+=Gs[5]->getEndPrice();
		EXPECT_EQ ( eq(a, A.getTotalAsset() ), true) << std::setw(110) << "***************** minus 4 points";


		// PRINTers
		
		std::string buf = A.printBasicInfo();
		std::string Name;
		std::istringstream(buf) >> Name;
		
		buf.erase(std::remove_if(buf.begin(), buf.end(), ::isspace), buf.end()); // remove all spaces
		if ( buf != "Jane>>Noofassets:9,TotalAsset:373.214,ChargedTax:32.514")
		{
			auto ns = extractNumbers(A.printBasicInfo());
			std::vector<double> NS{9, 373.214, 32.514};
			EXPECT_EQ( Name, "Jane") << std::setw(110) << "***************** minus 2 points";
			try
			{
				EXPECT_EQ( eq(ns.at(0),NS[0]) && eq(ns.at(1),NS[1]) && eq(ns.at(2),NS[2]) , true ) << std::setw(110) << "***************** minus 2 points";
			}
			catch (const std::out_of_range& oor)
			{
				EXPECT_EQ (true, false) << std::setw(110) << "***************** minus 2 points";;
			}
		}

		// FILLers
		using sharedBG = std::shared_ptr<BasicGoods>;
		std::deque<sharedBG> mq;
		A.findGoods(mq, [] (const sharedBG& in) -> bool { return in->getBrandName() == "Suger"; } );
		double prc{};
		for (auto item: mq) prc += item->getTaxPrice();
		EXPECT_EQ( eq(prc, 2*Gs[5]->getTaxPrice() + Gs[3]->getTaxPrice()) , true ) << std::setw(110) << "***************** minus 6 points";


		std::priority_queue< sharedBG, std::deque<sharedBG>, Shared_less<BasicGoods> > mpq;
		A.queueGoods<Food>(mpq);
		std::stringstream pqs;
		while (! mpq.empty())
		{
			Food* p = reinterpret_cast<Food*>(mpq.top().get());
			pqs << p->getBrandName() << "-";
			mpq.pop();
		}
		EXPECT_EQ ( pqs.str() , "Potato-Pasta-Fish-Banana-" ) << std::setw(110) << "***************** minus 6 points";
		
		// Legal
		LegalCustomer L{"Parham","EE"};
	    L.importNewGoods(Gs[0]);
		L.importNewGoods(Gs[2]);

		RealCustomer A2 {"Jane",124};
		EXPECT_EQ ( A<L, true) << std::setw(110) << "***************** minus 2 points";
		EXPECT_EQ ( A==A2, true) << std::setw(110) << "***************** minus 2 points";
	}
	TEST (CO_Store, Store) // 14
	{
		Storehouse Bport {"Customs"};

		auto A = std::make_shared<RealCustomer>  ( "A", 11  );
		auto B = std::make_shared<RealCustomer>  ( "A", 11  );
		auto C = std::make_shared<LegalCustomer> ( "E","ee" );
		auto D = std::make_shared<LegalCustomer> ( "E","ee" );
		
		A->importNewGoods(std::make_shared<Material> ("Wood", 33, 3));
		C->importNewGoods(std::make_shared<Food> ("Macaroni", 20, 10));
		D->importNewGoods(std::make_shared<Food> ("Chips", 20, 20));
		
		Bport.newCustomer(A);
		Bport.newCustomer(B);
		Bport.newCustomer(C);
		Bport.newCustomer(D);

		//std::cout << Bport.printCustomers();
		std::string buf = Bport.printCustomers();
		buf.erase(std::remove_if(buf.begin(), buf.end(), ::isspace), buf.end()); // remove all spaces
		
		if ( buf !=
			 "Legal:E>>Noofassets:1,TotalAsset:20.4,ChargedTax:0.4Real:A>>Noofassets:1,TotalAsset:35.145,ChargedTax:2.145" )
		{
			auto ns = extractNumbers(Bport.printCustomers());
			std::vector<double> N = {1, 20.4, 0.4, 1, 35.145, 2.145};

			std::istringstream ss{Bport.printCustomers()};
			ss >> buf;
			EXPECT_EQ (buf, "Legal:") << std::setw(110) << "***************** minus 4 points";
			try
			{
				EXPECT_EQ ( eq(ns.at(0), N[0]) && eq(ns.at(1),N[1]) && eq(ns.at(2),N[2]) , true ) << std::setw(110) << "***************** minus 4 points";
				EXPECT_EQ ( eq(ns.at(3),N[3]) && eq(ns.at(4),N[4]) && eq(ns.at(5),N[5]) , true) << std::setw(110) << "***************** minus 4 points";
			}
			catch(const std::out_of_range& orr)
			{
				std::cout << "EXCEPTION !!! \n";
				EXPECT_EQ ( true,false ) << std::setw(110) << "***************** minus 8 points";
			}
		}
	}
}

