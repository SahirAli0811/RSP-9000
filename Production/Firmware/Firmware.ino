
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const int SERVO_COUNT = 5;
const int SERVO_MIN = 1200;
const int SERVO_MAX = 1800;
const int SERVO_CENTER = 1500;

void setServo(uint8_t channel, uint16_t pulse) {
  uint32_t ticks = (uint32_t)pulse * 4096UL * 50UL / 1000000UL;
  pwm.setPWM(channel, 0, ticks);
}

void sweepServo(uint8_t channel) {
  for (int pulse = SERVO_CENTER; pulse <= SERVO_MAX; pulse += 10) {
    setServo(channel, pulse);
    delay(20);
  }

  delay(300);

  for (int pulse = SERVO_MAX; pulse >= SERVO_MIN; pulse -= 10) {
    setServo(channel, pulse);
    delay(20);
  }

  delay(300);

  for (int pulse = SERVO_MIN; pulse <= SERVO_CENTER; pulse += 10) {
    setServo(channel, pulse);
    delay(20);
  }

  delay(500);
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(500);

  for (int i = 0; i < SERVO_COUNT; i++) {
    setServo(i, SERVO_CENTER);
  }

  delay(1000);
}

void loop() {
  for (int channel = 0; channel < SERVO_COUNT; channel++) {
    sweepServo(channel);
  }

  delay(1000);
}
