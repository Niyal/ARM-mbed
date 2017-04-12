/*	----
		Prepared by: Naila 
		Date: 20.03.2017 
	---- 
	#Program Functionality: I2C, Reading Data from FX0S8700CQ-1
	#Board: FRDM-K82F
	#Sensor: FXOS8700CQ

	# Source: https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/interfaces/digital/I2C/#hello-world
			

	/* Read from an I2C slave
  *
  * Performs a complete read transaction. The bottom bit of
  * the address is forced to 1 to indicate a read.
  *
  * @param address 8-bit I2C slave address [ addr | 1 ]
  * @param data Pointer to the byte-array to read data in to
  * @param length Number of bytes to read
  * @param repeated Repeated start, true - don't send stop at end
  *
  * @returns
  * 0 on success (ack),
  * non-0 on failure (nack)
  * /		
			
	 int write(int address, const char *data, int length, bool repeated = false);

 		
*/

#include "mbed.h"

I2C sensor(PTA1, PTA2); //Configuring Port, sda(PTA1), scl(PTA2)

const int addr8bit = 0x1E // 8bit I2C address, Data Sheet
char config_t[3];
char sensor_read[2];
float sensor_value;

int main() {
   	config_t[0] = 0x01; //set pointer reg to ’ conﬁg register ’
	config_t[1] = 0x60; // config data byte1
	config_t[2] = 0xA0; // config data byte2
	
	sensor.write(addr8bit,config_t,3);
	
	config_t[0] = 0x00;
	sensor.write(addr,config_t,1);
	
	while(1){
		wait(0.5);
		sensor.read(addr8bit,config_t,2);
		
		sensor_value = 0.976 * ((config_t[0]<<8)|config_t[1]); // conversion factor 0.976 from Data Sheet!
        pc.printf("Temp = %.2f\n", sensor_value);
		
	}

}

