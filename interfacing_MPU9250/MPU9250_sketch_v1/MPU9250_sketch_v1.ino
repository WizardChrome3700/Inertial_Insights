#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  // pinMode(2, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,21);
  int16_t GyroX=Wire.read() << 8 | Wire.read();
  Wire.end();
  Serial.print("GyroX: ");
  Serial.println(GyroX);
  delay(2000);
}

// #define SDA 4
// #define SCL 3

// int x = 0;
// int y = 0;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(4, OUTPUT);
//   pinMode(3, OUTPUT);
// }

// void loop() {
//   // // put your main code here, to run repeatedly:
//   // // START
//   // digitalWrite(SDA, LOW);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // delay(1);

//   // // ADDRESS + W
//   // // 1  
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
  
//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // pinMode(SDA, INPUT);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // delay(1);
//   // pinMode(SDA, OUTPUT);

//   // // RA = 0x43
//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // pinMode(SDA, INPUT);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // delay(1);
//   // pinMode(SDA, OUTPUT);
//   // delay(1);

//   // digitalWrite(SDA, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);

//   // // START
//   // digitalWrite(SDA, LOW);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // ADDRESS + R
//   // // 1  
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
  
//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 0
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // // 1
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // pinMode(SDA, INPUT);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // delay(1);
//   // pinMode(SDA, OUTPUT);
//   // delay(1);

//   // pinMode(SDA, INPUT);
//   // // bit7
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit6
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit5
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit4
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit3
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit2
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit1
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit0
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);

//   // pinMode(SDA, OUTPUT);
//   // delay(1);
//   // digitalWrite(SDA, LOW);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // pinMode(SDA, INPUT);
//   // // bit7
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit6
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit5
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit4
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit3
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit2
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit1
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);
//   // // bit0
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // x = (x << 1) | digitalRead(SDA);
//   // delay(1);
//   // digitalWrite(SCL, LOW);
//   // y = (y << 1) | digitalRead(SDA);

//   // // NACK
//   // pinMode(SDA, OUTPUT);
//   // delay(1);
//   // digitalWrite(SDA, HIGH);
//   // // clock
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SCL, LOW);

//   // digitalWrite(SDA, LOW);

//   // // STOP
//   // pinMode(SDA, OUTPUT);
//   // delay(1);
//   // digitalWrite(SCL, HIGH);
//   // delay(1);
//   // digitalWrite(SDA, HIGH);

//   // Serial.println(x);
//   // x = 0;
// }

