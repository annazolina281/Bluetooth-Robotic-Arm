#include <Servo.h>

// Motor pins
#define L_MOTOR_DIO 2
#define L_MOTOR_PWM 5
#define R_MOTOR_DIO 4
#define R_MOTOR_PWM 6

// Servo pins
#define BASE_SERVO_PIN 10
#define UPDOWN_SERVO_PIN 9
#define EXTEND_SERVO_PIN 11
#define CLAW_UPDOWN_SERVO_PIN 12
#define CLAW_SERVO_PIN 8     // Claw servo pin

Servo baseServo, updownServo, extendServo, clawUpDownServo, clawServo;

// 5 positions per servo
const int servoSteps[5] = {30, 75, 120, 165, 180};

int baseIndex = 0, baseCurrent = servoSteps[0];
bool baseForward = true;

int updownIndex = 0, updownCurrent = servoSteps[0];
bool updownForward = true;

int extendIndex = 0, extendCurrent = servoSteps[0];
bool extendForward = true;

int clawIndex = 0, clawCurrent = servoSteps[0];
bool clawForward = true;

int motorSpeed = 200;
char command;

// Claw specific positions
const int POS_OPEN = 130;
const int POS_PART_OPEN = 100;
const int POS_PART_CLOSE = 70;
const int POS_CLOSE = 0;

bool startState = false;
bool pauseState = false;

void setup() {
  Serial.begin(9600);

  pinMode(L_MOTOR_DIO, OUTPUT);
  pinMode(L_MOTOR_PWM, OUTPUT);
  pinMode(R_MOTOR_DIO, OUTPUT);
  pinMode(R_MOTOR_PWM, OUTPUT);

  stopMotors();

  baseServo.attach(BASE_SERVO_PIN);
  baseServo.write(baseCurrent);

  updownServo.attach(UPDOWN_SERVO_PIN);
  updownServo.write(180 - updownCurrent);  // Inverted

  extendServo.attach(EXTEND_SERVO_PIN);
  extendServo.write(extendCurrent);

  clawUpDownServo.attach(CLAW_UPDOWN_SERVO_PIN);
  clawUpDownServo.write(clawCurrent);

  clawServo.attach(CLAW_SERVO_PIN);
  clawServo.write(POS_OPEN);

  Serial.println("Ready: Motors F/B/L/R/P | Base 'C' | UpDown 'X' | Extend 'T' | Claw 'S' | ClawControl: Start(A)/Pause(P)");
}

void loop() {
  if (Serial.available()) {
    command = Serial.read();
    switch (command) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      case 'P': 
        // PAUSE controls claw partial close / close
        if (pauseState) {
          clawServo.write(POS_PART_CLOSE);
        } else {
          clawServo.write(POS_CLOSE);
        }
        pauseState = !pauseState;
        break;

      case 'C': handleServoToggle(baseServo, servoSteps, baseIndex, baseCurrent, baseForward); break;
      case 'X': handleUpdownServoToggle(updownServo, servoSteps, updownIndex, updownCurrent, updownForward); break;
      case 'T': handleServoToggle(extendServo, servoSteps, extendIndex, extendCurrent, extendForward); break;
      case 'S': handleServoToggle(clawUpDownServo, servoSteps, clawIndex, clawCurrent, clawForward); break;

      case 'A': 
        // START controls claw open / partial open
        if (startState) {
          clawServo.write(POS_OPEN);
        } else {
          clawServo.write(POS_PART_OPEN);
        }
        startState = !startState;
        break;

      default: stopMotors(); break;
    }
  }
}

void handleServoToggle(Servo &servo, const int steps[], int &index, int &current, bool &forward) {
  if (forward) {
    if (index < 4) index++;
    else { forward = false; index--; }
  } else {
    if (index > 0) index--;
    else { forward = true; index++; }
  }
  smoothMoveServo(servo, current, steps[index], 10);
  current = steps[index];
}

void handleUpdownServoToggle(Servo &servo, const int steps[], int &index, int &current, bool &forward) {
  if (forward) {
    if (index < 4) index++;
    else { forward = false; index--; }
  } else {
    if (index > 0) index--;
    else { forward = true; index++; }
  }
  smoothMoveServo(servo, 180 - current, 180 - steps[index], 10);
  current = steps[index];
}

void smoothMoveServo(Servo &myServo, int fromPos, int toPos, int stepDelay) {
  if (fromPos < toPos) {
    for (int i = fromPos; i <= toPos; i++) {
      myServo.write(i);
      delay(stepDelay);
    }
  } else {
    for (int i = fromPos; i >= toPos; i--) {
      myServo.write(i);
      delay(stepDelay);
    }
  }
}

void forward() {
  digitalWrite(L_MOTOR_DIO, HIGH);
  digitalWrite(R_MOTOR_DIO, HIGH);
  analogWrite(L_MOTOR_PWM, motorSpeed);
  analogWrite(R_MOTOR_PWM, motorSpeed);
}

void backward() {
  digitalWrite(L_MOTOR_DIO, LOW);
  digitalWrite(R_MOTOR_DIO, LOW);
  analogWrite(L_MOTOR_PWM, motorSpeed);
  analogWrite(R_MOTOR_PWM, motorSpeed);
}

void turnLeft() {
  digitalWrite(L_MOTOR_DIO, HIGH);
  digitalWrite(R_MOTOR_DIO, LOW);
  analogWrite(L_MOTOR_PWM, motorSpeed / 2);
  analogWrite(R_MOTOR_PWM, motorSpeed);
}

void turnRight() {
  digitalWrite(L_MOTOR_DIO, LOW);
  digitalWrite(R_MOTOR_DIO, HIGH);
  analogWrite(L_MOTOR_PWM, motorSpeed);
  analogWrite(R_MOTOR_PWM, motorSpeed / 2);
}

void stopMotors() {
  analogWrite(L_MOTOR_PWM, 0);
  analogWrite(R_MOTOR_PWM, 0);
}
