EESchema Schematic File Version 4
LIBS:EXT_LCD+TECLADO-cache
EELAYER 29 0
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
Text Label 6400 2900 2    50   ~ 0
FIL1
Text Label 5550 2900 2    50   ~ 0
FIL2
Text Label 6400 3000 2    50   ~ 0
FIL3
Text Label 5550 3000 2    50   ~ 0
FIL4
Text Label 6400 3100 2    50   ~ 0
COL1
Text Label 5550 3100 2    50   ~ 0
COL2
Text Label 6400 3200 2    50   ~ 0
COL3
Text Label 5550 3200 2    50   ~ 0
COL4
Wire Wire Line
	6150 2900 6550 2900
Wire Wire Line
	6150 3000 6550 3000
Wire Wire Line
	6150 3100 6550 3100
Wire Wire Line
	6150 3200 6550 3200
Wire Wire Line
	6150 3300 6550 3300
Wire Wire Line
	6150 3400 6550 3400
Wire Wire Line
	6150 3500 6550 3500
Wire Wire Line
	6150 3600 6550 3600
Wire Wire Line
	5650 2900 5150 2900
Wire Wire Line
	5650 3000 5150 3000
Wire Wire Line
	5150 3100 5650 3100
Wire Wire Line
	5650 3200 5150 3200
Wire Wire Line
	5650 3300 5150 3300
Wire Wire Line
	5650 3400 5150 3400
Wire Wire Line
	5650 3500 5150 3500
Wire Wire Line
	5150 3600 5650 3600
Text Label 6400 3400 2    50   ~ 0
SCK
Text Label 5550 3300 2    50   ~ 0
MISO
Text Label 6400 3300 2    50   ~ 0
MOSI
Text Label 6450 3500 2    50   ~ 0
LCD_RS
Text Label 5550 3400 2    50   ~ 0
LCD_E
$Comp
L power:GND #PWR0101
U 1 1 5CE5A54D
P 6550 4500
F 0 "#PWR0101" H 6550 4250 50  0001 C CNN
F 1 "GND" H 6555 4327 50  0000 C CNN
F 2 "" H 6550 4500 50  0001 C CNN
F 3 "" H 6550 4500 50  0001 C CNN
	1    6550 4500
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5CE5A9CB
P 5150 4450
F 0 "#PWR0102" H 5150 4300 50  0001 C CNN
F 1 "+5V" H 5165 4623 50  0000 C CNN
F 2 "" H 5150 4450 50  0001 C CNN
F 3 "" H 5150 4450 50  0001 C CNN
	1    5150 4450
	1    0    0    1   
$EndComp
Text Label 5200 3500 0    50   ~ 0
RESET-MCU
Text Label 5500 5450 2    50   ~ 0
RXD
Text Label 6300 5450 2    50   ~ 0
TXD
Wire Wire Line
	8750 2350 9050 2350
Wire Wire Line
	9050 2250 8750 2250
Wire Wire Line
	9050 2150 8750 2150
Wire Wire Line
	9050 2050 8750 2050
Wire Wire Line
	9700 4450 9700 4150
Wire Wire Line
	9800 4450 9800 4150
Wire Wire Line
	9900 4450 9900 4150
Wire Wire Line
	10000 4450 10000 4150
Text Label 8850 2350 0    50   ~ 0
FIL1
Text Label 8850 2250 0    50   ~ 0
FIL2
Text Label 8850 2150 0    50   ~ 0
FIL3
Text Label 8850 2050 0    50   ~ 0
FIL4
Text Label 9700 4250 3    50   ~ 0
COL1
Text Label 9800 4250 3    50   ~ 0
COL2
Text Label 10000 4250 3    50   ~ 0
COL4
Text Label 9900 4250 3    50   ~ 0
COL3
Text Label 9300 4250 3    50   ~ 0
FIL1k
Text Label 9400 4250 3    50   ~ 0
FIL2k
Text Label 9500 4250 3    50   ~ 0
FIL3k
Text Label 9600 4250 3    50   ~ 0
FIL4k
$Comp
L power:GND #PWR0103
U 1 1 5CAAEDCE
P 9450 2550
F 0 "#PWR0103" H 9450 2300 50  0001 C CNN
F 1 "GND" H 9455 2377 50  0000 C CNN
F 2 "" H 9450 2550 50  0001 C CNN
F 3 "" H 9450 2550 50  0001 C CNN
	1    9450 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 5CAB0E0E
