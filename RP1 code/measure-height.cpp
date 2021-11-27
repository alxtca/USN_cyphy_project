#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "RS-232/rs232.h"
#include <iostream>
#include <string>

#define BUF_SIZE 128


int measureHeight(){
  //your serial code here
  
  //int i=0;
	int COM_port = {24}; /* COM port number for device /dev/ttyACM0 (Arduino MEGA)*/
	int baud_rate = {115200}; /* baud rate */
	char mode[] = {'8', 'N', '1', 0 }; // Setup: 8 data bits, no parity, 1 stop bit, no flow control
	
	char string_to_send[BUF_SIZE]; // send data buffer
	unsigned char string_receive[BUF_SIZE]; // receive data buffer
  
	//open Serial COM port
	if(RS232_OpenComport(COM_port, baud_rate, mode, 0))
	{
		printf("Can not open comport\n");
		return(0);
	}
  
	usleep(2000000);  /* wait 2 seconds for stable condition */
  
	strcpy(string_to_send, "start");
	RS232_cputs(COM_port, string_to_send); // sends string on serial
	printf("Sent to Arduino: '%s'\n", string_to_send);
	usleep(3000000);  /* wait 2 seconds before checking reply */
	
	int no_ofBytes_back = RS232_PollComport(COM_port, string_receive, (int)BUF_SIZE);
	if(no_ofBytes_back > 0){
		string_receive[no_ofBytes_back] = 0;   /* always put a "null" at the end of a string! */
		printf("Received %i bytes: '%s'\n", no_ofBytes_back, (char *)string_receive);
	}
	
	RS232_CloseComport(COM_port);
	
	char buf[BUF_SIZE];
	for(int i = 0 ; i < BUF_SIZE; i++){
		buf[i] = string_receive[i];
	}
	
	std::cout << "riktig variabel: " << string_receive << std::endl;
	std::cout << "riktig variabel: " << buf << std::endl;
	
	//int int_distance = (int)(string_receive[0]);
	
    //string to int
	std::string d{buf};
	int int_distance{std::stoi(d)};
	std::cout << "riktig variabel: " << int_distance << std::endl;
  
  return int_distance;
}

