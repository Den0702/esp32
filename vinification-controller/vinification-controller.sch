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
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Screw_Terminal_1x02 J?
U 1 1 59DF348F
P 2800 1150
F 0 "J?" H 2800 1400 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 2650 1150 50  0000 C TNN
F 2 "" H 2800 925 50  0001 C CNN
F 3 "" H 2775 1150 50  0001 C CNN
	1    2800 1150
	1    0    0    -1  
$EndComp
$Comp
L IRF540N Q?
U 1 1 59DF350E
P 3800 2950
F 0 "Q?" H 4050 3025 50  0000 L CNN
F 1 "IRF540N" H 4050 2950 50  0000 L CNN
F 2 "TO-220" H 4050 2875 50  0000 L CIN
F 3 "" H 3800 2950 50  0000 L CNN
	1    3800 2950
	0    -1   1    0   
$EndComp
$Comp
L IRF540N Q?
U 1 1 59DF35BF
P 3800 2100
F 0 "Q?" H 4050 2175 50  0000 L CNN
F 1 "IRF540N" H 4050 2100 50  0000 L CNN
F 2 "TO-220" H 4050 2025 50  0000 L CIN
F 3 "" H 3800 2100 50  0000 L CNN
	1    3800 2100
	0    -1   1    0   
$EndComp
$Comp
L Screw_Terminal_1x02 J?
U 1 1 59DF3638
P 2800 3150
F 0 "J?" H 2800 3400 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 2650 3150 50  0000 C TNN
F 2 "" H 2800 2925 50  0001 C CNN
F 3 "" H 2775 3150 50  0001 C CNN
	1    2800 3150
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x02 J?
U 1 1 59DF36AF
P 2800 2300
F 0 "J?" H 2800 2550 50  0000 C TNN
F 1 "Screw_Terminal_1x02" V 2650 2300 50  0000 C TNN
F 2 "" H 2800 2075 50  0001 C CNN
F 3 "" H 2775 2300 50  0001 C CNN
	1    2800 2300
	1    0    0    -1  
$EndComp
Entry Bus Bus
	3350 2400 3450 2500
Wire Bus Line
	3000 2400 3350 2400
Entry Bus Bus
	3350 3250 3450 3350
Wire Bus Line
	3350 3250 3000 3250
Wire Bus Line
	3450 1350 3450 3350
Entry Bus Bus
	3350 1250 3450 1350
Wire Bus Line
	3000 1250 3350 1250
Wire Bus Line
	3600 2200 3000 2200
Wire Bus Line
	3000 1050 4000 1050
Wire Bus Line
	4000 1050 4000 3050
Wire Bus Line
	3000 3050 3600 3050
$Comp
L +12V #PWR?
U 1 1 59DF3F57
P 2950 1050
F 0 "#PWR?" H 2950 900 50  0001 C CNN
F 1 "+12V" H 2950 1190 50  0000 C CNN
F 2 "" H 2950 1050 50  0000 C CNN
F 3 "" H 2950 1050 50  0000 C CNN
	1    2950 1050
	0    1    1    0   
$EndComp
$Comp
L Earth #PWR?
U 1 1 59DF3FA8
P 3000 1250
F 0 "#PWR?" H 3000 1000 50  0001 C CNN
F 1 "Earth" H 3000 1100 50  0001 C CNN
F 2 "" H 3000 1250 50  0000 C CNN
F 3 "" H 3000 1250 50  0000 C CNN
	1    3000 1250
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