P 9450 1050
F 0 "#PWR0104" H 9450 900 50  0001 C CNN
F 1 "+5V" H 9465 1223 50  0000 C CNN
F 2 "" H 9450 1050 50  0001 C CNN
F 3 "" H 9450 1050 50  0001 C CNN
	1    9450 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 1550 9050 1550
Text Label 8800 1550 0    50   ~ 0
LCD_E
Text Label 8800 1350 0    50   ~ 0
LCD_RS
Wire Wire Line
	8750 1350 9050 1350
Wire Wire Line
	9050 1450 8550 1450
Wire Wire Line
	8550 1450 8550 1650
$Comp
L Display_Character:RC1602A U1
U 1 1 5CAB7505
P 9450 1850
F 0 "U1" H 9250 2550 50  0000 C CNN
F 1 "RC1602A" H 9650 2550 50  0000 C CNN
F 2 "Display:WC1602A" H 9550 1050 50  0001 C CNN
F 3 "http://www.raystar-optronics.com/down.php?ProID=18" H 9550 1750 50  0001 C CNN
	1    9450 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5CAB5EE8
P 8550 1700
F 0 "#PWR0105" H 8550 1450 50  0001 C CNN
F 1 "GND" H 8555 1527 50  0000 C CNN
F 2 "" H 8550 1700 50  0001 C CNN
F 3 "" H 8550 1700 50  0001 C CNN
	1    8550 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5CAD2723
P 9950 1950
F 0 "#PWR0106" H 9950 1700 50  0001 C CNN
F 1 "GND" H 9955 1777 50  0000 C CNN
F 2 "" H 9950 1950 50  0001 C CNN
F 3 "" H 9950 1950 50  0001 C CNN
	1    9950 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	9950 1950 9950 2050
Wire Wire Line
	9950 2050 9850 2050
$Comp
L power:+5V #PWR0107
U 1 1 5CAD3958
P 9900 2500
F 0 "#PWR0107" H 9900 2350 50  0001 C CNN
F 1 "+5V" H 9915 2673 50  0000 C CNN
F 2 "" H 9900 2500 50  0001 C CNN
F 3 "" H 9900 2500 50  0001 C CNN
	1    9900 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	9850 2150 9900 2150
Wire Wire Line
	9900 2150 9900 2500
$Comp
L Device:R R1
U 1 1 5CBFFB89
P 10200 1850
F 0 "R1" H 10270 1896 50  0000 L CNN
F 1 "2.2k-3.3k" H 10270 1805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 10130 1850 50  0001 C CNN
F 3 "~" H 10200 1850 50  0001 C CNN
	1    10200 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 1650 10200 1650
Wire Wire Line
	10200 1650 10200 1700
Wire Wire Line
	10200 2000 10200 2050
Wire Wire Line
	10200 2050 9950 2050
Connection ~ 9950 2050
$Comp
L Connector:Conn_01x08_Male J5
U 1 1 5CE052E8
P 9650 6050
F 0 "J5" V 9850 5500 50  0000 R CNN
F 1 "Keypad4x4" V 9750 5500 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 9650 6050 50  0001 C CNN
F 3 "~" H 9650 6050 50  0001 C CNN
	1    9650 6050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9750 5850 9750 5550
Wire Wire Line
	9850 5850 9850 5550
Wire Wire Line
	9950 5850 9950 5550
Wire Wire Line
	10050 5850 10050 5550
Text Label 9750 5650 3    50   ~ 0
COL1
Text Label 9850 5650 3    50   ~ 0
COL2
Text Label 10050 5650 3    50   ~ 0
COL4
Text Label 9950 5650 3    50   ~ 0
COL3
Wire Wire Line
	9350 5550 9350 5850
Wire Wire Line
	9450 5850 9450 5550
Wire Wire Line
	9550 5850 9550 5550
Wire Wire Line
	9650 5850 9650 5550
Wire Wire Line
	9450 1050 9450 1150
