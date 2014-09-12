EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:em4095
LIBS:rfid-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "12 sep 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR?
U 1 1 53C90ECA
P 2900 6400
F 0 "#PWR?" H 2900 6490 20  0001 C CNN
F 1 "+5V" H 2900 6490 30  0000 C CNN
F 2 "" H 2900 6400 60  0001 C CNN
F 3 "" H 2900 6400 60  0001 C CNN
	1    2900 6400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 53C90E8C
P 1300 7150
F 0 "#PWR?" H 1300 7150 30  0001 C CNN
F 1 "GND" H 1300 7080 30  0001 C CNN
F 2 "" H 1300 7150 60  0001 C CNN
F 3 "" H 1300 7150 60  0001 C CNN
	1    1300 7150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 53C90E8A
P 1300 6450
F 0 "#PWR?" H 1300 6540 20  0001 C CNN
F 1 "+5V" H 1300 6540 30  0000 C CNN
F 2 "" H 1300 6450 60  0001 C CNN
F 3 "" H 1300 6450 60  0001 C CNN
	1    1300 6450
	1    0    0    -1  
$EndComp
$Comp
L ZENER D?
U 1 1 53C90E70
P 2500 6900
F 0 "D?" H 2500 7000 50  0000 C CNN
F 1 "3V6" H 2500 6800 40  0000 C CNN
F 2 "" H 2500 6900 60  0001 C CNN
F 3 "" H 2500 6900 60  0001 C CNN
	1    2500 6900
	0    -1   -1   0   
$EndComp
$Comp
L ZENER D?
U 1 1 53C90E64
P 2200 6900
F 0 "D?" H 2200 7000 50  0000 C CNN
F 1 "3V6" H 2200 6800 40  0000 C CNN
F 2 "" H 2200 6900 60  0001 C CNN
F 3 "" H 2200 6900 60  0001 C CNN
	1    2200 6900
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 53C90DF2
P 2750 6650
F 0 "R?" V 2830 6650 40  0000 C CNN
F 1 "68" V 2757 6651 40  0000 C CNN
F 2 "~" V 2680 6650 30  0000 C CNN
F 3 "~" H 2750 6650 30  0000 C CNN
	1    2750 6650
	0    1    -1   0   
$EndComp
$Comp
L R R?
U 1 1 53C90DEF
P 2600 6450
F 0 "R?" V 2680 6450 40  0000 C CNN
F 1 "2K2" V 2607 6451 40  0000 C CNN
F 2 "~" V 2530 6450 30  0000 C CNN
F 3 "~" H 2600 6450 30  0000 C CNN
	1    2600 6450
	0    1    -1   0   
$EndComp
$Comp
L R R?
U 1 1 53C90DD9
P 2750 6200
F 0 "R?" V 2830 6200 40  0000 C CNN
F 1 "68" V 2757 6201 40  0000 C CNN
F 2 "~" V 2680 6200 30  0000 C CNN
F 3 "~" H 2750 6200 30  0000 C CNN
	1    2750 6200
	0    1    -1   0   
$EndComp
$Comp
L USB J?
U 1 1 53C90DC8
P 1750 6300
F 0 "J?" H 1700 6700 60  0000 C CNN
F 1 "USB" V 1500 6450 60  0000 C CNN
F 2 "" H 1750 6300 60  0001 C CNN
F 3 "" H 1750 6300 60  0001 C CNN
	1    1750 6300
	1    0    0    -1  
$EndComp
$Comp
L ATMEGA8-P IC1
U 1 1 534AC529
P 5500 4950
F 0 "IC1" H 4750 6250 40  0000 L BNN
F 1 "ATMEGA8-P" H 6000 3500 40  0000 L BNN
F 2 "DIL28" H 5500 4950 30  0000 C CIN
F 3 "" H 5500 4950 60  0001 C CNN
	1    5500 4950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR6
