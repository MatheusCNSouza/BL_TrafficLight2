#include <mbed.h>

DigitalOut red_led(p5);
DigitalOut yellow_led(p6);
DigitalOut green_led(p7);
InterruptIn btn(p8);
Ticker ticker;
typedef enum{state_1, state_2, state_3, state_A, state_O} State;
State init = state_1;
float led_aux = 1.0f;
  
void estado_1(){
  red_led = 1;
  yellow_led = 0;
  green_led = 0;
}

void estado_2(){
  red_led = 0;
  yellow_led = 0;
  green_led = 1;
}

void estado_3(){
  red_led = 0;
  yellow_led = 1;
  green_led = 0;
}

void estado_A(){
  red_led = 0;
  yellow_led = 0;
  green_led = 0;
}

void estado_O(){
  red_led = 1;
  yellow_led = 0;
  green_led = 0;
}

int main() {
  estado_1();

  while(1) {
    // put your main code here, to run repeatedly:
  }
}