#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
//#include "Compos.h"
using namespace std;



//\/\/\/\/\/\/\\ Strategy //\/\/\/\/\/\/\\

template < typename T >
class MyVector;

template < typename T>
class Compositor
{
public:
	Compositor(){};
	virtual void sort(MyVector<T>* vec) = 0;
private:

};

template < typename T>
class SSort : public Compositor <T>
{
public:
	SSort() {};
private:
	void sort(MyVector<T> * vec) override
	{
		std::sort(vec->begin(), vec->end());
	}
};

template < typename T>
class RSort : public Compositor <T>
{
public:
	RSort() {};
private:
	void sort(MyVector<T>* vec) override
	{
		std::sort(vec->rbegin(), vec->rend());
	}
};

template < typename T >
class MyVector : public vector<T>
{
public:

	MyVector(Compositor<T> * _sort_type) : _type(_sort_type)
	{
		
	}

	void sorting()
	{
		_type->sort(this);
	}

private:
	Compositor<T> * _type;

};


//\/\/\/\/\/\/\\ Strategy END //\/\/\/\/\/\/\\


//\/\/\/\/\/\/\\ Decorator //\/\/\/\/\/\/\\


class Functions
{
public:
	Functions()
	{

	}
	virtual void Show() = 0;
private:

};

class Object : public Functions
{
public:
	Object()
	{

	}

	void Show() override
	{
		std::cout << 1;
	}

private:
};


class Decorator : public Functions
{
public:
	Decorator(Functions * obj) : obj(obj)
	{
		
	}

	void Show() override
	{
		obj->Show();
	}
protected:
	Functions* obj;
};

class Countur1 : public Decorator
{
public:
	Countur1(Functions* obj) : Decorator(obj){

	}

	void Show() override
	{
		Decorator::Show();
		ShowCounter();
	}

private:
	void ShowCounter()
	{
		std::cout << 2;
	}
};

class Countur2 : public Decorator
{
public:
	Countur2(Functions* obj) : Decorator(obj) {
	}

	void Show() override
	{
		Decorator::Show();
		ShowCounter();
	}

private:

	void ShowCounter()
	{
		std::cout << 3;
	}
};

void Show_Elem(Functions* elem)
{
	elem->Show();
	std::cout << std::endl;
}


//\/\/\/\/\/\/\\ Decorator END //\/\/\/\/\/\/\\


//\/\/\/\/\/\/\\ Bridge //\/\/\/\/\/\/\\

class Bridge_Impl
{
public:
	Bridge_Impl()
	{

	}

	virtual void impldraw(const std::string&) = 0;
	virtual void implprint(const std::string&) = 0;
	~Bridge_Impl() {}
protected:
	std::string msg;
private:

};


class Windows : public  Bridge_Impl
{
public:
	Windows()
	{
		msg = "Windows";
	}
	void impldraw(const std::string& str) override
	{
		std::cout << "draw: " << str << "+" << msg << std::endl;
	}
	void implprint(const std::string& str) override
	{
		std::cout << "print: " << str << "+" << msg << std::endl;
	}
	~Windows() {}
};

class Linux : public  Bridge_Impl
{
public:
	Linux()
	{
		msg = "Linux";
	}
	void impldraw(const std::string& str) override
	{
		std::cout << "draw: " << str << "+" << msg << std::endl;
	}
	void implprint(const std::string& str) override
	{
		std::cout << "print: " << str << "+" << msg << std::endl;
	}
	~Linux() {}
};

struct Fabric
{
public:
	static Bridge_Impl* _get_impl();
};

Bridge_Impl* Fabric::_get_impl()
{
	if (0/* Если Windows */)
	{
		return new Windows();
	}
	if (1/* Если Linux */)
	{
		return new Linux();
	}
}



class Bridge_Abst
{
public:
	Bridge_Abst()
	{
		
	}

	virtual void draw() = 0;
	virtual void print() = 0;

	~Bridge_Abst(){}

protected:

	Bridge_Impl * get_impl()
	{
		return Fabric::_get_impl();
	}

private:

//	Bridge_Impl* impl;

};


class Excel : public Bridge_Abst
{
public:
	Excel()
	{

	}

	void draw() override
	{
		// новый код
		get_impl()->impldraw("Excel");
	}

	void print() override
	{
		// новый код
		get_impl()->implprint("Excel");
	}

	~Excel() {}
private:

};


class Word : public Bridge_Abst
{
public:

	Word()
	{

	}

	virtual void draw()
	{
		// новый код
		get_impl()->impldraw("Word");
	}

	void print() override
	{
		// новый код
		get_impl()->implprint("Word");
	}

	~Word() {}
private:

};


//\/\/\/\/\/\/\\ Bridge END //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Adapter Functions //\/\/\/\/\/\/\\

class ArifmeticAdaptee
{
private:
	std::vector<int> bin_List;
public:
	auto Bin_Slice(int n)
	{
		// Bin Slice function return vec -> 16 8 2 1 etc...
		while (n) {
			bin_List.push_back(n & ~(n - 1));
			n &= n - 1;
		}

		return bin_List;
	}

};

//\/\/\/\/\/\/\\ Adapter Functions End//\/\/\/\/\/\/\\

class Component;
class Composite;
class Leaf;

// Pattern visitor Down VVV

//\/\/\/\/\/\/\\ Chain of Responsibility //\/\/\/\/\/\/\\

class ChainComponent
{
protected:

