#include "database.h"
#include "take-height-measurement.h"
#include "read-distance-and-update-xml.h"
//#include "Coms_NO.h" // For Norwegian language
#include "Coms_EN.h" // For English language
#include "button.h"


int main(int argc, char *argv[])
{
    int m = 1; // Meny option holder 
    int um = 0; // User meny choice
    char* l = "EN"; // Language for lcd output
  
    Coms user_comms; // Input / Output / Error Messages
    Database DB(l); // SQL database with lcd output language
    Button button; // Code related to button
    button.setup(); 
    user_comms.intro();

    while (m >= 0) {
        if (m == 1) { // Main menu
            user_comms.menu_main();
            um = user_comms.get_menu_int(3);
            if (um == 1) { // go to m2, menu for new user
                m = 2;
                um = 0;
            }
            else if (um == 2) { // go to m3, menu for exicting user
                m = 3;
                um = 0;
            }
            else if (um == 3) { // go to m4, menu for settings
                m = 4;
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
                m = 2;//----loop back to new user menu---- 
                um = 0;
                
                //int hight = 0; // dummy for local test
                std::string user;                 
                user_comms.ask_for_name();
                std::cin >>user;
                
                int z = 0; // For loop, waiting on button
                int height;
      
                // --------------------------TO DO, ADD BUTTON---------------------------------------
                while(z==0){ // While button not pressed
                    // x = check_button(); // checks button
                    if(button.button_pushed==true){ // Button pressed
                        button.do_something();
                        height = takeHeightMeasurement();
                        z = 1; // Breaks loop
                    }
                }
                // --------------------------TO DO, ADD BUTTON---------------------------------------
                
               // DB.write_user(user, hight); // For local test
                DB.write_user(user, height);
                user = ""; // Reset user name
                // --------------------------TO DO, ADD LCD screen---------------------------------------

                DB.get_last_user(); // returns string vector with name and height

                // --------------------------TO DO, ADD LCD screen---------------------------------------

                DB.print_to_lcd(); // returns string vector with name and height
                DB.send_to_lcd();

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
            user_comms.menu_excisting();
            um = user_comms.get_menu_int(2);
            if (um == 1) {
                m = 3;//---loop back to existing menu----
                um = 0;

                std::string user = "";
                user_comms.ask_for_name(); 
                std::cin >> user;
                DB.read_user(user);

            }
            else if (um == 2) {
                m = 3;//---loop back to existing menu----
                um = 0;
                DB.view_database();
            }
            else if (um == 0) {//return to main
                m = 1;
                um = 0;
            }
            else if (um == -1) {//wrong input, return to menu
                m = 3;
                um = 0;
            }
            else {// error, um out of range
                user_comms.error_message("user input(um) out of range");
            }

        }
         else if (m == 4) {// menu for system settings
            user_comms.menu_settings();
            um = user_comms.get_menu_int(3);

            if (um == 1) { // Read XMl file and save system values
                m = 4;//---loop back to settings menu----
                um = 0;
                //----------------------------- TO DO --------------------------------
                DB.create_table();// Create the table in database
                if (readDistanceAndUpdateXml() == 1) {
                    std::cout << "Xml: Read/Uppdate Successful" << std::endl << std::endl;

                }
                else user_comms.error_message("Error reading/uppdating xml");
                //----------------------------- TO DO --------------------------------

            }
            else if (um == 2) { // Renew default height sensor distance
                m = 4;//---loop back to settings menu----
                um = 0;
                if (readDistanceAndUpdateXml() == 1) {
                    std::cout << "Xml: Read/Uppdate Successful" << std::endl;
                }
                else user_comms.error_message("Error reading/uppdating xml");
                
            }
            else if (um == 3) { // Clear database
                m = 4;//---loop back to settings menu----
                um = 0;
                DB.clear_database(); // Clear data from database
            }
            else if (um == 0) {//return to main
                m = 1;
                um = 0;
            }
            else if (um == -1) {//wrong input, return to menu
                m = 4;
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

