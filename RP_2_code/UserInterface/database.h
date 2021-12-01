#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "sqlite3/sqlite3.h"  //For windows
//# include <sqlite3.h> //For Linux

class Database
{

	private: 
		/*Name of the database*/
		std::string database_name ="HeightMeasure.db";
		/*Pointer to the database*/
		sqlite3 *DB;
		/*Error message for SQL errors*/
		char *error_message = 0;
		/*Temp saved user data*/
		static std::vector<std::string> user;
		/*Used in sqlite3_exec*/
		static int callback(void* NotUsed, int num_results, char** values, char** columns);
		/*Used in sqlite3_exec(SELECT) for saving retuned values */
		static int save_callback(void* NotUsed, int num_results, char** values, char** columns);
		

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
		std::vector<std::string> get_user(void);
		/*Closes the database*/
		void close_database();
		/*Se all of database content*/
		void view_database();
		/*Deletes the table in database*/
		void clear_database();


		

};