	virtual ChainComponent* next(ChainComponent* parrent)
	{
		ptr = parrent;
		return parrent;
	}
	virtual std::string chainfunc(std::string n)
	{
		if (ptr)
		{
			return ptr->chainfunc(n);
		}
		return "";
	}
private:
	ChainComponent* ptr = nullptr;
};


//\/\/\/\/\/\/\\ Chain of Responsibility End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Command //\/\/\/\/\/\/\\


class Visitor
{
public:
	virtual void VisitLeaf(Leaf* lf) = 0;
	virtual void VisitComposite(Composite* comp) = 0;
private:
};

class Command
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
private:

};

class MenuItem
{
public:

	MenuItem(Command* command) : command(command) {
		commandName = typeid(command).name();
	}

	std::string get_command_name()
	{
		return commandName;
	}
	void Click()
	{
		command->Execute();
	}
private:
	Command* command;
	std::string commandName;
};


class Menu
{
public:
	Menu()
	{
	}

	void Add(MenuItem* item)
	{
		items.push_back(item);
	}
	void Print()
	{
		std::cout << "Menu:\n";
		for (int i = 0; i < items.size(); i++)
		{
			std::cout << items[i]->get_command_name() << std::endl;
		}
	}
	void Click(int id)
	{
		items[id]->Click();
	}
private:
	std::vector<MenuItem*> items;
};
//\/\/\/\/\/\/\\ Command end //\/\/\/\/\/\/\\
// 
//\/\/\/\/\/\/\\ Memento //\/\/\/\/\/\/\\

class MementoLeaf
{
public:
	friend class Leaf;

private:

	void SetId(int n)
	{
		id = n;
	}

	auto GetId()
	{
		return id;
	}

private:
	int id;
};

//\/\/\/\/\/\/\\ Memento End //\/\/\/\/\/\/\\ 
// 
//\/\/\/\/\/\/\\ Composition //\/\/\/\/\/\/\\

class Component : public ChainComponent
{
public:

	virtual Component * Clone() = 0;
	virtual void addChild(Component*) {}
	virtual void ArifmeticDraw() { }
	virtual void removeChild(int) {}
	virtual void draw() = 0;
	virtual Component* getChild(int index) { return nullptr; };
	virtual Component* getParrent() = 0;
	virtual size_t getSize() { return 0; };
	virtual void Accept(Visitor*) = 0;
	bool isLeaf()
	{
		return !is_comp;
	}
	int curr_id = 0;

	virtual void setParrent(Component* parent) = 0;
	bool is_comp;
	int id;
	Component* parrent;
	std::string name;
	virtual ~Component()
	{

	}
private:
};

class Leaf : public Component, private ArifmeticAdaptee
{
public:

	std::string chainfunc(std::string n) override
	{
		if (n.size()<=5 && n.size()>=1)
		{
			return "OK! Leaf id: " + 
					std::to_string(id) + 
					" ,make work: " + 
					n;
		}
		else
		{
			return ChainComponent::chainfunc(n);
		}
	}

	Component * Clone() override
	{
		return new Leaf(*this);
	}
	Leaf()
	{
		id = 0;
	}
	Leaf(int n)
	{
		is_comp = false;
		id = n;
	}
	void draw() override
	{
		std::cout << id << " ";
	}
	Component* getParrent()
	{
		return parrent;
	}
	void Accept(Visitor* visitor) override
	{
		visitor->VisitLeaf(this);
	}
	void ArifmeticDraw() override
	{
		for (auto i : Bin_Slice(id))
		{
			std::cout << i << " ";
		}
	}
	
	void SetMemonto(MementoLeaf * m)
	{
		id = m->GetId();
	}

	MementoLeaf * CreateMemonto()
	{
		auto * memonto = new MementoLeaf;
		memonto->SetId(id);
		return memonto;
	}

protected:
	void setParrent(Component* parent)
	{
		parrent = parent;
		//ChainOfResponsipility
		next(parent);
	}
private:
	Leaf(Leaf& copy)
	{
		this->curr_id = 0;
		this->id = copy.id;
		this->is_comp = false;
		this->parrent = nullptr;
		this->name = copy.name;
	}
};

class Composite : public Component
{
public:

	std::string chainfunc(std::string n) override
	{
		if (n.size() >=6)
		{
			return "OK! Composite id: " +
				std::to_string(id) +
				", make work: " +
				n;
		}
		else
		{
			return ChainComponent::chainfunc(n);
		}
	}

	Component * Clone() override
	{
		return new Composite(*this);
	}
	Composite()
	{
		is_comp = true;
		id = 0;
	}
	Composite(int n) 
	{
		is_comp = true ;
		id = n;
	}
	void addChild(Component* comp) override
	{		
		childrens.push_back(comp);
		comp->setParrent(this);

	}
	void removeChild(int n) override
	{

	}
	void draw() override
	{
		for (auto i = childrens.begin(); i < childrens.end(); i++)
		{
			(*i)->draw();
		}
	}
	Component * getChild(int index)
	{
		curr_id = index + 1;
		return childrens.at(index);
	}
	size_t getSize()
	{
		return childrens.size();
	}
	Component* getParrent()
	{
		return parrent;
	}
	void Accept(Visitor* visitor) override
	{
		visitor->VisitComposite(this);
	}
	virtual ~Composite()
	{
		for (int i = 0; i < childrens.size(); i++)
		{			
			delete childrens[i];
		}
	}
protected:
	void setParrent(Component* parent) 
	{
		parrent = parent;
	}

private:
	Composite(Composite & copy)
	{

		this->curr_id = 0;
		this->id = copy.id;
		this->is_comp = true;
		this->parrent = nullptr;
		this->name = copy.name;
		this->childrens = {};

	}
	std::vector<Component*> childrens;
};
class WriteA : public Command
{
public:
	WriteA(Component * comp) : comp(comp)
	{

	}

