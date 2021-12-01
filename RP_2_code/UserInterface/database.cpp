
#include "database.h"



int Database::callback(void* NotUsed, int num_results, char** values, char** columns)
{
    int i;
    for (i = 0; i < num_results; i++) {
        printf("%s = %s\n", columns[i], values[i] ? values[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int Database::save_callback(void* NotUsed, int num_results, char** values, char** columns)
{
    if (num_results == 1) {
        user.push_back(values[0]);
        user.push_back(values[1]);
    }
    else
    {
        std::cout << "ERROR save_callback"<<std::endl;
    }

    return 0;
}

int Database::open_database()
{
    int exit = 0;
    exit = sqlite3_open(database_name.c_str(), &DB); //opens the database
    test_open(exit, "DB Open: "); //Check if database opened succsessfully
    
    return exit;
}

void Database::test_open(int exit, std::string success_message)
{
    if (exit != SQLITE_OK) {// The database interaction failed
        fprintf(stderr, "SQL error: %s\n", error_message);
        sqlite3_free(error_message); 
    }
    else // Database interaction succsessful
        std::cout << success_message; 
}


void Database::create_table()
{
    int exit = open_database();

    if (!exit) { //Database opened succsessfully
        /*SQL statment for table creation*/
        exit = sqlite3_exec(DB, "CREATE TABLE USER(" \
            "NAME TEXT PRIMARY KEY NOT NULL,"\
            "HIGHT INT NOTT NULL,"\
            "TIME TIMESTAMP WITHOUT TIME ZONE); ", callback, 0, &error_message);

        test_open(exit, "Table created successfully"); //Check if table created successfully
    }
    close_database();

}

void Database::write_user(std::string name, int height)
{
    int exit = open_database();

    if (!exit) {//Database opened succsessfully
        /*Create string for sql Query*/
        std::string sql = "INSERT INTO USER (NAME,HIGHT,TIME) VALUES('"+name+"',"+std::to_string(height)+",'"+__TIMESTAMP__+"')";
        /*SQL statment for inserting user into table*/
        exit = sqlite3_exec(DB,sql.c_str(), callback, 0, &error_message);
        test_open(exit, "Innsert to table successfully");
    }
    
    close_database();
}

void Database::read_user(std::string name)
{
    int exit = open_database();
    if (!exit) {//Database opened succsessfully
        /*Create string for sql Query*/
        std::string sql = "SELECT * FROM USER WHERE NAME ='" + name + "'";
        /*SQL statment for finding user in table*/
        exit = sqlite3_exec(DB, sql.c_str(), callback, 0, &error_message);
        test_open(exit, "Read from table successfull");
    }
    close_database();
}

std::vector<std::string> Database::get_user(void)
{
    int exit = open_database();
    if (!exit) {//Database opened succsessfully
        /*Create string for sql Query*/
        std::string sql = "SELECT * FROM USER ORDER BY column DESC LIMIT 1";
        /*SQL statment for finding user in table*/
        exit = sqlite3_exec(DB, sql.c_str(), save_callback, 0, &error_message);
        test_open(exit, "Read from table successfull");
    }

    return user;
    
}

void Database::close_database()
{
    int exit = sqlite3_close(DB); //Close the database
    test_open(exit, " :DB Closed\n");//Check if database closed successfully


}

void Database::view_database()
{

    int exit = open_database();

    if (!exit) {//Database opened succsessfully
        std::cout <<"View Database "<< std::endl;
        /*SQL statment for printing all users in table*/
        sqlite3_exec(DB, "SELECT * FROM USER", callback, 0, &error_message);
    }
    close_database();
}

void Database::clear_database()
{
    int exit = open_database();

    if (!exit) {//Database opened succsessfully
        /*SQL statment for deleting table*/
        exit = sqlite3_exec(DB, "DROP TABLE USER", callback, 0, &error_message);
        test_open(exit, "Table removed successfully");
    }
    close_database();

}

