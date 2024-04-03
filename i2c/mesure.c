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

void init_Timer0(void);

unsigned int VM1, VM2, VM3, VM4, VM5, VM6;
unsigned int FVR_CHECK = 0x0000;

/*******************************************************************************
 * FUNCTION:   void main(void)
 * PURPOSE:    Main.
 ******************************************************************************/
void main(void)
{

	// INITIALISATION

	ANSEL = 0b11111100; // ports en analogique (numérique = 0)
	ANSELH = 0b00000000;
	PORTA = 0b00000000;
	TRISA = 0b00010100;
	WPUA = 0b000000; // pas de RBPU
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

	// WPUAbits.WPUA2 = 1;

	// Configuration de l'oscillateur interne
	OSCCON = 0b01010001;  // osc interne a 16 MHz
	OSCTUNE = 0b00000000; // PLL off

	// I2C

	SSPADD = 0b11011010; // Adresse

	// FIN INITIALISATION

	while (FVR_CHECK == 0x0000)
	{
		Delay100TCYx(50); // Delay
		ConvertADC();	  // Start conversion
		while (BusyADC())
			;				   // Wait for completion
		FVR_CHECK = ReadADC(); // Read result
	}

	OpenI2C(SLAVE_7, SLEW_OFF);

	// Le TIMER 0 est à l'arrêt mais prêt à fonctionner
	// init_Timer0();

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
	}
}

//*************************************************************************************
void init_Timer0(void)
//*************************************************************************************
{
	// Initialisation du Timer 0
	INTCONbits.TMR0IF = 0; // raz flag
	INTCONbits.TMR0IE = 0; // pas IT

	// Init du registre T0CON
	T0CONbits.TMR0ON = 0; // stop timer
	T0CONbits.T08BIT = 0; // mode 16 bits
	T0CONbits.T0CS = 0;	  // horloge fclk/4
	T0CONbits.PSA = 0;	  // prescaler on
	T0CONbits.T0PS2 = 1;  // division par 128
	T0CONbits.T0PS1 = 1;
	T0CONbits.T0PS0 = 0;
	// Ttmro = 1/ (8MHz/4*128) = 64
	// 64 * 15625 = 1sec
	// 0d15625=0x3D09
	TMR0H = 0x3D; // valeur d'initialisation
	TMR0L = 0x09; // pour 1 seconde
}