	void Execute()
	{
		std::cout << "WriteA->" << std::endl;
		comp->draw();
	}
	void Undo()
	{

	}
private:
	Component* comp;
};

class WriteB : public Command
{
public:
	WriteB(Component* comp) : comp(comp)
	{

	}
	void Execute()
	{
		std::cout << "WriteB->" << std::endl;
		comp->draw();
	}
	void Undo()
	{

	}
private:
	Component* comp;
};

class WriteComp
{
public:
	WriteComp()
	{
		
	}
	void Execute()
	{
		for(int i=0;i<com.size();i++)
			com[i]->Execute();
	}
	void Undo() 
	{
		for (int i = 0; i < com.size(); i++)
			com[i]->Undo();
	}
private:
	std::vector<Command*> com = {};
};

//\/\/\/\/\/\/\\ Composition + Command END //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Memento + Commands //\/\/\/\/\/\/\\


class MyCommand : public Command
{
public:
	MyCommand(Leaf* lf) :lf(lf), memento(nullptr) {}
	void Execute() override
	{
		if (memento)
			delete memento;

		memento = lf->CreateMemonto();

		lf->id = rand() % 20 + 10;

	}
	void Undo() override
	{
		lf->SetMemonto(memento);
	}
	~MyCommand()
	{
		if (memento)
			delete memento;
	}
private:
	Leaf* lf;
	MementoLeaf* memento;
};


//\/\/\/\/\/\/\\ Memento + Commands End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Iterator //\/\/\/\/\/\/\\


class IteratorComosition
{
public:
	IteratorComosition(Component * p): comp(p){}
		Component* begin()
		 {
				auto is_leaf = comp->isLeaf();
				if (is_leaf)
				{
					is_end = true;
				}
				while (!comp->isLeaf())
				{
					comp = comp->getChild(0);
				}
				return comp;
		 }
		 bool end()
		{
			 return !is_end;
		}

		 Component* Next()
		 {
			 while (comp->isLeaf())
			 {
				 comp = comp->getParrent();
			 }
			 while (!comp->isLeaf())
			 {
				 if (comp->getSize() == comp->curr_id)
				 {
					 comp = comp->getParrent();
					 if (comp == nullptr)
					 {
						 is_end = true;
						 return nullptr;
					 }
				 }
				 comp = comp->getChild(comp->curr_id);
			 }
			 return comp;
		 }
private:
	bool is_end = false;
	int _position;
	Component* comp;
};


//\/\/\/\/\/\/\\ Iterator END //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Visitor //\/\/\/\/\/\/\\


class VisitorA : public Visitor
{
public:
	void VisitLeaf(Leaf * comp) override
	{
		if (!(comp->id % 2))
		{
			std::cout << "Odd-object: ";
			comp->draw();
			std::cout << std::endl;
		}
	}
	void VisitComposite(Composite * comp) override
	{
		if (!(comp->id % 2))
		{
			std::cout << "Odd-object: ";
			comp->draw();
			std::cout << std::endl;
		}
	}
private:
	int n;
};



class VisitorB : public Visitor
{
public:
	void VisitLeaf(Leaf* comp) override
	{
		if ((comp->id % 2))
		{
			std::cout << "Even-object: ";
			comp->draw();
			std::cout << std::endl;
		}
	}
	void VisitComposite(Composite* comp) override
	{
		if ((comp->id % 2))
		{
			std::cout << "Even-object: ";
			comp->draw();
			std::cout << std::endl;
		}
	}
private:
	int n;
};



//\/\/\/\/\/\/\\ Visitor End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Singleton //\/\/\/\/\/\/\\

#include "Compos.h"

//\/\/\/\/\/\/\\ Singleton End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Builder //\/\/\/\/\/\/\\

class BuilderComponent
{
public:
	virtual void SetId(int n) = 0;
	virtual void SetName(std::string name) = 0;
	virtual int GetId() = 0;
	Component* getBuild()
	{
		return ptr;
	}
private:

protected:
	Component* ptr;
};


class BuilderComponentLeaf : public BuilderComponent
{
public:
	BuilderComponentLeaf() {
		ptr = new Leaf;
	}
	void SetId(int n) override
	{
		ptr->id = n;
	}
	void SetName(std::string name) override
	{
		ptr->name = name;
	}
	int GetId() override
	{
		return ptr->id;
	}
};

class BuilderComponentComposite : public BuilderComponent
{
public:
	BuilderComponentComposite() {
		ptr = new Composite;
	}
	void SetId(int n)
	{
		ptr->id = n;
	}
	void SetName(std::string name) override
	{
		name += "|It Composit|\n";
		ptr->name = name;
	}
	int GetId() override
	{
		return ptr->id;
	}
};


class DirectorComponent
{
public:
	static Component * MakeComponentTypeA(BuilderComponent * builder)
	{
		builder->SetId(999);
		builder->SetName("Type A");
		return builder->getBuild();
	}

	static Component * MakeComponentTypeB(BuilderComponent* builder)
	{
		builder->SetId(444);
		builder->SetName("Type B");
		return builder->getBuild();
	}
	//functions with builder
private:

protected:
	DirectorComponent(){}
};


//\/\/\/\/\/\/\\ Builder End //\/\/\/\/\/\/\\

#include <memory>

