#include "User.h"
#include <iostream>
#include <string>

std::string User::user_name()
{
	return name;
}

std::string User::user_hight()
{
	return std::to_string(hight);
}
