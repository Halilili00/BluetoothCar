#include <SoftwareSerial.h>

SoftwareSerial bt_connection(8, 9);

#define left_forward 5
#define left_reverse 6
#define right_forward 7
#define right_reverse 10
#define enA 4
#define enB 3

int motorspeed = 150;
char lastAction;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(left_forward, OUTPUT);
  pinMode(left_reverse, OUTPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT);

  digitalWrite(left_reverse, 0);
  digitalWrite(right_reverse, 0);
  digitalWrite(left_forward, 0);
  digitalWrite(right_forward, 0);
  analogWrite(enA, motorspeed);
  analogWrite(enB, motorspeed);
  Serial.begin(9600);
  bt_connection.begin(9600);
}

void loop() {

  if (bt_connection.available()) {
    char data = bt_connection.read();
    Serial.println(data);

    if (data == 'F') {
      stop();
      delay(10);
      forward();
      lastAction = 'F';
    }

    else if (data == 'B') {
      stop();
      delay(10);
      backward();
      lastAction = 'B';
    }

    else if (data == 'R') {
      stop();
      delay(10);
      right();
      lastAction = 'R';
    }

    else if (data == 'L') {
      stop();
      delay(10);
      left();
      lastAction = 'L';
    }

    else if (data == 'S') {  //STOP (all motors stop)
      stop();
    }

    else if (data == 'I') {
      motorspeed = motorspeed + 25;
      if (motorspeed > 255) {
        motorspeed = 255;
      }
      Serial.print(motorspeed);
      continueLastaction();
    }

    else if (data == 'D') {
      
      continueLastaction();
    }
  }
}

void stop() {
  digitalWrite(left_forward, 0);
  digitalWrite(left_reverse, 0);
  digitalWrite(right_forward, 0);
  digitalWrite(right_reverse, 0);
  delay(100);
}

void forward() {
  digitalWrite(left_reverse, 0);
  digitalWrite(right_reverse, 0);
  digitalWrite(left_forward, 1);
  digitalWrite(right_forward, 1);
  analogWrite(enA, motorspeed);
  analogWrite(enB, motorspeed);
}

void backward() {
  digitalWrite(left_reverse, 1);
  digitalWrite(right_reverse, 1);
  digitalWrite(left_forward, 0);
  digitalWrite(right_forward, 0);
  analogWrite(enA, motorspeed);
  analogWrite(enB, motorspeed);
}

void left() {
  digitalWrite(left_reverse, 0);
  digitalWrite(right_reverse, 1);
  digitalWrite(left_forward, 1);
  digitalWrite(right_forward, 0);
  analogWrite(enA, motorspeed);
  analogWrite(enB, motorspeed);
}

void right() {
  digitalWrite(left_reverse, 1);
  digitalWrite(right_reverse, 0);
  digitalWrite(left_forward, 0);
  digitalWrite(right_forward, 1);
  analogWrite(enA, motorspeed);
  analogWrite(enB, motorspeed);
}

void continueLastaction() {
  if (lastAction == 'F') {
    forward();
  } else if (lastAction == 'B') {
    backward();
  } else if (lastAction == 'L') {
    left();
  } else if (lastAction == 'R') {
    right();
  }
}

void increase() {}

void decrease() {
motorspeed = motorspeed - 25;
      if (motorspeed < 150) {
        motorspeed = 150;
      }
      Serial.print(motorspeed);
}