Text Notes 10300 2050 0    50   ~ 0
3.3k placed
Text Label 9650 5650 3    50   ~ 0
FIL4k
Text Label 9550 5650 3    50   ~ 0
FIL3k
Text Label 9450 5650 3    50   ~ 0
FIL2k
Text Label 9350 5650 3    50   ~ 0
FIL1k
$Comp
L Diode:1N4148 D3
U 1 1 5CB1F1C7
P 9000 3750
F 0 "D3" H 9000 3966 50  0000 C CNN
F 1 "1N4148" H 9000 3875 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9000 3575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 9000 3750 50  0001 C CNN
	1    9000 3750
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D2
U 1 1 5CB1E861
P 9300 3750
F 0 "D2" H 9300 3966 50  0000 C CNN
F 1 "1N4148" H 9300 3875 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9300 3575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 9300 3750 50  0001 C CNN
	1    9300 3750
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 5CB1D915
P 9600 3750
F 0 "D1" H 9600 3966 50  0000 C CNN
F 1 "1N4148" H 9600 3875 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9600 3575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 9600 3750 50  0001 C CNN
	1    9600 3750
	0    1    1    0   
$EndComp
Text Label 9600 3200 3    50   ~ 0
FIL4
Text Label 9500 3200 3    50   ~ 0
FIL3
Text Label 9400 3200 3    50   ~ 0
FIL2
Text Label 9300 3200 3    50   ~ 0
FIL1
Wire Wire Line
	9300 3100 9300 3400
Wire Wire Line
	9300 4150 9300 4450
$Comp
L Diode:1N4148 D4
U 1 1 5CB87997
P 8650 3750
F 0 "D4" H 8650 3966 50  0000 C CNN
F 1 "1N4148" H 8650 3875 50  0000 C CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 8650 3575 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 8650 3750 50  0001 C CNN
	1    8650 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 3900 9600 4450
Wire Wire Line
	9500 3900 9300 3900
Wire Wire Line
	9500 3900 9500 4450
Wire Wire Line
	9400 4000 9000 4000
Wire Wire Line
	9000 4000 9000 3900
Wire Wire Line
	9400 4000 9400 4450
Wire Wire Line
	9300 4150 8650 4150
Wire Wire Line
	8650 4150 8650 3900
Wire Wire Line
	9600 3100 9600 3600
Wire Wire Line
	9500 3550 9300 3550
Wire Wire Line
	9300 3550 9300 3600
Wire Wire Line
	9500 3100 9500 3550
Wire Wire Line
	9400 3500 9000 3500
Wire Wire Line
	9000 3500 9000 3600
Wire Wire Line
	9400 3100 9400 3500
Wire Wire Line
	9300 3400 8650 3400
Wire Wire Line
	8650 3400 8650 3600
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J1
U 1 1 5CC9F7F7
P 5750 6950
F 0 "J1" H 5800 7267 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 5800 7176 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" H 5750 6950 50  0001 C CNN
F 3 "~" H 5750 6950 50  0001 C CNN
	1    5750 6950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x02_Odd_Even J2
U 1 1 5CCA012C
P 5800 5450
F 0 "J2" H 5850 5667 50  0000 C CNN
F 1 "Conn_02x02_Odd_Even" H 5850 5576 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Vertical" H 5800 5450 50  0001 C CNN
F 3 "~" H 5800 5450 50  0001 C CNN
	1    5800 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 5CCA0AE3
P 5450 5550
F 0 "#PWR0108" H 5450 5400 50  0001 C CNN
F 1 "+5V" H 5465 5723 50  0000 C CNN
F 2 "" H 5450 5550 50  0001 C CNN
F 3 "" H 5450 5550 50  0001 C CNN
	1    5450 5550
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5CCA0E25
P 6300 5600
F 0 "#PWR0109" H 6300 5350 50  0001 C CNN
F 1 "GND" H 6305 5427 50  0000 C CNN
F 2 "" H 6300 5600 50  0001 C CNN
F 3 "" H 6300 5600 50  0001 C CNN
	1    6300 5600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5600 5450 5350 5450
Wire Wire Line
	6100 5450 6400 5450
Wire Wire Line
	5600 5550 5450 5550
Wire Wire Line
	6100 5550 6300 5550
Wire Wire Line
	6300 5550 6300 5600
