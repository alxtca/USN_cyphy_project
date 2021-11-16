#pragma once
#
#include <iostream>

class User				//User data class
{
private:
	std::string name;	//Name of user
	int hight;			//Hight of user

public:
	User(std::string name, int hight) :name{ name }, hight{ hight }{}
};

