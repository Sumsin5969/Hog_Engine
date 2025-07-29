#pragma once
#include <glad/gl.h>
#include <iostream>
#include <array>

struct vec2
{ 
	float x, y;
	vec2() :x(0), y(0) {}
	vec2(float a, float b) :x(a), y(b) {}
};

struct Obj
{
	
	float x;
	float y;
	float w;
	float h;
};

class ObjectManager
{
public:
	vec2 pos{ 0,1 };
	
private:

};