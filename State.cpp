
/*
#include "State.h"
#include <iostream>
	void State::ClickedEvent(DragNDrop*) {

	}
	void State::ReleasedEvent(DragNDrop*) {

	}
	void State::print()
	{
		std::cout << typeid(this).name() << " state";
	}


	 None* None::Instanse() {

		static None* ptr;

		if (ptr)
			return ptr;
		else
			new None;
	}

	void None::ClickedEvent(DragNDrop* obj){

		print();
		std::cout << "printEvent\n";

		obj->SetState(Drag::Instanse());

		//start timer and event but now we use parametrs
		if (obj->mseconds < 1000)
			obj->DragAcceptEvent(false);
		else
			obj->DragAcceptEvent(true);

	}
	void None::ReleasedEvent(DragNDrop* obj){

		print();
		std::cout << "ReleasedEvent\n";

	}

	None::None() {}

	Trigg* Trigg::Instanse() {

		static Trigg* ptr;

		if (ptr)
			return ptr;
		else
			new Trigg;
	}
	void Trigg::ClickedEvent(DragNDrop* obj){

		print();
		std::cout << "ClickedEvent\n";

		obj->SetState(None::Instanse());
	}
	void Trigg::ReleasedEvent(DragNDrop* obj) {

		print();
		std::cout << "ReleasedEvent\n";

		//drop ok
		if (1)
		{
			std::cout << "OK file droped";
		}

		obj->SetState(None::Instanse());
	}

	Trigg::Trigg() {}


	Drag* Drag::Instanse() {

		static Drag* ptr;

		if (ptr)
			return ptr;
		else
			new Drag;
	}

	void Drag::ClickedEvent(DragNDrop* obj) {

		print();
		std::cout << "ClickedEvent\n";

		obj->SetState(Trigg::Instanse());
	}
	void Drag::ReleasedEvent(DragNDrop* obj) {

		print();
		std::cout << "ReleasedEvent\n";

		obj->SetState(None::Instanse());
	}
	*/