//\/\/\/\/\/\/\\ Prototype //\/\/\/\/\/\/\\

// Реализован в методах Composition функции Clone()
// Prototype_Composition()

//\/\/\/\/\/\/\\ Prototype End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Factory Method //\/\/\/\/\/\/\\

class FactoryComposition
{
public:
	virtual Component * create(int) = 0;
};

class FactoryLeaf : public FactoryComposition
{
public:
	Component* create(int id)
	{
		Component * ptr =  new Leaf;
		ptr->id = id;
		return ptr;
	}
};

class FactoryCompositor : public FactoryComposition
{
public:
	Component* create(int id)
	{
		Component* ptr = new Composite;
		ptr->id = id;
		return ptr;
	}
};

//\/\/\/\/\/\/\\ Factory Method End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Facade //\/\/\/\/\/\/\\

#include <map>

	//very easy example facade made by hard logic trees
class Facade
{
public:
	Menu * makeMenu()
	{
		return new Menu;
	}

	MenuItem * addMenuItem(Menu * menu , Command * command)
	{
		auto* ptr = new MenuItem(command);
		menu->Add(ptr);
		if (max_child.find(menu) == max_child.end())
		{
			max_child[menu] = 1;
		}
		else
			max_child[menu]++;
		return ptr;
	}

	size_t getSizeMenu(Menu* menu)
	{
		return max_child.find(menu)->second;
	}

private:
	std::map < Menu*, int > max_child;
};

//\/\/\/\/\/\/\\ Facade End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Flyweight //\/\/\/\/\/\/\\

// Realisation without impl in Composition Inteface, but you need make this

class ComponentContext
{
public:
	ComponentContext(int n)
	{
		ExtraCode = n;
	}
	int getExtraCode()
	{
		return ExtraCode;
	}
private:
	int ExtraCode = 1000;
};

class FlyweightFabric
{
public:
	/*const */Leaf* CreateLeaf(int n)
	{
		auto node = mp.find(n);
		if (node == mp.end())
		{
			 auto * ptr = new Leaf(n);
			 mp[n] = ptr;
			 return ptr;
		}
		else
			return node->second;
	}
private:
	std::map <int, Leaf*> mp;
};

//\/\/\/\/\/\/\\ Flyweight end //\/\/\/\/\/\/\\

#include <fstream>
//\/\/\/\/\/\/\\ Proxy //\/\/\/\/\/\/\\

class PhotoComponent
{
public:
	virtual void draw() = 0;

};

class _Photo : public PhotoComponent
{
public:
	void draw() override
	{
		if (image.empty())
		std::cout << "Image error\n";
		std::for_each(image.begin(), image.end(), [](char c) { std::cout << c; });
	}
	_Photo(const std::string & path)
	{
		image.reserve(500);
		_getImage(path);
	}
private:
	void _getImage(const std::string& path)
	{
		char ch;
		std::ifstream in(path);
		if (in.is_open())
		{
			while (!in.eof())
			{
				in.get(ch);
				image.push_back(ch);
			}
			in.close();
		}
	}
	std::string image;
};

//Proxy
class Photo : public PhotoComponent
{
public:
	Photo(std::string login, std::string password) :path("")
	{
		getPath(login, password);
	}
	void draw() override
	{
		if (photo == nullptr)
		{
			photo = new _Photo(path);
		}
		photo->draw();
	}
	~Photo()
	{
		if(photo!=nullptr)
			delete photo;
	}
private:
	void getPath(std::string login, std::string password)
	{
		if (login == "admin" && password == "admin")
		{
			path = "image.txt";
		}
	}
	std::string path;
	_Photo * photo;
};

//\/\/\/\/\/\/\\ Proxy end //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Template Method //\/\/\/\/\/\/\\

class CommonOutput
{
public:
	CommonOutput(const std::string & s):s(s){}
	void start()
	{
		doStringMethod();
		reverse();
		print();
	}
protected:
	std::string s;
	virtual void print()
	{
		std::cout << "hahahha";
	}
	virtual void doStringMethod() = 0;
	virtual void reverse()
	{
		std::reverse(s.begin(), s.end());
	}
	
};

class AngryOutput: public CommonOutput
{
public:
	AngryOutput(const std::string& s) :CommonOutput(s) {}
protected:

	void print() override
	{
		std::cout << "You ass:(, " << s;
	}
	virtual void doStringMethod() override
	{
		s += "0";
	}

};

class StrangeOutput : public CommonOutput
{
public:
	StrangeOutput(const std::string& s) : CommonOutput(s) {}
protected:

	void print() override
	{
		std::cout << "lol)))";
	}
	void doStringMethod() override
	{
		s = " <- words gay's";
	}

};

class NormalOutput: public AngryOutput
{
public:
	NormalOutput(const std::string& s) : AngryOutput(s) {}
protected:

	void print() override
	{
		std::cout << "Hello, " << s;
	}
	void doStringMethod() override
	{
		s += "1";
	}

};

template<typename Functor>
class StrategyTemplate
{
	Functor* obj;
public:
	StrategyTemplate(const std::string & s): obj(new Functor(s))
	{

	}
	void execute()
	{
		obj->start();
	}
	~StrategyTemplate()
	{
		delete obj;
	}
};

//\/\/\/\/\/\/\\ Template Method End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ State //\/\/\/\/\/\/\\

class DragNDrop
{
	friend class State;
	friend class Trigg;
	friend class Drag;
	friend class None;

public:
	DragNDrop(State* state);
	void ClickedEvent();
	void ReleasedEvent();
	void SetSeconds(int msec);
public:

