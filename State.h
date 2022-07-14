
/*
#ifndef MY_1_HPP_INCLUDE
#define MY_1_HPP_INCLUDE

#include "DragNDrop.h"

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
protected:
	Drag();
private:

};

#endif

*/