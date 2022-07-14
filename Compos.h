#include <iostream>

class SingleFabric
{
public:

	enum class Type
	{
		FabricA,
		FabricB
	};

	static SingleFabric* Instanse(Type&& type);
	virtual void GetPaint();
	virtual void GetBrush();
protected:
	SingleFabric();
private:
	static SingleFabric* ptr;
};

class FabricA : public SingleFabric
{
private:

public:
	void GetPaint() override;
	void GetBrush() override;
};

class FabricB : public SingleFabric
{
private:

public:

	void GetBrush() override;

};

void fabric_func(SingleFabric* fabric);