	void DragAcceptEvent(bool is);

	int mseconds = 1000;

	void SetState(State* state);

	State* _state;
};

class State
{
public:
	virtual void ClickedEvent(DragNDrop*);
	virtual void ReleasedEvent(DragNDrop*);
	virtual void print();
private:

};

class None : public State
{
public:
	static None* Instanse();

	void ClickedEvent(DragNDrop* obj) override;
	void ReleasedEvent(DragNDrop* obj) override;
	void print() override;
protected:
	None();
private:
};

class Trigg : public State
{
public:
	static Trigg* Instanse();

	void ClickedEvent(DragNDrop* obj) override;
	void ReleasedEvent(DragNDrop* obj) override;
	void print() override;
protected:
	Trigg();
private:

};

class Drag : public State
{
public:
	static Drag* Instanse();

	void ClickedEvent(DragNDrop* obj) override;
	void ReleasedEvent(DragNDrop* obj) override;
	void print() override;
protected:
	Drag();
private:

};


	DragNDrop::DragNDrop(State* state = None::Instanse())
	{
		_state = state;
	}

	void DragNDrop::ClickedEvent()
	{
		_state->ClickedEvent(this);
	}
	void DragNDrop::ReleasedEvent()
	{
		_state->ReleasedEvent(this);
	}
	void DragNDrop::SetSeconds(int msec)
	{
		mseconds = msec;
	}

	void DragNDrop::DragAcceptEvent(bool is)
	{
		if (is)
			_state->ClickedEvent(this);
		else
			_state->ReleasedEvent(this);
	}

	void DragNDrop::SetState(State* state)
	{
		_state = state;
	}

	void State::ClickedEvent(DragNDrop*) {

	}
	void State::ReleasedEvent(DragNDrop*) {

	}
	void State::print()
	{
		std::cout << typeid(this).name() << " state";
	}

	None * None::Instanse() {

		static None* ptr;

		if (ptr)
			return ptr;
		else
			new None;
	}

	void None::ClickedEvent(DragNDrop* obj) {

		print();
		std::cout << " ClickedEvent\n";

		obj->SetState(Drag::Instanse());

		//start timer and event but now we use parametrs
		if (obj->mseconds < 1000)
			obj->DragAcceptEvent(false);
		else
			obj->DragAcceptEvent(true);

	}
	void None::ReleasedEvent(DragNDrop* obj) {

		print();
		std::cout << " ReleasedEvent\n";

	}

	None::None() {}

	void None::print()
	{
		std::cout << typeid(this).name() << " state";
	}

	Trigg* Trigg::Instanse() {

		static Trigg* ptr;

		if (ptr)
			return ptr;
		else
			new Trigg;
	}
	void Trigg::ClickedEvent(DragNDrop* obj) {

		print();
		std::cout << " ClickedEvent\n";

		obj->SetState(None::Instanse());
	}
	void Trigg::ReleasedEvent(DragNDrop* obj) {

		print();
		std::cout << " ReleasedEvent\n";

		//drop ok
		if (1)
		{
			std::cout << " OK file droped";
		}

		obj->SetState(None::Instanse());
	}

	Trigg::Trigg() {}

	void Trigg::print()
	{
		std::cout << typeid(this).name() << " state";
	}

	Drag* Drag::Instanse() {

		static Drag* ptr;

		if (ptr)
			return ptr;
		else
			new Drag;
	}

	void Drag::ClickedEvent(DragNDrop* obj) {

		print();
		std::cout << " ClickedEvent\n";

		obj->SetState(Trigg::Instanse());
	}
	void Drag::ReleasedEvent(DragNDrop* obj) {

		print();
		std::cout << " ReleasedEvent\n";

		obj->SetState(None::Instanse());
	}

	Drag::Drag() {}

	void Drag::print()
	{
		std::cout << typeid(this).name() << " state";
	}

//\/\/\/\/\/\/\\ State End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Mediator //\/\/\/\/\/\/\\

class Widget;
class Button;
class Label;

class Mediator
{
	public:

		Mediator() {}

		void setting();

		Button* but1;
		Button* but2;
		Button* but3;
		Label* text1;

		//slots

		void Clicked(Widget* ptr);
		void SetText(Widget* ptr, std::string text);
};

class Widget
{
public:
	virtual void SetMidator(Mediator* mid = nullptr) { this->mid = mid; }
protected:
	Mediator* mid;
};

class Button : public Widget
{
public:
	Button(){}

//signals

	void Clicked()
	{
		mid->Clicked(this);
	}

// slots

	void SwitchEnabled()
	{
		if (isEnabled)
			isEnabled = false;
		else
			isEnabled = true;
	}

	bool getEnabled()
	{
		return isEnabled;
	}
private:
	bool isEnabled = true;
};

class Label : public Widget
{
public:
	Label(){}

//signals

	void TextChanged(std::string text)
	{
		mid->Clicked(this);
	}

//slots

	void SetText(std::string text)
	{
		s = text;
	}
	auto GetText()
	{
		return s;
	}

private:
	std::string s;
};


void Mediator::setting()
{
		if (!but1)
		{
			std::cout << "Empty " << typeid(but1).name();
			exit(0);
		}
		else
			but1->SetMidator(this);
		if (!but2)
		{
			std::cout << "Empty " << typeid(but2).name();
			exit(0);
		}
		else
			but2->SetMidator(this);
		if (!but3)
		{
			std::cout << "Empty " << typeid(but2).name();
			exit(0);
		}
		else
			but3->SetMidator(this);
		if (!text1)
		{
			std::cout << "Empty " << typeid(text1).name();
			exit(0);
		}
		else
			text1->SetMidator(this);
}

