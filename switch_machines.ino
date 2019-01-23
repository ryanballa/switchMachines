#include <Bounce2.h>
#include <Servo.h>

#define BUTTON_PIN_1 0
#define RED_LED_PIN_1 2
#define GREEN_LED_PIN_1 3
#define TURNOUT_SERVO_PIN_1 7

#define BUTTON_PIN_2 4
#define RED_LED_PIN_2 6
#define GREEN_LED_PIN_2 5
#define TURNOUT_SERVO_PIN_2 A0

#define BUTTON_PIN_3 11
#define RED_LED_PIN_3 10
#define GREEN_LED_PIN_3 9
#define TURNOUT_SERVO_PIN_3 A1

#define BUTTON_PIN_4 8
#define RED_LED_PIN_4 1
#define GREEN_LED_PIN_4 12
#define TURNOUT_SERVO_PIN_4 A2

Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncer4 = Bounce(); 

Servo turnout1;
Servo turnout2;
Servo turnout3;
Servo turnout4;

// Change to 45 to make diverging by default
int turnoutPos[] = {0, 0, 0, 0, 0};
// Change to false to make diverging by default
int isDiverging[] = {false, false, false, false, false};
 
void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT);
  digitalWrite(A0, HIGH);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, HIGH);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  
  pinMode(BUTTON_PIN_1,INPUT_PULLUP);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  pinMode(BUTTON_PIN_2,INPUT_PULLUP);
  pinMode(5, INPUT);
  pinMode(6, INPUT);

  pinMode(BUTTON_PIN_3,INPUT_PULLUP);
  pinMode(9, INPUT);
  pinMode(10, INPUT);

  pinMode(BUTTON_PIN_4,INPUT_PULLUP);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms

  debouncer2.attach(BUTTON_PIN_2);
  debouncer2.interval(5); 

  debouncer3.attach(BUTTON_PIN_3);
  debouncer3.interval(5);

  debouncer4.attach(BUTTON_PIN_4);
  debouncer4.interval(5);

  animateLEDs(turnoutPos[1], RED_LED_PIN_1, GREEN_LED_PIN_1);
  animateLEDs(turnoutPos[2], RED_LED_PIN_2, GREEN_LED_PIN_2);
  animateLEDs(turnoutPos[3], RED_LED_PIN_3, GREEN_LED_PIN_3);
  animateLEDs(turnoutPos[4], RED_LED_PIN_4, GREEN_LED_PIN_4);
  
}

void loop()
{

  animateTurnout(turnoutPos[1], isDiverging[1], 1);
  animateTurnout(turnoutPos[2], isDiverging[2], 2);
  animateTurnout(turnoutPos[3], isDiverging[3], 3);
  animateTurnout(turnoutPos[4], isDiverging[4], 4);

  // Buttons
  debouncer1.update();
  if (debouncer1.rose()) {
    turnout1.attach(TURNOUT_SERVO_PIN_1);
    isDiverging[1] = turnoutPos[1] == 0 ? true : false;
    while(animateTurnout(turnoutPos[1], isDiverging[1], 1)){
      animateLEDs(turnoutPos[1], RED_LED_PIN_1, GREEN_LED_PIN_1);
      turnout1.write(turnoutPos[1]);
    };
    turnout1.detach();
  }

  debouncer2.update();
  if (debouncer2.rose()) {
    turnout2.attach(TURNOUT_SERVO_PIN_2);
    isDiverging[2] = turnoutPos[2] == 0 ? true : false;
    while(animateTurnout(turnoutPos[2], isDiverging[2], 2)){
      animateLEDs(turnoutPos[2], RED_LED_PIN_2, GREEN_LED_PIN_2);
      turnout2.write(turnoutPos[2]);
    };
    turnout2.detach();
  }

  debouncer3.update();
  if (debouncer3.rose()) {
    turnout3.attach(TURNOUT_SERVO_PIN_3);
    isDiverging[3] = turnoutPos[3] == 0 ? true : false;
    while(animateTurnout(turnoutPos[3], isDiverging[3], 3)){
      animateLEDs(turnoutPos[3], RED_LED_PIN_3, GREEN_LED_PIN_3);
      turnout3.write(turnoutPos[3]);
    };
    turnout3.detach();
  }

  debouncer4.update();
  if (debouncer4.rose()) {
    turnout4.attach(TURNOUT_SERVO_PIN_4);
    isDiverging[4] = turnoutPos[4] == 0 ? true : false;
    while(animateTurnout(turnoutPos[4], isDiverging[4], 4)){
      animateLEDs(turnoutPos[4], RED_LED_PIN_4, GREEN_LED_PIN_4);
      turnout4.write(turnoutPos[4]);
    };
    turnout4.detach();
  }
}

bool animateLEDs(int pos, int red, int green) {
  if (pos != 0 || pos != 60) {
    if (pos % 10 == 0 && pos != 0) {
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      delay(10);
    } else if (pos % 5 == 0) {
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(10);
    } 
  }
  
}

bool animateTurnout(int pos, int diverging, int turnoutNum) {
  if (diverging) {
    while(pos<=59) {
      delay(50);
      turnoutPos[turnoutNum] = turnoutPos[turnoutNum] + 1;
      return true;
    } 
  } else {
    while(pos>=1) {
      delay(50);
      turnoutPos[turnoutNum] = turnoutPos[turnoutNum] - 1;
      return true; 
    } 
  }
  return false;
}
