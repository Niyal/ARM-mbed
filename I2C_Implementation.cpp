/*	----
		Prepared by: Naila 
		Date: 20.03.2017 
	---- 
	#Program Functionality: Set up for an I2C Data Link with FX0S8700CQ-1
	#Board: FRDM-K82F
	#Sensor: FXOS8700CQ

	#single-byte I2C, message transmission, 
			i.e. start - send_address - send_data - stop
	#Source: https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/io/inputs_outputs/
			
	#Data Sheet
		Table 4.  Accelerometer and magnetometer signals connection   
					FXOS8700Q  K82F Connection 
					SCL :PTA2/ I2C3_SCL 
					SDA :PTA1/ I2C3_SDA 
					
		Table 5.  LED signal connection   
				  RGB LED  K82F Connection 
				  Red  PTC8 
				  Green  PTC9 
				  Blue  PTC10  
				  
		Table 6.  Push button switch connections   
				  Switch  K82F Connection 
				  SW2  PTA4/NMI_B 
				  SW3  PTC6/LLWU_P10
 



*/

#include "mbed.h"

I2C i2c_port(PTA1, PTA2); //Configuring Port, sda(PTA1), scl(PTA2)

DigitalOut red_led(PTC3); //red led
DigitalOut green_led(PTC9); //green led

DigitalIn switch_ip1(PTA4); //input switch1
DigitalIn switch_ip2(PTC6); //inpput switch2
 

char switch_word ; //word to send
char recd_val; //value received from slave
const int addr = 0x1E; //the I2C slave address, SA1(0) and SA0(0), Data Sheet

int main() {

while(1) {
	switch_word=0xa0; //set up for a recognizable output pattern
	if (switch_ip1==1)
		switch_word=switch_word | 0x01; //OR in lsb

	if (switch_ip2==1)
		switch_word=switch_word | 0x02;  

//send a single byte of data
i2c_port.start(); //force a start condition
i2c_port.write(addr); //send the address, 0x1E
i2c_port.write(switch_word); //send one byte of data, ie switch_word
i2c_port.stop(); //force a stop condition
wait_ms(2);

//receive a single byte of data
i2c_port.start(); //force a start condition
i2c_port.write(addr|0x01); //send address, with R/W bit set to Read
recd_val=i2c_port.read(addr); //Read and save the received byte
i2c_port.stop(); //force a stop condition
wait_ms(2);

//set leds according to incoming word from slave
	red_led=0; //preset both to 0
	green_led=0;
	recd_val=recd_val&0x03; //AND out unwanted bits
	if (recd_val==1)
		red_led=1;
	if (recd_val==2)
		green_led=1;
	if (recd_val==3)
	{
		red_led=1;
		green_led=1;
	}
}
}










