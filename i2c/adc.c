/**********************************************************************
* 2009 Microchip Technology Inc.
*
* FileName:        	adc.c
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
* signal to be converted is fed to AN0 channel.
**********************************************************************/

#define USE_OR_MASKS
#include <p18cxxx.h>
#include "adc.h"

//-------------------------------Configuration setting ----------------------------------------------
/**
	* Oscillator is configured as HS
	* Fail safe monitor is enabled
	* watch dog timer is disabled
	* Extended instruction mode is disabled
	* oscillator switch over is enabled	
*/
#if defined(__18F4685)				//If the selected device if PIC18F4685, then apply below settings else user will have to set
#pragma config OSC=HS, FCMEN=ON, WDT=OFF, IESO=ON, XINST=OFF, LVP=OFF 
#endif



unsigned int ADCResult=0;
float voltage=0;

void main(void)
{	

	unsigned char channel=0x00,config1=0x00,config2=0x00,config3=0x00,portconfig=0x00,i=0;

//----- clear adc interrupt and turn off adc if in case was on prerviously---------------		
	CloseADC();	

//-------------------------initialize adc---------------------------------------------------------------
/**** ADC configured for:
	* FOSC/2 as conversion clock
	* Result is right justified
	* Aquisition time of 2 AD
	* Channel 1 for sampling
	* ADC interrupt on
	* ADC reference voltage from VDD & VSS
*/
	config1 = ADC_FOSC_2 | ADC_RIGHT_JUST | ADC_2_TAD ;
	config2 = ADC_CH0 | ADC_INT_ON | ADC_REF_VDD_VSS ;
	portconfig = ADC_15ANA ;
	OpenADC(config1,config2,portconfig);


//------------------------------initialize the adc interrupt and enable them-------------------------------------	
	ADC_INT_ENABLE(); 

//-----------------------sample and convert-------------------------------- -------------------------
	for(i=0;i<16;i++)
	{
	ConvertADC();
    while(BusyADC());	
	ADCResult += (unsigned int) ReadADC();
	}
	ADCResult /= 16;
	voltage = (ADCResult*5.0)/1024; // convert ADC count into voltage
	
//----------------------------------------------------------------------------------------------------------- 
    CloseADC(); 		//turn off ADC
	
	while(1);						//End of program 
}    
  
