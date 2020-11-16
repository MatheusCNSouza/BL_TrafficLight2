#include <mbed.h>

DigitalOut red_led(p5);
DigitalOut yellow_led(p6);
DigitalOut green_led(p7);
InterruptIn btn(p8);
Ticker ticker;
typedef enum{state_1, state_2, state_3, state_A, state_O} State;
float times[] = {10.0, 20.0, 4.0};
int state = state_1;
float led_aux = 1.0f;
Timeout timeout;
int tbt = 0;
int previous;

void ticker_a(){
  static int a_aux = 1;
  a_aux = !a_aux;
  yellow_led = a_aux? led_aux:0;
}

void estado_1(){
  state = state_1;
  red_led = 1;
  yellow_led = 0;
  green_led = 0;
}

void estado_2(){
  state = state_2;
  red_led = 0;
  yellow_led = 0;
  green_led = 1;
}

void estado_3(){
  state = state_3;
  red_led = 0;
  yellow_led = 1;
  green_led = 0;
}

void estado_A(int pre){
  previous = pre;
  state = state_A;
  red_led = 0;
  yellow_led = led_aux;
  green_led = 0;
  ticker.attach(ticker_a,1.0);
}

void estado_O(){
  state = state_O;
  red_led = 0;
  yellow_led = 0;
  green_led = 0;
}

void time_transition(){
  if (state < 2){
    state++;
    int st = state;
    switch (st){ 
    case state_1:
      estado_1();
      break;
    case state_2:
      estado_2();
      break;
    default:
      break;
    }
  }else estado_1();
  }

  void btn_transition(){
    int val = tbt;
    tbt = 0;
    if (val > 10){
      if (state == state_O) estado_1();
      else estado_O();
      } else if (state == state_1){
        if (val == 10) estado_2();
        else if (val >= 3) estado_A(0);
      } else if (state == state_2 ){
        if (val >= 3) estado_A(1);
        else estado_3();
      } else if (state == state_3 ){
        if (val >= 3) estado_A(2);      
      } else if (state == state_A ){
        if (previous == 0) estado_1();
        else if (previous == 1) estado_2();
        else if (previous == 2) estado_3();
    }
    tbt = 0;
  }

  void btn_counter(){
    tbt++;
    while (tbt >=1){
      wait_ms(1000);
      printf("count up");
    }
  }

int main() {
  estado_1();
  btn.rise(&btn_counter);
  btn.fall(&btn_transition);
  timeout.attach (&time_transition, times[state]);
  while(1) {
    wait_ms(10);
  }
}