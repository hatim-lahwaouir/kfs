#include "kernel.h"
#include <stdbool.h>


bool capsOn;
bool capsLock;
const int n_screen = 3;

unsigned char screens[3][COLUMNS * LINES * 2];
struct s_screens screen_x_y[3];
int32_t current_screen = 0;

const uint32_t UNKNOWN = 0xFFFFFFFF;
const uint32_t ESC = 0xFFFFFFFF - 1;
const uint32_t CTRL = 0xFFFFFFFF - 2;
const uint32_t LSHFT = 0xFFFFFFFF - 3;
const uint32_t RSHFT = 0xFFFFFFFF - 4;
const uint32_t ALT = 0xFFFFFFFF - 5;
const uint32_t F1 = 0xFFFFFFFF - 6;
const uint32_t F2 = 0xFFFFFFFF - 7;
const uint32_t F3 = 0xFFFFFFFF - 8;
const uint32_t F4 = 0xFFFFFFFF - 9;
const uint32_t F5 = 0xFFFFFFFF - 10;
const uint32_t F6 = 0xFFFFFFFF - 11;
const uint32_t F7 = 0xFFFFFFFF - 12;
const uint32_t F8 = 0xFFFFFFFF - 13;
const uint32_t F9 = 0xFFFFFFFF - 14;
const uint32_t F10 = 0xFFFFFFFF - 15;
const uint32_t F11 = 0xFFFFFFFF - 16;
const uint32_t F12 = 0xFFFFFFFF - 17;
const uint32_t SCRLCK = 0xFFFFFFFF - 18;
const uint32_t HOME = 0xFFFFFFFF - 19;
const uint32_t UP = 0xFFFFFFFF - 20;
const uint32_t LEFT = 0xFFFFFFFF - 21;
const uint32_t RIGHT = 0xFFFFFFFF - 22;
const uint32_t DOWN = 0xFFFFFFFF - 23;
const uint32_t PGUP = 0xFFFFFFFF - 24;
const uint32_t PGDOWN = 0xFFFFFFFF - 25;
const uint32_t END = 0xFFFFFFFF - 26;
const uint32_t INS = 0xFFFFFFFF - 27;
const uint32_t DEL = 0xFFFFFFFF - 28;
const uint32_t CAPS = 0xFFFFFFFF - 29;
const uint32_t NONE = 0xFFFFFFFF - 30;
const uint32_t ALTGR = 0xFFFFFFFF - 31;
const uint32_t NUMLCK = 0xFFFFFFFF - 32;


const uint32_t lowercase[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
'9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL,
'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
'.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

const uint32_t uppercase[128] = {
    UNKNOWN,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R',
'T','Y','U','I','O','P','{','}','\n',CTRL,'A','S','D','F','G','H','J','K','L',':','"','~',LSHFT,'|','Z','X','C',
'V','B','N','M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',
LEFT,UNKNOWN,RIGHT,'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};




void initKeyboard() {

	irq_install_handler(1, &KeyboardHandler);
	capsOn = false;
	capsLock = false;

}

void KeyboardHandler(struct InterruptRegister *regs){
	char info  = inPortB(0x60);
	char scanCode =  info & 0x7F; // what key was pressed
	char press = info & 0x80; // press down or released
	switch(scanCode){
		case 1:
			if (press == 0)
				switchScreen();
			break;
		case 29:
		case 56:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 87:
		case 88:
		    break;
		case 42:
		    //shift key
		    if (press == 0){
			capsOn = true;
		    }else{
			capsOn = false;
		    }
		    break;
		case 58:
		    if (!capsLock && press == 0){
			capsLock = true;
		    }else if (capsLock && press == 0){
			capsLock = false;
		    }
		    break;
		default:
		    if (press == 0){
			if (capsOn || capsLock){
			    printf("%c", uppercase[scanCode]);
			}else{
			    printf("%c", lowercase[scanCode]);
			}
		    }
		    
	    }

}


void clear_screens() {
	for (int i = 0 ; i < n_screen; i++){
		screen_x_y[i].xpos = 0;
		screen_x_y[i].ypos = 0;
		for (int j= 0 ; j < COLUMNS * LINES * 2; j++)
			screens[i][j] =  0;
	}
}


void switchScreen() {
	// first save current window 
	for (int i = 0; i < COLUMNS * LINES * 2; i++) {
    		screens[current_screen][i] = *(video + i);
		}
	screen_x_y[current_screen].ypos = ypos;
	screen_x_y[current_screen].xpos = xpos; 

	current_screen = (current_screen + 1) % n_screen;
	
	// now changing the screen
	for (int i = 0; i < COLUMNS * LINES * 2; i++)
    		*(video + i) = screens[current_screen][i];

	xpos = screen_x_y[current_screen].xpos;
	ypos = screen_x_y[current_screen].ypos;

}
