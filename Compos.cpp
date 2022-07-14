#include "Compos.h"


	SingleFabric* SingleFabric::Instanse(Type&& type)
	{
		if (ptr == nullptr)
		{
			switch (type)
			{
			case(Type::FabricB):
			{
				ptr = new FabricB;
				break;
			}
			case(Type::FabricA):
			{
				ptr = new FabricA;
				break;
			}
			}
		}
		return ptr;
	}
     void SingleFabric::GetPaint()
	{
		std::cout << "Paint\n";
		//return Paint
	}
	 void SingleFabric::GetBrush()
	{
		std::cout << "Brush\n";
		//return Brush
	}

	 SingleFabric::SingleFabric() {
		 if (ptr != nullptr)
			 delete ptr;
	 };


	 SingleFabric * SingleFabric::ptr = nullptr;



	void FabricA::GetPaint() 
	{
		std::cout << "Paint A\n";
		// Special Paint
	}
	void FabricA::GetBrush()
	{
		std::cout << "Brush A\n";
		// Special Brush
	}



	void FabricB::GetBrush() 
	{
		std::cout << "Brush B\n";
		// Special Brush
	}


void fabric_func(SingleFabric* fabric)
{
	fabric->GetBrush();
	fabric->GetPaint();
}
