#ifndef OBJECT_H
#define OBJECT_H

#define OBJECTS_CNT 5
#define START_BOT_HEALTH 100
#define FOOD_ADD_HEALTH 10
#define POISON_TAKE_HEALTH 10
#define HEALTH_PER_TURN 1
#define COMMAND_COUNT 5
#define BOT_MEMORY 64



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
	MyObject();
	MyObject(ObjectType aType);
	virtual ~MyObject();
	ObjectType getType();
private:
	ObjectType mType;
};

#endif // !OBJECT_H