U 1 1 534ACCC4
P 2650 550
F 0 "#PWR6" H 2650 640 20  0001 C CNN
F 1 "+5V" H 2650 640 30  0000 C CNN
F 2 "" H 2650 550 60  0001 C CNN
F 3 "" H 2650 550 60  0001 C CNN
	1    2650 550 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR12
U 1 1 534ADBDC
P 5500 6700
F 0 "#PWR12" H 5500 6700 30  0001 C CNN
F 1 "GND" H 5500 6630 30  0001 C CNN
F 2 "" H 5500 6700 60  0001 C CNN
F 3 "" H 5500 6700 60  0001 C CNN
	1    5500 6700
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL X1
U 1 1 534ADCCA
P 4150 4700
F 0 "X1" H 4150 4850 60  0000 C CNN
F 1 "16MHz" H 4150 4550 60  0000 C CNN
F 2 "~" H 4150 4700 60  0000 C CNN
F 3 "~" H 4150 4700 60  0000 C CNN
	1    4150 4700
	0    -1   -1   0   
$EndComp
$Comp
L C C4
U 1 1 534ADD31
P 3800 4400
F 0 "C4" H 3800 4500 40  0000 L CNN
F 1 "22p" H 3806 4315 40  0000 L CNN
F 2 "~" H 3838 4250 30  0000 C CNN
F 3 "~" H 3800 4400 60  0000 C CNN
	1    3800 4400
	0    -1   -1   0   
$EndComp
$Comp
L C C5
U 1 1 534ADD37
P 3800 5000
F 0 "C5" H 3800 5100 40  0000 L CNN
F 1 "22p" H 3806 4915 40  0000 L CNN
F 2 "~" H 3838 4850 30  0000 C CNN
F 3 "~" H 3800 5000 60  0000 C CNN
	1    3800 5000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR8
U 1 1 534ADE03
P 3600 5200
F 0 "#PWR8" H 3600 5200 30  0001 C CNN
F 1 "GND" H 3600 5130 30  0001 C CNN
F 2 "" H 3600 5200 60  0001 C CNN
F 3 "" H 3600 5200 60  0001 C CNN
	1    3600 5200
	1    0    0    -1  
$EndComp
$Comp
L EM4095 IC?
U 1 1 5412E927
P 7900 2300
F 0 "IC?" H 7300 3000 40  0000 L BNN
F 1 "EM4095" H 8200 1600 40  0000 L BNN
F 2 "SO16" H 7850 2350 30  0000 C CIN
F 3 "" H 7600 2250 60  0000 C CNN
	1    7900 2300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5412EAA8
P 6850 2650
F 0 "#PWR?" H 6850 2740 20  0001 C CNN
F 1 "+5V" H 6850 2740 30  0000 C CNN
F 2 "" H 6850 2650 60  0001 C CNN
F 3 "" H 6850 2650 60  0001 C CNN
	1    6850 2650
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5412EABD
P 6800 1750
F 0 "#PWR?" H 6800 1750 30  0001 C CNN
F 1 "GND" H 6800 1680 30  0001 C CNN
F 2 "" H 6800 1750 60  0001 C CNN
F 3 "" H 6800 1750 60  0001 C CNN
	1    6800 1750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5412EBEF
P 6800 2350
F 0 "#PWR?" H 6800 2350 30  0001 C CNN
F 1 "GND" H 6800 2280 30  0001 C CNN
F 2 "" H 6800 2350 60  0001 C CNN
F 3 "" H 6800 2350 60  0001 C CNN
	1    6800 2350
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5412EC59
P 9400 2350
F 0 "#PWR?" H 9400 2350 30  0001 C CNN
F 1 "GND" H 9400 2280 30  0001 C CNN
F 2 "" H 9400 2350 60  0001 C CNN
F 3 "" H 9400 2350 60  0001 C CNN
	1    9400 2350
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5412ECC4
P 8800 3050
F 0 "C?" H 8800 3150 40  0000 L CNN
F 1 "100n" H 8806 2965 40  0000 L CNN
F 2 "~" H 8838 2900 30  0000 C CNN
F 3 "~" H 8800 3050 60  0000 C CNN
	1    8800 3050
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5412ED50
P 9250 2700
F 0 "C?" H 9250 2800 40  0000 L CNN
F 1 "1n" H 9256 2615 40  0000 L CNN
F 2 "~" H 9288 2550 30  0000 C CNN
F 3 "~" H 9250 2700 60  0000 C CNN
	1    9250 2700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5412ED62
