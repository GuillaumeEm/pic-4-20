# MPLAB IDE generated this makefile for use with GNU make.
# Project: TestLED.mcp
# Date: Tue Jun 04 09:33:13 2013

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

TestLED.cof : mesure.o
	$(LD) /p18LF13K22 /l"C:\mcc18\lib" /k"C:\mcc18\lkr" "mesure.o" /u_CRUNTIME /u_DEBUG /u_DEBUGCODESTART=0x1e10 /u_DEBUGCODELEN=0x1f0 /m"TestLED.map" /w /o"TestLED.cof"

mesure.o : mesure.c C:/mcc18/h/adc.h C:/mcc18/h/delays.h C:/mcc18/h/eep.h mesure.c C:/mcc18/h/p18lf13k22.h C:/mcc18/h/pconfig.h C:/mcc18/h/p18cxxx.h
	$(CC) -p=18LF13K22 /i"C:\mcc18\h" "mesure.c" -fo="mesure.o" -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "mesure.o" "TestLED.cof" "TestLED.hex" "TestLED.map"

