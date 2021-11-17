#pragma once
#include <iostream>

/*
---------------Not in Use--------------------
*/


class User				//User data class
{
private:
	std::string name;	//Name of user
	int hight;			//Hight of user

public:
	// Create user
	User(std::string name, int hight) :name{ name }, hight{ hight }{}
	/* Return user name */
	std::string user_name();
	/* Return user name*/
	std::string user_hight();
};

