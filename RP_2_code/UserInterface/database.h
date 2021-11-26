#include <iostream>
#include <ctime>
#include <string>
//#include "sqlite3/sqlite3.h"  //For windows
# include <sqlite3.h> //For Linux

class Database
{

	private: 
		/*Name of the database*/
		std::string database_name ="HightMeasure.db";
		/*Pointer to the database*/
		sqlite3 *DB;
		/*Error message for SQL errors*/
		char *error_message = 0;
		/*Used in sqlite3_exec*/
		static int callback(void* NotUsed, int argc, char** argv, char** azColName);
		

	public:
		/*Opens the database*/
		int open_database();
		/*Check if database interaction is succsessfull*/
		void test_open(int exit, std::string success_message);
		/*Create a table in database*/
		void create_table();
		/*Insert a new user into database*/
		void write_user(std::string name, int height);
		/*Finds if User with name (Name), if so, prints*/
		void read_user(std::string name);
		/*Closes the database*/
		void close_database();
		/*Se all of database content*/
		void view_database();
		/*Deletes the table in database*/
		void clear_database();


		

};

