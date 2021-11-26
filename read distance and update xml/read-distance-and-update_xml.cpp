//this program is a setting option in main menu
//it shall call send-distance-request()
//and save returned value to a file data.xml

/* to be called from main menu like this:

#include "read-height-and-update-xml.h"

int main()
{
    readDistanceAndUpdateXml();
}

*/

#include <iostream>
#include <fstream>
#include <string>
#include "send-distance-request.h"

int readDistanceAndUpdateXml() {
    //request distance
    char request_message[] = "height"; //curretly only one request is supported
    int distance = sendRequest(request_message);

    if (distance == 10000) {
        std::cout << "bad request" << std::endl;
        return 0;
    }
    else {
        std::cout << "height is: " << distance << std::endl;
    }

    //store height into data.txt //replace with write to data.xml //write to tag <sensor position>
    std::ofstream MyFile("data.txt");
    MyFile << distance;
    MyFile.close();

    std::cout << "data saved: " << distance << std::endl;

    return 1;
}