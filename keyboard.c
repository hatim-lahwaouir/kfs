#include "kernel.h"





void initKeyboard() {

	printf("init keyboard\n");
	irq_install_handler(1, &KeyboardHandler);
}

void KeyboardHandler(struct InterruptRegister *regs){

	char info  = inPortB(0x60);
	char scanCode =  info & 0x7F; // what key was pressed
	char press = info & 0x80; // press down or released

	printf("keyboard handler\n");

	printf("Scan code %d, Press %d\n", scanCode, press);

}

