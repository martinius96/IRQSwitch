# Seznamte se, IRQSwitch.

## IRQSwitch je sada nástrojů (Tříd) pro obsluhu stisknutí tlačítek na Embedded zařízeních.

- ***!!Knihovna je stále ve vývoji!!***  
- ***Není vázána na některou z rodin MCU!!***  
- ***Handler pro usnadnění práce s Arduino!***

------------------------------------

Třída **'IRQSwitch'** v sobě ukrývá celou logiku pro detekci různých druhů událostí nad tlačítkem. Podporuje následující metody obsluhy tlačítek:  
- `isClicked()` - Jednoduché stisknutí  
- `getClickCount()` - Počet stisknutí tlačítka (mezi cykly, nebo mezi přístupy k této metodě)  
- `isHolded()` - Udržování tlačítka ve stisknutém stavu  
- `getHoldedTime()` - Doba v milisekundách, po kterou je tlačítko udržováno ve stisknutém stavu.

### Arduino  
Pokud nechcete sami vytvářet rutinu změny stavu tlačítek, je možné k tomu použít Třídu **'IRQSwitchArduino'**.

Třída **'IRQSwitchArduino'** v sobě ukrývá iterátor, který projde seznamem přidaných tlačítek a upraví jejich stavy podle stavů pinů ke kterým jsou přidruženy. Obsahuje následující metody:

- `AddButton(button, pin)` - Přidá tlačítko.  
- `Update(ms)` - Aktualizuje stavy tlačítek.  
- `GetButton(pin)` - Vrátí ukazatel na tlačítko podle jeho čísla pinů.  
@see examples/.


V případě potíží nebo nápadu:
- [Issues](http://github.com/colesnicov/IRQSwitch/issues/) jsou vítány.
- [PullRequests](http://github.com/colesnicov/IRQSwitch/pulls/) jsou vítány ale budou důkladně zvažovány.

Všechny třídy jsou komentovány a všechny možnosti knihovny jsou dobře předvedený v [ukázkách](http://github.com/colesnicov/IRQSwitch/tree/master/examples/).

**MIT Licence**
