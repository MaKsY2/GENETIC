#include "Object.h"

#include <iostream>

using namespace std;

MyObject::MyObject()
{

}

MyObject::MyObject(ObjectType aType) :
	mType(aType)
{}

ObjectType MyObject::getType()
{
	if (mType == ObjectType::FOOD)
	{
		int tt = 0;
		tt++;
	}
	return mType;

}

MyObject::~MyObject()
{

}