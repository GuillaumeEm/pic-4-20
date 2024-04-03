#include <p18lf13k22.h>
#include <adc.h>
#include <delays.h>
#include <i2c.h>

#define V1 ADC_CH7
#define V2 ADC_CH2
#define V3 ADC_CH3
#define V4 ADC_CH4
#define V5 ADC_CH5
#define V6 ADC_CH6

#define led PORTBbits.RB5

void Initialisation(void);
void Conversion(unsigned int *Canal_lecture, unsigned int *Valeur_AOP_Correspondante);

unsigned int VM1 = 0, VM2 = 0, VM3 = 0, VM4 = 0, VM5 = 0, VM6 = 0; // 6 variables du convertisseur (de 0x000 à 0x3FF )
unsigned int FVR_CHECK = 0x0000;								   // Vérification simple pour le FVR
unsigned char ConvertisseurSelect = 0;							   // Sélection de la variable à envoyer

/*******************************************************************************
		Fonction MAIN
 ******************************************************************************/
void main(void)
{

	// INITIALISATION
	Initialisation();

	while (FVR_CHECK != 0x03FF)
	{
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;				   // Wait for completion
		FVR_CHECK = ReadADC(); // Read result
	}

	while (1)
	{

		SetChanADC(V1);	  // conversion de +V1
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;			 // Wait for completion
		VM1 = ReadADC(); // Read result

		SetChanADC(V2);	  // conversion de +V2
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;			 // Wait for completion
		VM2 = ReadADC(); // Read result

		SetChanADC(V3);	  // conversion de +V3
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;			 // Wait for completion
		VM3 = ReadADC(); // Read result

		SetChanADC(V4);	  // conversion de +V4
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;			 // Wait for completion
		VM4 = ReadADC(); // Read result

		SetChanADC(V5);	  // conversion de +V5
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;			 // Wait for completion
		VM5 = ReadADC(); // Read result

		SetChanADC(V6);	  // conversion de +V6
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;			 // Wait for completion
		VM6 = ReadADC(); // Read result

		led = 1;
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		led = 0;
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		Delay100TCYx(8000);
		Delay100TCYx(8000);

		CloseI2C();
		OpenI2C(SLAVE_7, SLEW_OFF);

		ConvertisseurSelect = 0;
		if (DataRdyI2C())
		{
			ConvertisseurSelect = getcI2C();
		}
		IdleI2C();
		if (ConvertisseurSelect == 0x01)
		{
			StartI2C();
			putsI2C(VM1);
			StopI2C();
		}
		else
		{
		}
	}
}

void Initialisation(void)
{

	ANSEL = 0b11111100; // Ports en analogique (numérique = 0) RA0 et RA1 à 0
	ANSELH = 0b00000000;
	PORTA = 0b00000000;
	TRISA = 0b00010100; // TRISA mise de
	PORTB = 0b00000000;
	TRISB = 0b00000000;
	WPUB = 0b00000000;	// pas de RBPU
	PORTC = 0b01000100; // EN=1
	TRISC = 0b00001111;

	// FVR

	VREFCON0 = 0xA0; // activation du FVR
	VREFCON1 = 0x00;

	// Convertisseur

	ADCON0 = 0x3D; // activation du convertisseur
	ADCON1 = 0x08; // FVR et Vss
	ADCON2 = 0b10101101;

	// Configuration de l'oscillateur interne
	OSCCON = 0b01010001;  // Osc interne à 16 MHz
	OSCTUNE = 0b00000000; // PLL off

	// I2C
	SSPADD = 0b11011010; // Adresse I2C (0x6D)
}