P 9450 2800
F 0 "#PWR?" H 9450 2800 30  0001 C CNN
F 1 "GND" H 9450 2730 30  0001 C CNN
F 2 "" H 9450 2800 60  0001 C CNN
F 3 "" H 9450 2800 60  0001 C CNN
	1    9450 2800
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5412EE60
P 9050 1900
F 0 "C?" H 9050 2000 40  0000 L CNN
F 1 "100n" H 9056 1815 40  0000 L CNN
F 2 "~" H 9088 1750 30  0000 C CNN
F 3 "~" H 9050 1900 60  0000 C CNN
	1    9050 1900
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 5412EE66
P 9050 1700
F 0 "C?" H 9050 1800 40  0000 L CNN
F 1 "100n" H 9056 1615 40  0000 L CNN
F 2 "~" H 9088 1550 30  0000 C CNN
F 3 "~" H 9050 1700 60  0000 C CNN
	1    9050 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5412EE6C
P 9300 1700
F 0 "#PWR?" H 9300 1700 30  0001 C CNN
F 1 "GND" H 9300 1630 30  0001 C CNN
F 2 "" H 9300 1700 60  0001 C CNN
F 3 "" H 9300 1700 60  0001 C CNN
	1    9300 1700
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5412EE72
P 9300 1900
F 0 "#PWR?" H 9300 1900 30  0001 C CNN
F 1 "GND" H 9300 1830 30  0001 C CNN
F 2 "" H 9300 1900 60  0001 C CNN
F 3 "" H 9300 1900 60  0001 C CNN
	1    9300 1900
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5412EE78
P 6350 2700
F 0 "C?" H 6350 2800 40  0000 L CNN
F 1 "RES" H 6356 2615 40  0000 L CNN
F 2 "~" H 6388 2550 30  0000 C CNN
F 3 "~" H 6350 2700 60  0000 C CNN
	1    6350 2700
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5412EE7E
P 6650 2500
F 0 "R?" V 6730 2500 40  0000 C CNN
F 1 "10R" V 6657 2501 40  0000 C CNN
F 2 "~" V 6580 2500 30  0000 C CNN
F 3 "~" H 6650 2500 30  0000 C CNN
	1    6650 2500
	0    1    -1   0   
$EndComp
$Comp
L C C?
U 1 1 5412EFAC
P 6250 3100
F 0 "C?" H 6250 3200 40  0000 L CNN
F 1 "DV1" H 6256 3015 40  0000 L CNN
F 2 "~" H 6288 2950 30  0000 C CNN
F 3 "~" H 6250 3100 60  0000 C CNN
	1    6250 3100
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5412EFB2
P 7150 3300
F 0 "C?" H 7150 3400 40  0000 L CNN
F 1 "DV2" H 7156 3215 40  0000 L CNN
F 2 "~" H 7188 3150 30  0000 C CNN
F 3 "~" H 7150 3300 60  0000 C CNN
	1    7150 3300
	0    -1   -1   0   
$EndComp
$Comp
L INDUCTOR L?
U 1 1 5412EFCD
P 6600 2050
F 0 "L?" V 6550 2050 40  0000 C CNN
F 1 "INDUCTOR" V 6700 2050 40  0000 C CNN
F 2 "~" H 6600 2050 60  0000 C CNN
F 3 "~" H 6600 2050 60  0000 C CNN
	1    6600 2050
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5412F8E2
P 6900 1150
F 0 "C?" H 6900 1250 40  0000 L CNN
F 1 "100n" H 6906 1065 40  0000 L CNN
F 2 "~" H 6938 1000 30  0000 C CNN
F 3 "~" H 6900 1150 60  0000 C CNN
	1    6900 1150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5412F8E8
