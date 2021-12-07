#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "RS-232/rs232.h"
#include <iostream>
#include <string>

/* This function sets up a serial connection with Arduino, sending it a message to take a measurement. 
* It waits for a Arduino to finish, and returns the data received back (from Arduino) to main as an int */

#define BUF_SIZE 128

int measureHeight(){
  //your serial code here
  
	int COM_port = {24}; // COM port number for device: /dev/ttyACM0 (Arduino MEGA)
	int baud_rate = {115200}; //chosen baud rate
	char mode[] = {'8', 'N', '1', 0 }; //Mode setup: {8 data bits, no parity, 1 stop bit, no flow control}
	
	char outgoing[BUF_SIZE]; // Buffer for outgoing message
	unsigned char incoming[BUF_SIZE]; // Buffer for incoming message
  
	//Open Serial COM port:
	if(RS232_OpenComport(COM_port, baud_rate, mode, 0)) // 0 = no flow control
	//Parameters: int RS232_OpenComport(int comport_number, int baudrate, const char * mode, int flowctrl)
	{
		printf("Can not open comport\n");	//print if no connection
	}
	

  
	usleep(1'000'000);  // wait 1 second for stable condition
  
	strcpy(outgoing, "start"); //copy "outgoing" buffer to string
	RS232_cputs(COM_port, outgoing); // sending "outgoing" string to Arduino
	printf("Message sent to Arduino: '%s'\n", outgoing); //Feedback: Showing data sent to Arduino
	usleep(10'000'000);  // wait 10 seconds before checking for reply
	
	// Check reply:
	// content will be stored in incoming[]
	int bytes_received = RS232_PollComport(COM_port, incoming, (int)BUF_SIZE); //int bytes_received is number of bytes received from Arduino
	//Parameters: int RS232_PollComport(int comport_number, unsigned char *buf, int size)

	if(bytes_received > 0){ // If number of 'bytes_received' is greater than zero, then there is data from Arduino
		incoming[bytes_received] = 0;   // add zero behind last received byte to signals end of data
		printf("Received %i bytes: '%s'\n", received, (char *)incoming); //Feedback: Showing number of bytes received
	}
	
	RS232_CloseComport(COM_port);
	
	/* Convert unsigned char message to normal char, because 
	 * std::string does not take unsigned char*/
	char char_copy[BUF_SIZE];
	for(int i = 0 ; i < BUF_SIZE; i++){
		char_copy[i] = incoming[i];		
		if(incoming[i] == '\0'){
			break;
		}
	}
	
	std::string string_copy{char_copy}; //convert message to string
	int distance{std::stoi(string_copy)}; //convert message to int
	//Test: Feedback to user, is distance correct?
	std::cout << "Distance to object: " << distance << " cm" << std::endl;
  
  return distance;
}

