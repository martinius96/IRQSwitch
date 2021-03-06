/**
* This file is a part of examples of a IRQSwitch library.
*
* Created on:  	31. 10. 2018
* Updated on: 	12.02.2020
* Author:    	Denis Colesnicov <eugustus@gmail.com>
* Licence:   	MIT
* Home:    		https://github.com/colesnicov/IRQSwitch
* Description:	Priklad pouziti s prerusenim. Jsou zde ukazany vsechny schopnosti knihovny.
* Note:    		Pozor! Metoda getClickCount() ma smysl, je pouzitelna pouze, v pripade pouziti externiho preruseni pro zmenu stavu tlacitka!!
*/


#include <Arduino.h>

#include "IRQSwitch/IRQSwitchArduino.hpp"
#include "IRQSwitch/IRQSwitchConfig.h"
#include "IRQSwitch/IRQSwitch.hpp"


// Definice pinu
#define BTN_one 2
#define BTN_two 3

// Objekty predstavujici tlacitka
IRQSwitch btn_two;
IRQSwitch btn_one;

// Spravce obsluhy stavu tlacitek
IRQSwitchArduino handler;

void buttonProccess() {
	handler.Update(millis());
}


void setup() {
	Serial.begin(115200);

	Serial.print("IRQSwitch Version ");
	Serial.println(IRQSwitch_Version);

	// Nastavuji piny jako vystup.
	pinMode(BTN_one, INPUT);
	pinMode(BTN_two, INPUT);

	// Zapinam interni PULL_UP rezistory.
	/* Odkomentovat, pokud nejsou pripojeny externi PULLUP odpory */
	//digitalWrite(BTN_one, HIGH);
	//digitalWrite(BTN_two, HIGH);

	handler.AddButton(&btn_one, BTN_one);
	handler.AddButton(&btn_two, BTN_two);

	// Navesuji preruseni.
	attachInterrupt(digitalPinToInterrupt(BTN_one), buttonProccess, CHANGE);
	attachInterrupt(digitalPinToInterrupt(BTN_two), buttonProccess, CHANGE);

	Serial.println("Ready!\n\n");

}

void loop() {

	// Vypis stavu tlacitek.
	if (btn_one.isClicked()) {
		Serial.println("Button 1 clicked!");
	}

	if (btn_two.isClicked()) {
		Serial.println("Button 2 clicked!");
	}

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
	{
		if (btn_one.isHolded(millis())) {
			Serial.println("Button 1 holded!");
		}

		if (btn_two.isHolded(millis())) {
			Serial.println("Button 2 holded!");
		}
	}
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_HELD_TIME
	{
		if (btn_one.isHolded(millis())) {
			Serial.print("Button 1 has holded state: '");
			Serial.print(btn_one.getHoldedTime(millis()));
			Serial.println("' ms");
		}

		if (btn_two.isHolded(millis())) {
			Serial.print("Button 2 has holded state: '");
			Serial.print(btn_two.getHoldedTime(millis()));
			Serial.println("' ms");
		}
	}
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
	{
		// Prvni tlacitko je bez automatickeho resetovani pocitadla stisku tlacitka.
		uint8_t count1 = btn_one.getClickCount();

		// Druhe tlacitko s automatickym resetovanim pocitadla stisknuti tlacitka.
		uint8_t count2 = btn_two.getClickCountWithReset();

		if (count1 > 0) {
			Serial.print("Button 1 has '");
			Serial.print(count1);
			Serial.println("' clicks");
		}

		if (count1 == IRQSWITCH_IMPLEMENT_CLICK_COUNT)
		// Pokud je dosazen limit poctu stisknuti, proved reset pocitadla stisku
		{
			btn_one.cleanClickCount();
			Serial.println("Reset clicks counter.");
		}

		if (count2 > 0) {
			Serial.print("Button 2 has '");
			Serial.print(count2);
			Serial.println("' clicks");
		}
	}
#endif

	// Pockame 2 sekundy v necinosti
	delay(2000);

}

















