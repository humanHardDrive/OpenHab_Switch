EESchema Schematic File Version 4
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
$Comp
L Converter_ACDC:IRM-02-3.3S PS?
U 1 1 5DC4C73C
P 3100 3050
F 0 "PS?" H 3100 3375 50  0000 C CNN
F 1 "IRM-02-3.3S" H 3100 3284 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_MeanWell_IRM-02-xx_SMD" H 3100 2750 50  0001 C CNN
F 3 "https://www.meanwell.com/Upload/PDF/IRM-02/IRM-02-SPEC.PDF" H 3100 3050 50  0001 C CNN
	1    3100 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C?
U 1 1 5DC4DBF1
P 3900 3100
F 0 "C?" H 4015 3146 50  0000 L CNN
F 1 "0.1uF" H 4015 3055 50  0000 L CNN
F 2 "" H 3900 3100 50  0001 C CNN
F 3 "~" H 3900 3100 50  0001 C CNN
	1    3900 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C?
U 1 1 5DC4E2BB
P 4350 3100
F 0 "C?" H 4465 3146 50  0000 L CNN
F 1 "1uF" H 4465 3055 50  0000 L CNN
F 2 "" H 4350 3100 50  0001 C CNN
F 3 "~" H 4350 3100 50  0001 C CNN
	1    4350 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2950 3900 2950
Wire Wire Line
	3900 2950 4350 2950
Connection ~ 3900 2950
Wire Wire Line
	3500 3150 3500 3250
Wire Wire Line
	3500 3250 3900 3250
Wire Wire Line
	3900 3250 4350 3250
Connection ~ 3900 3250
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY?
U 1 1 5DC4EB4A
P 3900 2800
F 0 "#SUPPLY?" H 3950 2800 45  0001 L BNN
F 1 "3.3V" H 3900 3076 45  0000 C CNN
F 2 "XXX-00000" H 3900 2981 60  0000 C CNN
F 3 "" H 3900 2800 60  0001 C CNN
	1    3900 2800
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND?
U 1 1 5DC4EFF8
P 3900 3450
F 0 "#GND?" H 3950 3400 45  0001 L BNN
F 1 "GND" H 3900 3280 45  0000 C CNN
F 2 "" H 3900 3350 60  0001 C CNN
F 3 "" H 3900 3350 60  0001 C CNN
	1    3900 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3450 3900 3250
Wire Wire Line
	3900 2950 3900 2800
$Comp
L RF_Module:ESP-07 U?
U 1 1 5DC51DFF
P 7500 2750
F 0 "U?" H 7300 3800 50  0000 C CNN
F 1 "ESP-07" H 7500 3640 50  0000 C CNN
F 2 "RF_Module:ESP-07" H 7500 2750 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 7150 2850 50  0001 C CNN
	1    7500 2750
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:3.3V #SUPPLY?
U 1 1 5DC5348D
P 7500 1650
F 0 "#SUPPLY?" H 7550 1650 45  0001 L BNN
F 1 "3.3V" H 7500 1926 45  0000 C CNN
F 2 "XXX-00000" H 7500 1831 60  0000 C CNN
F 3 "" H 7500 1650 60  0001 C CNN
	1    7500 1650
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-PowerSymbols:GND #GND?
U 1 1 5DC53DE4
P 7500 3600
F 0 "#GND?" H 7550 3550 45  0001 L BNN
F 1 "GND" H 7500 3430 45  0000 C CNN
F 2 "" H 7500 3500 60  0001 C CNN
F 3 "" H 7500 3500 60  0001 C CNN
	1    7500 3600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5DC56D08
P 5900 2150
F 0 "SW?" H 5900 2435 50  0000 C CNN
F 1 "SW_Push" H 5900 2344 50  0000 C CNN
F 2 "" H 5900 2350 50  0001 C CNN
F 3 "~" H 5900 2350 50  0001 C CNN
	1    5900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3450 7500 3600
Wire Wire Line
	7500 1650 7500 1950
$Comp
L Switch:SW_Push SW?
U 1 1 5DC58780
P 9100 2100
F 0 "SW?" H 9100 2385 50  0000 C CNN
F 1 "SW_Push" H 9100 2294 50  0000 C CNN
F 2 "" H 9100 2300 50  0001 C CNN
F 3 "~" H 9100 2300 50  0001 C CNN
	1    9100 2100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
