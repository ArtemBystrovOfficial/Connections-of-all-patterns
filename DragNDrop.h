/*

#ifndef MY_2_HPP_INCLUDE
#define MY_2_HPP_INCLUDE

#include "State.h"

class DragNDrop
{
	friend class State;
	friend class Trigg;
	friend class Drag;
	friend class None;

public:
	DragNDrop(State* state = None::Instanse());
	void ClickedEvent();
	void ReleasedEvent();
	void SetSeconds(int msec);
public:

	void DragAcceptEvent(bool is);

	int mseconds = 1000;

	void SetState(State* state);

	State* _state;
};

#endif

*/