$Comp
L power:+5V #PWR0110
U 1 1 5CCA89C3
P 6300 6650
F 0 "#PWR0110" H 6300 6500 50  0001 C CNN
F 1 "+5V" H 6315 6823 50  0000 C CNN
F 2 "" H 6300 6650 50  0001 C CNN
F 3 "" H 6300 6650 50  0001 C CNN
	1    6300 6650
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5CCA8D82
P 6300 7150
F 0 "#PWR0111" H 6300 6900 50  0001 C CNN
F 1 "GND" H 6305 6977 50  0000 C CNN
F 2 "" H 6300 7150 50  0001 C CNN
F 3 "" H 6300 7150 50  0001 C CNN
	1    6300 7150
	-1   0    0    -1  
$EndComp
Text Label 5300 6850 2    50   ~ 0
MISO
Text Label 5300 6950 2    50   ~ 0
SCK
Text Label 6350 6950 2    50   ~ 0
MOSI
Wire Wire Line
	6300 6650 6300 6850
Wire Wire Line
	6300 6850 6050 6850
Wire Wire Line
	6050 6950 6450 6950
Wire Wire Line
	6050 7050 6300 7050
Wire Wire Line
	6300 7050 6300 7150
Wire Wire Line
	5550 7050 5050 7050
Wire Wire Line
	5550 6950 5050 6950
Wire Wire Line
	5550 6850 5050 6850
Text Label 5100 7050 0    50   ~ 0
RESET-MCU
Text Label 5550 3700 2    50   ~ 0
RXD
Text Label 6350 3700 2    50   ~ 0
TXD
Wire Wire Line
	5650 3700 5350 3700
Wire Wire Line
	6400 3700 6150 3700
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J3
U 1 1 5CCC8C53
P 5850 3300
F 0 "J3" H 5900 3917 50  0000 C CNN
F 1 "Conn_02x10_Odd_Even" H 5900 3826 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x10_P2.54mm_Vertical_Lock" H 5850 3300 50  0001 C CNN
F 3 "~" H 5850 3300 50  0001 C CNN
	1    5850 3300
	1    0    0    -1  
$EndComp
$Comp
L jcaf_ibrary:keypad4x4_plastic SW1
U 1 1 5CC5D653
P 9300 4550
F 0 "SW1" H 10128 4204 50  0000 L CNN
F 1 "keypad4x4_plastic" H 10128 4113 50  0000 L CNN
F 2 "jcaf_library:keypad4x4_plastic" H 9300 4550 50  0001 C CNN
F 3 "" H 9300 4550 50  0001 C CNN
	1    9300 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3600 5150 3800
Wire Wire Line
	6550 3600 6550 3800
Wire Wire Line
	6150 3800 6550 3800
Connection ~ 6550 3800
Wire Wire Line
	6550 3800 6550 4300
Wire Wire Line
	5650 3800 5150 3800
Connection ~ 5150 3800
Wire Wire Line
	5150 3800 5150 4300
$Comp
L Device:CP1 C1
U 1 1 5CC8BB27
P 5900 4300
F 0 "C1" V 6152 4300 50  0000 C CNN
F 1 "10uF/25V" V 6061 4300 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 5900 4300 50  0001 C CNN
F 3 "~" H 5900 4300 50  0001 C CNN
	1    5900 4300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5750 4300 5150 4300
Connection ~ 5150 4300
Wire Wire Line
	5150 4300 5150 4450
Wire Wire Line
	6050 4300 6550 4300
Connection ~ 6550 4300
Wire Wire Line
	6550 4300 6550 4500
Wire Wire Line
	9050 1950 9000 1950
Wire Wire Line
	9000 1950 9000 1850
Wire Wire Line
	9000 1650 9050 1650
Wire Wire Line
	9050 1750 9000 1750
Connection ~ 9000 1750
Wire Wire Line
	9000 1750 9000 1650
Wire Wire Line
	9050 1850 9000 1850
Connection ~ 9000 1850
Wire Wire Line
	9000 1850 9000 1750
Wire Wire Line
	9000 1650 8550 1650
Connection ~ 9000 1650
Connection ~ 8550 1650
Wire Wire Line
	8550 1650 8550 1700
$EndSCHEMATC
