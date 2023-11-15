
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET
#define NO_OF_BUTTONS 3

extern int button1_flag ;
extern int button2_flag ;
extern int button3_flag ;
extern int button1Pressed2s_flag;

int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();
int isButton1Pressed2s();
void setUpButton();

void getKeyInput();

#endif /* INC_BUTTON_H_ */
