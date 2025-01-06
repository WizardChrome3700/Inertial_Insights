#define SDA 4
#define SCL 3
#define deviceAddr 0x68

uint8_t write = 0;
uint8_t read = 1;
uint8_t nop = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t regAddr = 0x43;
  int16_t x = readMPU(regAddr)/131;
  Serial.println(x);
}

int16_t readMPU(uint8_t regAddr) {
  startI2C();
  sendByteI2C(deviceAddr, write);
  receiveACKI2C();
  sendByteI2C(regAddr, nop);
  receiveACKI2C();
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);  
  startI2C();
  sendByteI2C(deviceAddr, read);
  receiveACKI2C();
  int16_t x = readDataI2C();
  sendNACKI2C();
  stopI2C();
  return x;
}

void startI2C() {
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  digitalWrite(SDA, LOW);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW);
  delayMicroseconds(1);
}

void sendByteI2C(uint8_t byte, uint8_t cmd) {
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  digitalWrite(SDA, LOW);
  if(cmd != nop) {
    byte = (byte << 1) + cmd;
  }
  for(int i = 0; i < 8; i++) {
    digitalWrite(SDA, ((byte >> (7-i)) & 0x01));
    delayMicroseconds(2);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCL, LOW);
  }
}

void sendNACKI2C() {
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(2);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, LOW);
}

void receiveACKI2C() {
  digitalWrite(SCL, LOW);
  pinMode(SDA, INPUT);
  delayMicroseconds(2);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, LOW);
}

void sendACKI2C() {
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, LOW);
  delayMicroseconds(2);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW);
}

int16_t readDataI2C() {
  digitalWrite(SCL, LOW);
  digitalWrite(SDA, LOW);
  int16_t x = 0;
  pinMode(SDA, INPUT);
  for(int i = 0; i < 8; i++) {
    delayMicroseconds(2);
    digitalWrite(SCL, HIGH);
    x = (x << 1) + digitalRead(SDA);
    delayMicroseconds(1);
    digitalWrite(SCL, LOW);
  }
  sendACKI2C();
  // digitalWrite(SDA, LOW);
  pinMode(SDA, INPUT);
  for(int i = 0; i < 8; i++) {
    delayMicroseconds(2);
    digitalWrite(SCL, HIGH);
    x = (x << 1) + digitalRead(SDA);
    delayMicroseconds(1);
    digitalWrite(SCL, LOW);
  }
  return x;
}

void stopI2C() {
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  delayMicroseconds(1);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SDA, HIGH);
}