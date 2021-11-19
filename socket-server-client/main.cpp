//purpose of this program is
// to demonstrate how to include sendRequest() into main program

#include "client_int.h"
#include <iostream>

int main(){
    char request_message[] = "height"; //curretly only one request is supported
    int height = sendRequest(request_message);

    if (height == 10000){
        std::cout << "bad request" << std::endl;
    } else {
        std::cout << "height is: " << height << std::endl;
    }

    return 0;
}

//how to compile
//g++ main.cpp client_int.cpp -o main_client