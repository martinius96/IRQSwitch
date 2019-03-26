/**
 * This file is a part of examples of a IRQSwitch Arduino library.
 *
 * File:		examples/Basic/Basic.ino
 * Created on:	31. 10. 2018
 * Author:		Denis Colesnicov <eugustus@gmail.com>
 * Licence:		MIT
 * Home:		https://github.com/colesnicov/IRQSwitch
 * Description:	Priklad pouziti Externich preruseni. Jsou zde ukazany vsechny schopnosti knihovny.
 * Note:		Pozor! Metoda getClickCount() ma smysl, je pouzitelna pouze, v pripade pouziti externiho preruseni pro zmenu stavu tlacitka!!
 * Note:		Pozor! Program byl testovan na Arduino UNO/AtMega328 a pouzita preruseni jsou INT0 a INT1.
 */

#include <Arduino.h>

//#define IRQSWITCH_IMPLEMENT_CLICK_HELD 0 // Odkomentovat pro zabraneni teto funkcionality!
#define IRQSWITCH_IMPLEMENT_CLICK_COUNT 14 // Maximalni pocet pocitanych kliknuti na tlacitko!
#include <IRQSwitch.hpp>

// Definice pinu
#define BTN_one	2
#define BTN_two	3

// Vypsat cas zpracovani obsluhy tlacitek?
#define DEBUG	0

// Objekty predstavujici tlacitka
IRQSwitch btn_two;
IRQSwitch btn_one;

// Prevence pred stiskem nekolika tlacitek soucasne.
volatile uint8_t last_btn_clicked = 0;

#if DEBUG
uint32_t delta = 0;
#endif

void buttonProccess()
{
#if DEBUG
	uint32_t start = millis();
#endif

	// Millisekundy pro detekci dlouheho stisku tlacitka.
	uint32_t ms = millis();

	// Test button 1
	if (digitalRead(BTN_one) == LOW)
	// Tlacitko stisknute
	{
		if (last_btn_clicked == 0)
		// Zadne jine tlacitko stisknute neni.
		{
			btn_one.setClickStart(ms); // Nastaveni tlacitka jako "PRESSED".
			last_btn_clicked = BTN_one; // Zapamatovani ID stisknuteho tlacitka.
		}

	} else if (last_btn_clicked == BTN_one)
	// Tlacitko neni stisknute,
	// ale naposledy stisknute tlacitko ma stejne ID.
	{
		btn_one.setClickEnd(ms); // Nastaveni tlacitka jako "RELEASED".
		last_btn_clicked = 0; // Nulovani ID naposledy stisknuteho tlacitka.
	}

	// Test button 2
	// Stejny postup ale s jinym ID (cislem pinu).
	if (digitalRead(BTN_two) == LOW)
	{
		if (last_btn_clicked == 0)
		{
			btn_two.setClickStart(ms);
			last_btn_clicked = BTN_two;
		}

	} else if (last_btn_clicked == BTN_two)
	{
		btn_two.setClickEnd(ms);
		last_btn_clicked = 0;
	}

#if DEBUG
	delta = millis() - start;
#endif
}

void setup()
{
	Serial.begin(9600);

	Serial.print("IRQSwitch version ");
	Serial.println(IRQSwitch_Version);

	Serial.println("Preparing...");

	// Nastavuji piny jako vystup.
	pinMode(BTN_one, INPUT);
	pinMode(BTN_two, INPUT);
	// Zapinam interni PULL_UP rezistory.
	digitalWrite(BTN_one, HIGH);
	digitalWrite(BTN_two, HIGH);

	// Navesuji preruseni.
	attachInterrupt(digitalPinToInterrupt(BTN_one), buttonProccess, CHANGE);
	attachInterrupt(digitalPinToInterrupt(BTN_two), buttonProccess, CHANGE);

	Serial.println("Ready!\n\n");

}

void loop()
{

	// Vypis stavu tlacitek.
	if (btn_one.isClicked())
	{
		Serial.println("Button 1 clicked!");
	}

	if (btn_two.isClicked())
	{
		Serial.println("Button 2 clicked!");
	}

#if IRQSWITCH_IMPLEMENT_CLICK_HELD
	{
		if (btn_one.isHolded())
		{
			Serial.println("Button 1 holded!");
		}

		if (btn_two.isHolded())
		{
			Serial.println("Button 2 holded!");
		}
	}
#endif

#if IRQSWITCH_IMPLEMENT_CLICK_COUNT > 0
	{
		// Prvni tlacitko je bez automatickeho resetovani pocitadla stisku tlacitka.
		uint8_t count1 = btn_one.getClickCount();

		// Druhe tlacitko s automatickym resetovanim pocitadla stisknuti tlacitka.
		uint8_t count2 = btn_two.getClickCountWithReset();

		if (count1 > 0)
		{
			Serial.print("Button 1 has ");
			Serial.print(count1);
			Serial.println(" clicks");
		}

		if (count2 > 0)
		{
			Serial.print("Button 2 has ");
			Serial.print(count2);
			Serial.println(" clicks");
		}

		if (count1 >= IRQSWITCH_IMPLEMENT_CLICK_COUNT)
		// Pokud je dosazen limit poctu stisknuti, proved reset pocitadla stisku tlacitka
		{
			btn_one.cleanClickCount();
			Serial.println("Reset clicks counter.");
		}
	}
#endif

#if DEBUG
	if (delta > 0)
	{
		Serial.print("buttonProccess = ");
		Serial.print(delta);
		Serial.println(" ms");
	}
#endif

	delay(1000);
}
