

#include <Wire.h>
#include <I2Cdev.h>    
#include <MPU6050.h>
#include <Mouse.h>


int left_button = 7;
int right_button = 6;

MPU6050 mpu;

int16_t ax, ay, az, gx, gy, gz;


int angleToDistance(int a)
{
  if (a < -80)
  {
    return -40;
  }

  else if (a < -65)
  {
    return -20;
  }

  else if (a < -50)
  {
    return -10;
  }

  else if (a < -15)
  {
    return -5;
  }

  else if (a < -5)
  {
    return -1;
  }

  else if (a > 80) 
  {
    return 40;
  }

  else if (a > 65) 
  {
    return 20;
  }

  else if (a > 15)
  {
    return 10;
  }

  else if (a > 5) 
  {
    return 1;
  }
}

void setup() {

  Serial.begin(9600);
  Mouse.begin();

  pinMode(left_button, INPUT_PULLUP);
  digitalWrite(left_button, HIGH);
  
  pinMode(right_button, INPUT_PULLUP);
  digitalWrite(right_button, HIGH);

  Wire.begin();

  mpu.initialize();

  if (!mpu.testConnection())
  {
    while (1);
  }
}

void loop() {

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  int vx = map(ax, -16000, 16000, 90, -90);
  int vy = map(ay, -16000, 16000, 90, -90);

  Mouse.move(angleToDistance(vx), angleToDistance(vy));
  
  
  if (digitalRead(left_button) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) 
    {
      Mouse.press(MOUSE_LEFT);
    }
  }

  else 
  {
    if (Mouse.isPressed(MOUSE_LEFT))
    {
      Mouse.release(MOUSE_LEFT);
    }
  }

  if (digitalRead(right_button) == LOW) 
  {
    if (!Mouse.isPressed(MOUSE_RIGHT)) 
    {
      Mouse.press(MOUSE_RIGHT);
    }
  }

  else
  {
    if (Mouse.isPressed(MOUSE_RIGHT))
    {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  delay(20);
}