/*
 * init.cpp
 *
 *  Created on: 6 Oct 2020
 *      Author: danie
 */

#include <init.h>

void prvSetupHardware()
{
	SystemCoreClockUpdate();
	Board_Init();
	heap_monitor_setup();
	ITM_init();
	Chip_PININT_Init(LPC_GPIO_PIN_INT);
	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}


XYdriver* driverSetup(void){
	DigitalIoPin *dirx = new DigitalIoPin(directionXPort, directionXPin,DigitalIoPin::output ,false);
	DigitalIoPin *diry = new DigitalIoPin(directionYPort, directionYPin,DigitalIoPin::output ,false);
	DigitalIoPin *stepx = new DigitalIoPin(driverXPort, driverXPin,DigitalIoPin::output ,false);
	DigitalIoPin *stepy = new DigitalIoPin(driverYPort, driverYPin,DigitalIoPin::output ,false);
	DigitalIoPin *limit1 = new DigitalIoPin(limit1Port, limit1Pin,DigitalIoPin::pullup, false);
	DigitalIoPin *limit2 = new DigitalIoPin(limit2Port, limit2Pin,DigitalIoPin::pullup, false);
	DigitalIoPin *limit3 = new DigitalIoPin(limit3Port, limit3Pin,DigitalIoPin::pullup, false);
	DigitalIoPin *limit4 = new DigitalIoPin(limit4Port, limit4Pin,DigitalIoPin::pullup, false);

	return new XYdriver(dirx,stepx,limit1,limit2,limit3,limit4,diry,stepy);

}


//IRQ setup, call ENABLE CLEAR before use
void irqSetup(int port, int pin, int channel){
	/* Set pin back to GPIO (on some boards may have been changed to something
		   else by Board_Init()) */
	Chip_IOCON_PinMuxSet(LPC_IOCON, port, pin,(IOCON_MODE_PULLUP |IOCON_DIGMODE_EN | IOCON_MODE_INACT) );

	/* Configure GPIO pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, port, pin);

	/* Enable PININT clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PININT);

	/* Reset the PININT block */
	Chip_SYSCTL_PeriphReset(RESET_PININT);

	/* Configure interrupt channel for the GPIO pin in INMUX block */
	Chip_INMUX_PinIntSel(channel, port, pin);

	/* Configure channel interrupt as edge sensitive and falling edge interrupt */
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(channel));

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(channel));

	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(channel));

	/* Enable interrupt in the NVIC */
	switch(channel) {
	case 0:NVIC_SetPriority(PIN_INT0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY+1);
	break;

	case 1:NVIC_SetPriority(PIN_INT1_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY+1);
	break;

	case 2:NVIC_SetPriority(PIN_INT2_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY+1);
	break;

	case 3:NVIC_SetPriority(PIN_INT3_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY+1);
	break;
	}

}
