/**********************************************************************
* 2009 Microchip Technology Inc.
*
* FileName:        	comparator.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       	PIC18F
* Compiler:        	MCC18 v3.30 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all 
* ownership and intellectual property rights in the code accompanying
* this message and in all derivatives hereto.  You may use this code,
* and any derivatives created by any person or entity by or on your 
* behalf, exclusively with Microchip's proprietary products.  Your 
* acceptance and/or use of this code constitutes agreement to the 
* terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS". NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT 
* NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
* CODE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS, COMBINATION WITH 
* ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE 
* LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR
* BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
* CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
* EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR 
* EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER 
* CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
* DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP 
* SPECIFICALLY TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify,
* test, certify, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Harsha.J.M	04/04/09	First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code uses the Peripheral library support available with MCC18 Compiler
* Code Tested on:
* PicDem2+ demo board with PIC18F4685 controller
* The Processor starts with the External Crystal (8 Mhz).
*
* signal to be compared are applied to CxIN+ & CxIN- and output is tapped at CxOUT
**********************************************************************/

#define USE_OR_MASKS
#include <p18cxxx.h>
#include "i2c.h"


//-------------------------------Configuration setting ----------------------------------------------
/**
	* Oscillator is configured as HS
	* Fail safe monitor is enabled
	* watch dog timer is disabled
	* Extended instruction mode is disabled
	* oscillator switch over is enabled	
*/
#if defined(__18F4685)		//If the selected device if PIC18F4685, then apply below settings else user will have to set
#pragma config OSC=HS, FCMEN=ON, WDT=OFF, IESO=ON, XINST=OFF, LVP=OFF 
#endif



unsigned char I2C_Send[21] = "MICROCHIP:I2C_SLAVE" ;
unsigned char I2C_Recv[21];

//************ I2C SLAVE ****************************************
void main(void)
{

unsigned char sync_mode=0, slew=0, add1,status,temp,w,length=0;

for(w=0;w<20;w++)
I2C_Recv[w]=0;

	CloseI2C();							//close i2c if was operating earlier

//------------------------INITIALISE THE I2C MODULE FOR MASTER MODE WITH 100KHz ---------------------------
	sync_mode = SLAVE_7;
	slew = SLEW_OFF;
  
	OpenI2C(sync_mode,slew);
	
SSPADD = 0xA2;							//initialze slave address
//********************* Read the address sent by master from buffer **************
		while(DataRdyI2C()==0);			//WAIT UNTILL THE DATA IS TRANSMITTED FROM master
		temp = ReadI2C();


//********************* Data reception from master by slave *********************
		
		do
		{
		while(DataRdyI2C()==0);			//WAIT UNTILL THE DATA IS TRANSMITTED FROM master
		I2C_Recv[length++]=getcI2C();       // save byte received
		}
		while(length!=20);
		
//******************** write sequence from slave *******************************
		while(SSPSTATbits.S!=1);		//wait untill STOP CONDITION

//********************* Read the address sent by master from buffer **************
		while(DataRdyI2C()==0);			//WAIT UNTILL THE DATA IS TRANSMITTED FROM master
		temp = ReadI2C();

//********************* Slave transmission ************************************		
	if(SSPSTAT & 0x04)					//check if master is ready for reception	
	while(putsI2C(I2C_Send));			// send the data to master

//-------------TERMINATE COMMUNICATION FROM MASTER SIDE---------------
	CloseI2C();							//close I2C module
	
	while(1);							//End of program
}

