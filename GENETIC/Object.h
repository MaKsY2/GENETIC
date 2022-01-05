#ifndef OBJECT_H
#define OBJECT_H

const int OBJECTS_CNT = 5;

enum ObjectType
{
	BOT,
	FOOD,
	NUN,
	POISON,
	WALL
};

class MyObject
{
public:
	MyObject(ObjectType aType);
	virtual ~MyObject();
	ObjectType getType();
private:
	ObjectType mType;
};

#endif // !OBJECT_H