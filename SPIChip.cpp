#include <Global.h>
#include <SPIChip.h>

/**
 * Default construction.
 *
 * @param selectedPin Pin for selection.
 * @return
 *     <p>No results returned.</p>
 */
SPIChip::SPIChip(DigitalPin selectedPin)
{
	//Set selected pin.
	this->selectedPin = selectedPin;

    //Set pin mode.
    pinMode(selectedPin,OUTPUT);
	//Unselected this chip.
    digitalWrite(selectedPin,HIGH);
}

/**
 * Get selected pin.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Selected pin.</p>
 */
DigitalPin SPIChip::getSelectedPin(void)
{
	//Return result.
	return selectedPin;
}

/**
 * Select chip.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SPIChip::selectChip(void)
{
	//Select this chip.
	digitalWrite(selectedPin,LOW);
}

/**
 * Unselected chip.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SPIChip::unselectChip(void)
{
	//Unselected this chip.
	digitalWrite(selectedPin,HIGH); 
}
