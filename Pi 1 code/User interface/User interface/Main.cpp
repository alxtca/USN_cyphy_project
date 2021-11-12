#include "User.h"
#include "Coms.h"

int main()
{
    Coms user_comms;
    int m = 1; // Meny option holder 
    int um = 0; // User meny choice

    user_comms.intro();

    while (m >= 0) {
        if (m == 1) { // Main menu
            user_comms.menu_main();
            um = user_comms.get_menu_int(2);
            if (um == 1) { // go to m2, menu for new user
                m = 2;
                um = 0;
            }
            else if (um == 2) { // go to m3, menu for exicting user
                m = 3;
                um = 0;
            }
            else if (um == 0) {// go to m0, end programm
                m = 0;
                um = 0;
            }
            else if (um == -1) {//redo m1, user input not valid
                m = 1;
                um = 0;
            }
            else {
                user_comms.error_message("user input(um) out of range");
            }
        }
        else if (m == 2) { // Menu for new user 
            user_comms.menu_new();
            um = user_comms.get_menu_int(1);
            if (um == 1) {// new user
                m = 2;//----temp---loop meny---- 
                um = 0;
                // --------------------------TO DO---------------------------------------
                    // create new user and get hight data

                   // save new user with hight data and time
                // --------------------------TO DO---------------------------------------
            }
            else if (um == 0) {//return to main
                m = 1;
                um = 0;
            }
            else if (um == -1) {//wrong input, return to meny
                m = 2;
                um = 0;
            }
            else {//error, um out of range
                user_comms.error_message("user input(um) out of range");
            }

        }
        else if (m == 3) {// menu for getting exicting user data
            user_comms.menu_existing();
            um = user_comms.get_menu_int(1);
            if (um == 1) {
                m = 3;//----temp---loop meny----
                um = 0;
                /*
             --------------------------TO DO---------------------------------------
                std::string username;// holds string input
                std::cout << "Name of user:  ";
                std::cin >> username;
                if(fund_user(username==true)){
                    //display user name and data
                    username="";//reset username
                }
                else{
                std::cout << "Now user with name "<< username<<" found in system."<<std::endl;
                username = ""//reset username
                }
             --------------------------TO DO---------------------------------------
                */

            }
            else if (um == 0) {//return to main
                m = 1;
                um = 0;
            }
            else if (um == -1) {//wrong input, return to meny
                m = 3;
                um = 0;
            }
            else {// error, um out of range
                user_comms.error_message("user input(um) out of range");
            }

        }
        else if (m == 0) {// exit programm
            user_comms.end();
            m = -1;
        }
        else {// Error, m out of range
            user_comms.error_message("user input(m) out of range");
        }

    }

}