void Mediator::Clicked(Widget * ptr)
{

	if (ptr == but1)
	{
		if (but1->getEnabled())
		{
			SetText(text1, "but1");
			but2->SwitchEnabled();
			but3->SwitchEnabled();
		}
	}
	if (ptr == but2)
	{
		if (but2->getEnabled())
		{
			SetText(text1, "but2");
			but1->SwitchEnabled();
			but3->SwitchEnabled();
		}
	}
	if (ptr == but3)
	{
		if (but3->getEnabled())
		{
			SetText(text1, "but3");
			but1->SwitchEnabled();
			but2->SwitchEnabled();
		}
	}

}

void Mediator::SetText(Widget * ptr,std::string text)
{

	if (ptr == text1)
	{
		text1->SetText(text);
	}

}


//\/\/\/\/\/\/\\ Mediator End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Observer //\/\/\/\/\/\/\\

class Observer;
class MyWidget;
// сирилизация данных
struct Pocket
{
	std::string s;
	int n;
};

class Observer
{

public:
	Observer()
	{

	}

	virtual void AddWidget(MyWidget* ptr);

	virtual void RemoveWidget(MyWidget* ptr);

	void RepublishToAll(Pocket* pock);


protected:
	std::vector< MyWidget* > _list;
};

class MyWidget
{
	friend Observer;
public:



	MyWidget()
	{

	}
	virtual void AddObserver(Observer* ptr)
	{
		auto it  = std::find(_list.begin(), _list.end(), ptr);
		if (it == _list.end())
		{
			_list.push_back(ptr);
		}
	}
	virtual void RemoveObserver(Observer* ptr)
	{
		auto it = std::find(_list.begin(), _list.end(), ptr);
		if (it != _list.end())
		{
			_list.erase(it);
		}
	}
protected:
	void PublishAll(Pocket * pock)
	{
		std::for_each(_list.begin(), _list.end(), [&](Observer* obs) {
			obs->RepublishToAll(pock);
			});
	}
	virtual void GetPocket(Pocket *) = 0;
	std::vector< Observer* > _list;
};

class Text : public MyWidget
{

protected:

public:

	//signal
	void textChanged(std::string s)
	{
		auto* pock = new Pocket{ s,0 };
		PublishAll(pock);
	}
	//slot
	auto getText()
	{
		return s;
	}
protected:
	void GetPocket(Pocket* pock)
	{
		s = pock->s;
	}
private:

	std::string s="";
};

class Number : public MyWidget
{
protected:

public:
	//signal
	void numberChanged(int n)
	{
		auto* pock = new Pocket{ "" , n };
		PublishAll(pock);
	}

	auto getNumber()
	{
		return n;
	}
protected:
	//slot
	void GetPocket(Pocket* pock)
	{
		n = pock->n;
	}
private:
	int n = 0;
};


void Observer::AddWidget(MyWidget* ptr)
{
	auto it = std::find(_list.begin(), _list.end(), ptr);
	if (it == _list.end())
	{
		_list.push_back(ptr);
	}
}

void Observer::RemoveWidget(MyWidget* ptr)
{
	auto it = std::find(_list.begin(), _list.end(), ptr);
	if (it != _list.end())
	{
		_list.erase(it);
	}
}

void Observer::RepublishToAll(Pocket* pock)
{
	std::for_each(_list.begin(), _list.end(), [&](MyWidget* wid) {
		wid->GetPocket(pock);
		});
}


class MyObserver : public Observer
{
public:

};

//\/\/\/\/\/\/\\ Observer End //\/\/\/\/\/\/\\

//\/\/\/\/\/\/\\ Special Functions //\/\/\/\/\/\/\\

void Compostion_Iterator_Visitor()
{
	auto* comp1 = new Composite(1);
	auto* comp2 = new Composite(2);
	auto* lf1 = new Leaf(3);
	auto* lf2 = new Leaf(4);
	auto* lf3 = new Leaf(5);

	comp1->addChild(lf1);
	comp2->addChild(comp1);
	comp2->addChild(lf2);
	comp1->addChild(lf3);

	IteratorComosition it(comp2);

	auto* vis = new VisitorB;

	for (auto i = it.begin(); it.end(); i = it.Next())
	{
		i->Accept(vis);
	}

	delete comp2;
	delete vis;
}

void Single_Fabric()
{
	fabric_func(SingleFabric::Instanse(SingleFabric::Type::FabricA));
	fabric_func(SingleFabric::Instanse(SingleFabric::Type::FabricB));
}

void Builder_Composition_Iterator_Vistior()
{
	auto builderComp1 = std::make_unique<BuilderComponentComposite>();
	auto builderComp2 = std::make_unique<BuilderComponentComposite>();
	auto builderLeaf1 = std::make_unique<BuilderComponentLeaf>();
	auto builderLeaf2 = std::make_unique<BuilderComponentLeaf>();

	auto * comp1 = DirectorComponent::MakeComponentTypeA(builderComp1.get());
	auto * lf1 = DirectorComponent::MakeComponentTypeA(builderLeaf1.get());
	auto * comp2 = DirectorComponent::MakeComponentTypeB(builderComp2.get());
	auto * lf2 = DirectorComponent::MakeComponentTypeB(builderLeaf2.get());
	auto* lf3 = new Leaf(3);

	comp1->addChild(lf1);
	comp2->addChild(comp1);
	comp2->addChild(lf2);
	comp1->addChild(lf3);

	//iterator Leafs
	IteratorComosition it1(comp2);

	//iterator Leafs
	IteratorComosition it2(comp2);

	auto* visA = new VisitorA;
	auto* visB = new VisitorB;

	for (auto i = it1.begin(); it1.end(); i = it1.Next())
	{
		i->Accept(visA);
		std::cout <<"his Name: "<< i->name <<"\n";
	}
	std::cout << "------------\n";
	for (auto i = it2.begin(); it2.end(); i = it2.Next())
	{
		i->Accept(visB);
		std::cout << "his Name: " << i->name << "\n";
	}

	delete visA;
	delete visB;
	delete comp2;
}