P 7200 1150
F 0 "C?" H 7200 1250 40  0000 L CNN
F 1 "1n" H 7206 1065 40  0000 L CNN
F 2 "~" H 7238 1000 30  0000 C CNN
F 3 "~" H 7200 1150 60  0000 C CNN
	1    7200 1150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5412F8EE
P 7050 1400
F 0 "#PWR?" H 7050 1400 30  0001 C CNN
F 1 "GND" H 7050 1330 30  0001 C CNN
F 2 "" H 7050 1400 60  0001 C CNN
F 3 "" H 7050 1400 60  0001 C CNN
	1    7050 1400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5412F8F4
P 7050 900
F 0 "#PWR?" H 7050 990 20  0001 C CNN
F 1 "+5V" H 7050 990 30  0000 C CNN
F 2 "" H 7050 900 60  0001 C CNN
F 3 "" H 7050 900 60  0001 C CNN
	1    7050 900 
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5412FCA7
P 9100 2350
F 0 "R?" V 9180 2350 40  0000 C CNN
F 1 "0R" V 9107 2351 40  0000 C CNN
F 2 "~" V 9030 2350 30  0000 C CNN
F 3 "~" H 9100 2350 30  0000 C CNN
	1    9100 2350
	0    1    -1   0   
$EndComp
$Comp
L +5VA #PWR?
U 1 1 5413002A
P 8700 900
F 0 "#PWR?" H 8700 1030 20  0001 C CNN
F 1 "+5VA" H 8700 1000 30  0000 C CNN
F 2 "" H 8700 900 60  0000 C CNN
F 3 "" H 8700 900 60  0000 C CNN
	1    8700 900 
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 54130039
P 6600 1150
F 0 "C?" H 6650 1250 50  0000 L CNN
F 1 "4.7u" H 6650 1050 50  0000 L CNN
F 2 "~" H 6600 1150 60  0000 C CNN
F 3 "~" H 6600 1150 60  0000 C CNN
	1    6600 1150
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L?
U 1 1 541303C4
P 7550 950
F 0 "L?" V 7500 950 40  0000 C CNN
F 1 "22uH 3A" V 7650 950 40  0000 C CNN
F 2 "~" H 7550 950 60  0000 C CNN
F 3 "~" H 7550 950 60  0000 C CNN
	1    7550 950 
	0    -1   -1   0   
$EndComp
$Comp
L CP1 C?
U 1 1 541303CB
P 8550 1150
F 0 "C?" H 8600 1250 50  0000 L CNN
F 1 "100u" H 8600 1050 50  0000 L CNN
F 2 "~" H 8550 1150 60  0000 C CNN
F 3 "~" H 8550 1150 60  0000 C CNN
	1    8550 1150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 541303D1
P 8800 1150
F 0 "C?" H 8800 1250 40  0000 L CNN
F 1 "100n" H 8806 1065 40  0000 L CNN
F 2 "~" H 8838 1000 30  0000 C CNN
F 3 "~" H 8800 1150 60  0000 C CNN
	1    8800 1150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 541303D7
P 9050 1150
F 0 "C?" H 9050 1250 40  0000 L CNN
F 1 "1n" H 9056 1065 40  0000 L CNN
F 2 "~" H 9088 1000 30  0000 C CNN
F 3 "~" H 9050 1150 60  0000 C CNN
	1    9050 1150
	1    0    0    -1  
