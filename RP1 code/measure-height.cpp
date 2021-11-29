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
		printf("Can not open comport\n");
		return;
		/* 	This is a fail-check, but not sure how it works. RS232_OpenComport() does return an 
		*	int depending on success or not, but I can't see it used here. It does work however, 
		*	and prints fail message when Arduino is not connected
	  */
	}
	//untested alternative
	/*int open = RS232_OpenComport(COM_port, baud_rate, mode, 0); //returns 1 in case of error
	if(open == 1){
		printf("Can not open comport\n");
		return; 
	}
	*/

  
	usleep(2000000);  // wait 2 seconds for stable condition
  
	strcpy(outgoing, "start"); //copy "outgoing" buffer to string
	RS232_cputs(COM_port, outgoing); // sending "outgoing" string to Arduino
	printf("Message sent to Arduino: '%s'\n", outgoing); //Feedback: Showing data sent to Arduino
	usleep(3000000);  // wait 3 seconds before checking for reply
	
	// Check reply: content to be stored in incoming[]
	int received = RS232_PollComport(COM_port, incoming, (int)BUF_SIZE); //int received shows number of bytes received from Arduino
	//Parameters: int RS232_PollComport(int comport_number, unsigned char *buf, int size)

	if(received > 0){ // If 'received' is greater than zero, then there was data from Arduino
		incoming[received] = 0;   // add zero behind last received byte to signals end of data
		printf("Received %i bytes: '%s'\n", received, (char *)incoming); //Feedback: Showing number of bytes received
	}
	
	RS232_CloseComport(COM_port);
	
	/* Making a signed copy of incoming[] buf, because std::string 
	does not work with unsigned char*/
	char signed_copy[BUF_SIZE];
	for(int i = 0 ; i < BUF_SIZE; i++){
		signed_copy[i] = incoming[i];
		/* untested change to include
		if(incoming[i] == '\0'){
			break;
		}*/
	}
	
	std::string charArray_to_string{signed_copy}; //convert char-array to string
	int distance{std::stoi(charArray_to_string)}; //convert string to int
	//Test: Feedback to user, is distance correct?
	std::cout << "Distance to object: " << distance << " cm" << std::endl;
  
  return distance;
}