void Prototype_Composition()
{
	auto* lf1 = new Leaf(2);
	auto* comp1 = new Composite(5);

	auto* lf2 = lf1->Clone();
	auto* comp2 = comp1->Clone();

	comp2->addChild(comp1);
	comp2->addChild(lf1);
	comp1->addChild(lf2);

	IteratorComosition it1(comp2);
	auto* visA = new VisitorA;

	for (auto i = it1.begin(); it1.end(); i = it1.Next())
	{
		i->Accept(visA);
	}

	std::cout << comp1->id << std::endl;
	std::cout << comp2->id << std::endl;

	delete visA;

	delete comp2;

}

void FactoryMethod()
{
	auto* lf1 = FactoryLeaf().create(5);
	auto* comp1 = FactoryCompositor().create(3);

	comp1->addChild(lf1);

	comp1->draw();

	delete comp1;
}

void Adapter()
{
	auto* lf1 = new Leaf(30);

	lf1->ArifmeticDraw();

	delete lf1;

}

void Facade_Command()
{
	//very easy example facade made by hard logic trees
	Facade fac;
	auto* menu = fac.makeMenu();
	fac.addMenuItem(menu, new WriteA(new Leaf(5)));
	menu->Click(fac.getSizeMenu(menu)-1);
}

void Flyweight_Сomposition()
{
	// Realisation without impl in Composition Inteface, but you need make this
	//Warning! Composition don't optimisation to delete 2 same ptr, make
	//you pattern in real project with help it
	FlyweightFabric fabric;
	ComponentContext context(1000);
	// make this impl composition

	auto * comp = FactoryCompositor().create(7);

	auto * lf1 = fabric.CreateLeaf(context.getExtraCode() + 5);
	auto * lf2 = fabric.CreateLeaf(context.getExtraCode() + 2);
	auto * lf3 = fabric.CreateLeaf(context.getExtraCode() + 5);
	
	std::cout << "Adresses\n";
	std::cout << "lf1: " << lf1 << "\n";
	std::cout << "lf2: " << lf2 << "\n";
	std::cout << "lf3: " << lf3 << "\n";

	comp->addChild(lf1);
	comp->addChild(lf2);
	comp->addChild(lf3);

	std::cout << "Draw\n";
	comp->draw();
	
	//delete comp;
}

void Proxy()
{
	Photo photo1("admin","admin");
	Photo photo2("test","123");

	photo1.draw();
	photo2.draw();
	
}

void ChainReponsinilityFunc()
{
	auto * comp = new Composite(1);
	auto* lf1 = new Leaf(2);
	auto* lf2 = new Leaf(3);

	comp->addChild(lf1);
	comp->addChild(lf2);
	
	std::cout << lf1->chainfunc("make1")<<std::endl;
	std::cout << lf2->chainfunc("make2") << std::endl;
	std::cout << lf1->chainfunc("makemorethan1") << std::endl;
	std::cout << lf2->chainfunc("makemorethan2") << std::endl;
	std::cout << comp->chainfunc("make3") << std::endl;
	std::cout << comp->chainfunc("makemorethan3") << std::endl;

	delete comp;
}

void TemplateMethod()
{
	StrategyTemplate<NormalOutput> out1("test1");
	StrategyTemplate<StrangeOutput> out2("test2");
	StrategyTemplate<AngryOutput> out3("test3");

	out1.execute();
	std::cout << "\n";
	out2.execute();
	std::cout << "\n";
	out3.execute();
}

void Memento_Command_Composition()
{
	Menu mn;

	auto* lf1 = new Leaf(5);
	auto* command = new MyCommand(lf1);
	auto * item =  new MenuItem(command);

	mn.Add(item);

	std::cout << "Rand: ";
	mn.Click(0);
	lf1->draw();
	std::cout << "\nRand: ";
	mn.Click(0);
	lf1->draw();
	std::cout << "\nUndo: ";
	command->Undo();
	lf1->draw();
	std::cout << "\nRand: ";
	mn.Click(0);
	lf1->draw();
	std::cout << "\nUndo: ";
	command->Undo();
	lf1->draw();

	delete lf1;
	delete command;
	delete item;
}

void _State()
{
	DragNDrop dnp;

	// задержка создается таймером, но в данном случае используем простую перменную

	// попробуем перетащить по правилам удерживаем больше секунды

	dnp.SetSeconds(1500);
	dnp.ClickedEvent();
	dnp.ReleasedEvent();
	

	std::cout << std::endl;
	std::cout << std::endl;
	// попробуем отпустить раньше 1 секунды

	dnp.SetSeconds(700);
	dnp.ClickedEvent();
	dnp.ReleasedEvent();

	std::cout << std::endl;
	// устроить сбой

	dnp.SetSeconds(1500);
	dnp.ClickedEvent();
	dnp.ClickedEvent();
	dnp.ReleasedEvent();

	std::cout << std::endl;

}