$EndComp
$Comp
L +5VA #PWR?
U 1 1 54130A98
P 6850 2200
F 0 "#PWR?" H 6850 2330 20  0001 C CNN
F 1 "+5VA" H 6850 2300 30  0000 C CNN
F 2 "" H 6850 2200 60  0000 C CNN
F 3 "" H 6850 2200 60  0000 C CNN
	1    6850 2200
	0    -1   -1   0   
$EndComp
$Comp
L CP1 C?
U 1 1 54130AA3
P 8300 1150
F 0 "C?" H 8350 1250 50  0000 L CNN
F 1 "100u" H 8350 1050 50  0000 L CNN
F 2 "~" H 8300 1150 60  0000 C CNN
F 3 "~" H 8300 1150 60  0000 C CNN
	1    8300 1150
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 54130AA9
P 8050 1150
F 0 "C?" H 8100 1250 50  0000 L CNN
F 1 "100u" H 8100 1050 50  0000 L CNN
F 2 "~" H 8050 1150 60  0000 C CNN
F 3 "~" H 8050 1150 60  0000 C CNN
	1    8050 1150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 54130FF1
P 6050 3100
F 0 "C?" H 6050 3200 40  0000 L CNN
F 1 "DV1" H 6056 3015 40  0000 L CNN
F 2 "~" H 6088 2950 30  0000 C CNN
F 3 "~" H 6050 3100 60  0000 C CNN
	1    6050 3100
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 54131001
P 6450 3100
F 0 "C?" H 6450 3200 40  0000 L CNN
F 1 "DV1" H 6456 3015 40  0000 L CNN
F 2 "~" H 6488 2950 30  0000 C CNN
F 3 "~" H 6450 3100 60  0000 C CNN
	1    6450 3100
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 54131049
P 6150 2700
F 0 "C?" H 6150 2800 40  0000 L CNN
F 1 "RES" H 6156 2615 40  0000 L CNN
F 2 "~" H 6188 2550 30  0000 C CNN
F 3 "~" H 6150 2700 60  0000 C CNN
	1    6150 2700
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5413104F
P 5950 2700
F 0 "C?" H 5950 2800 40  0000 L CNN
F 1 "RES" H 5956 2615 40  0000 L CNN
F 2 "~" H 5988 2550 30  0000 C CNN
F 3 "~" H 5950 2700 60  0000 C CNN
	1    5950 2700
	1    0    0    -1  
$EndComp
Connection ~ 2200 7100
Connection ~ 1300 7100
Wire Wire Line
	1300 7100 2500 7100
Wire Wire Line
	2900 6400 2900 6450
Wire Wire Line
	2900 6450 2850 6450
Connection ~ 2200 6500
Wire Wire Line
	2100 6500 2200 6500
Wire Wire Line
	1300 6450 1300 6500
Wire Wire Line
	1300 6500 1350 6500
Wire Wire Line
	1300 7150 1300 6650
Wire Wire Line
	1300 6650 1350 6650
Wire Wire Line
	5500 6450 5500 6700
Wire Wire Line
	4000 4400 4600 4400
Wire Wire Line
	4600 4400 4600 4550
Wire Wire Line
	4600 4750 4600 5000
Wire Wire Line
	4600 5000 4000 5000
Connection ~ 4150 4400
Connection ~ 4150 5000
Wire Wire Line
	3600 4400 3600 5200
Connection ~ 3600 5000
Wire Wire Line
	6650 3950 6500 3950
Wire Wire Line
	6500 5050 6700 5050
Wire Wire Line
	6700 5050 6700 4900
Wire Wire Line
	2100 6750 2100 6850
Wire Wire Line
	2100 6850 1300 6850
Wire Wire Line
	1350 6750 1300 6750
Connection ~ 1300 6750
Connection ~ 1300 6850
Wire Wire Line
	2500 6200 2200 6200
Wire Wire Line
	2200 6200 2200 6700
Wire Wire Line
	2100 6650 2500 6650
Wire Wire Line
	2500 6650 2500 6700
Wire Wire Line
	2350 6450 2350 6650
