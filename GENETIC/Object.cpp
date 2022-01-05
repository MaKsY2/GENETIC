#include "Object.h"

#include <iostream>

using namespace std;

MyObject::MyObject(ObjectType aType) :
	mType(aType)
{}

ObjectType MyObject::getType()
{
	return mType;
}

MyObject::~MyObject()
{

}