void _Mediator()
{
	Mediator mid;

	auto * but1 = new Button;
	auto * but2 = new Button;
	auto * but3 = new Button;
	auto * text1 = new Label;

	mid.but1 = but1;
	mid.but2 = but2;
	mid.but3 = but3;
	mid.text1 = text1;

	mid.setting();
	//settings end

	std::cout << "Clicked but1\n";
	but1->Clicked();
	std::cout << "but1 Enabled: " << but1->getEnabled() << std::endl;
	std::cout << "but2 Enabled: " << but2->getEnabled() << std::endl;
	std::cout << "but3 Enabled: " << but3->getEnabled() << std::endl;
	std::cout << "text1 Text: " << text1->GetText() << std::endl;
	std::cout << std::endl;

	std::cout << "Clicked but2\n";
	but2->Clicked();
	std::cout << "but1 Enabled: " << but1->getEnabled() << std::endl;
	std::cout << "but2 Enabled: " << but2->getEnabled() << std::endl;
	std::cout << "but3 Enabled: " << but3->getEnabled() << std::endl;
	std::cout << "text1 Text: " << text1->GetText() << std::endl;
	std::cout << std::endl;

	std::cout << "Clicked but1\n";
	but1->Clicked();
	std::cout << "but1 Enabled: " << but1->getEnabled() << std::endl;
	std::cout << "but2 Enabled: " << but2->getEnabled() << std::endl;
	std::cout << "but3 Enabled: " << but3->getEnabled() << std::endl;
	std::cout << "text1 Text: " << text1->GetText() << std::endl;
	std::cout << std::endl;

	std::cout << "Clicked but3\n";
	but3->Clicked();
	std::cout << "but1 Enabled: " << but1->getEnabled() << std::endl;
	std::cout << "but2 Enabled: " << but2->getEnabled() << std::endl;
	std::cout << "but3 Enabled: " << but3->getEnabled() << std::endl;
	std::cout << "text1 Text: " << text1->GetText() << std::endl;
	std::cout << std::endl;



	//clean
	delete but1;
	delete but2;
	delete but3;
	delete text1;


}

void _Observer()
{
	auto * obs =  new Observer;
	auto * txt1 = new Text;
	auto * txt2 = new Text;
	auto * txt3 =  new Text;
	auto * number1 = new Number;
	auto * number2 = new Number;
	auto * number3 = new Number;

	obs->AddWidget(txt1);
	obs->AddWidget(txt2);
	obs->AddWidget(number1);
	obs->AddWidget(number2);

	txt1->AddObserver(obs);
	txt3->AddObserver(obs);
	number2->AddObserver(obs);
	number3->AddObserver(obs);

	txt1->textChanged("test1");
	std::cout << "\ntxt1 signal\n";
	std::cout << "text1 " << txt1->getText() << "\n";
	std::cout << "text2 " << txt2->getText() << "\n";
	std::cout << "text3 " << txt3->getText() << "\n";

	txt3->textChanged("test2");
	std::cout << "\ntxt3 signal\n";
	std::cout << "text1 " << txt1->getText() << "\n";
	std::cout << "text2 " << txt2->getText() << "\n";
	std::cout << "text3 " << txt3->getText() << "\n";

	txt2->textChanged("test3");
	std::cout << "\ntxt2 signal\n";
	std::cout << "text1 " << txt1->getText() << "\n";
	std::cout << "text2 " << txt2->getText() << "\n";
	std::cout << "text3 " << txt3->getText() << "\n";
	
	obs->RemoveWidget(number1);
	std::cout << std::endl;
	number1->numberChanged(1);
	std::cout << "\nnumber1 signal\n";
	std::cout << "num1 " << number1->getNumber() << "\n";
	std::cout << "num2 " << number2->getNumber() << "\n";
	std::cout << "num3 " << number3->getNumber() << "\n";

	number2->numberChanged(2);
	std::cout << "\nnumber2 signal\n";
	std::cout << "num1 " << number1->getNumber() << "\n";
	std::cout << "num2 " << number2->getNumber() << "\n";
	std::cout << "num3 " << number3->getNumber() << "\n";

	number3->numberChanged(3);
	std::cout << "\nnumber3 signal\n";
	std::cout << "num1 " << number1->getNumber() << "\n";
	std::cout << "num2 " << number2->getNumber() << "\n";
	std::cout << "num3 " << number3->getNumber() << "\n";

	delete obs;
	delete txt1;
	delete txt2;
	delete txt3;
	delete number1;
	delete number2;
	delete number3;
}

//\/\/\/\/\/\/\\ Special Functions End //\/\/\/\/\/\/\\

//Interpretator едиснтвенный паттерн не сделанный мной, так как не имеет четкой структуры, довольно сложный
//его можно реализовать и парсером и деревом по желанию, применяется довольно редко в реальных проектах


int main()
{
	//Single_Fabric();
	//Compostion_Iterator_Visitor();
	//Builder_Composition_Iterator_Vistior();
	//Prototype_Composition();
	//FactoryMethod();
	//Adapter();
	//Facade_Command();
	//Flyweight_Сomposition();
	//Proxy();
	//ChainReponsinilityFunc();
	//TemplateMethod();
	//Memento_Command_Composition();
	//_State();
	//_Mediator();
	//_Observer();
}






//артем писька какашка вонючая жопа в трусах с сердечками 
//я тебя люблю !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