Connection ~ 2350 6650
Wire Wire Line
	6800 1750 6950 1750
Wire Wire Line
	6850 2200 6950 2200
Wire Wire Line
	6850 2650 6950 2650
Wire Wire Line
	6800 2350 6950 2350
Wire Wire Line
	8850 1900 8800 1900
Wire Wire Line
	8800 1750 8850 1750
Wire Wire Line
	8850 1750 8850 1700
Wire Wire Line
	9250 1700 9300 1700
Wire Wire Line
	9250 1900 9300 1900
Wire Wire Line
	6600 950  7250 950 
Wire Wire Line
	6600 1350 9300 1350
Wire Wire Line
	7050 1400 7050 1350
Connection ~ 7050 1350
Wire Wire Line
	7050 900  7050 950 
Connection ~ 7050 950 
Wire Wire Line
	8800 2350 8850 2350
Wire Wire Line
	9350 2350 9400 2350
Connection ~ 6900 950 
Connection ~ 6900 1350
Wire Wire Line
	7850 950  9300 950 
Connection ~ 8550 950 
Connection ~ 8800 950 
Wire Wire Line
	8700 900  8700 950 
Connection ~ 8700 950 
Connection ~ 8800 1350
Connection ~ 7200 1350
Connection ~ 8550 1350
Connection ~ 7200 950 
Connection ~ 8300 950 
Connection ~ 8050 950 
Wire Wire Line
	5950 2500 6400 2500
Connection ~ 6350 2500
Connection ~ 6150 2500
Wire Wire Line
	6050 3300 6950 3300
Wire Wire Line
	7350 3300 7350 3400
$Comp
L GND #PWR?
U 1 1 541312FA
P 7350 3400
F 0 "#PWR?" H 7350 3400 30  0001 C CNN
F 1 "GND" H 7350 3330 30  0001 C CNN
F 2 "" H 7350 3400 60  0001 C CNN
F 3 "" H 7350 3400 60  0001 C CNN
	1    7350 3400
	1    0    0    -1  
$EndComp
Connection ~ 6450 3300
Connection ~ 6250 3300
Connection ~ 6450 2900
Connection ~ 6350 2900
Connection ~ 6250 2900
Connection ~ 6150 2900
Connection ~ 6050 2900
Connection ~ 5950 2900
Wire Wire Line
	6300 2050 5750 2050
Wire Wire Line
	5750 2050 5750 2900
Wire Wire Line
	6900 2050 6950 2050
Wire Wire Line
	6950 2500 6900 2500
Wire Wire Line
	8800 3250 8950 3250
Wire Wire Line
	8950 3250 8950 2650
Wire Wire Line
	8950 2650 8800 2650
Wire Wire Line
	8800 2800 8800 2850
$Comp
L C C?
U 1 1 541314DC
P 9250 2500
F 0 "C?" H 9250 2600 40  0000 L CNN
F 1 "1u" H 9256 2415 40  0000 L CNN
F 2 "~" H 9288 2350 30  0000 C CNN
F 3 "~" H 9250 2500 60  0000 C CNN
	1    9250 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 2500 9050 2500
Wire Wire Line
	9050 2500 9050 2700
Wire Wire Line
	9450 2500 9450 2800
Connection ~ 9450 2700
Connection ~ 9050 2500
Wire Wire Line
	6950 3300 6950 2800
Wire Wire Line
	5750 2900 6450 2900
Connection ~ 6950 3300
$Comp
L ZENER D?
U 1 1 541317EB
P 9300 1150
F 0 "D?" H 9300 1250 50  0000 C CNN
F 1 "5V6" H 9300 1050 40  0000 C CNN
F 2 "~" H 9300 1150 60  0000 C CNN
F 3 "~" H 9300 1150 60  0000 C CNN
	1    9300 1150
	0    -1   -1   0   
$EndComp
Connection ~ 9050 950 
Connection ~ 9050 1350
$EndSCHEMATC
