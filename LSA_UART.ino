    
const byte rx = 0;    // Defining pin 0 as Rx
const byte tx = 1;    // Defining pin 1 as Tx
const byte serialEn = 2;    // Connect UART output enable of LSA08 to pin 2
const byte junctionPulse = 4;   // Connect JPULSE of LSA08 to pin 4

unsigned int junctionCount = 0;   // Variable to store junction count value

void setup() {
  pinMode(serialEn,OUTPUT);   // Setting serialEn as digital output pin
  pinMode(junctionPulse,INPUT);   // Setting junctionPulse as digital input pin

  // Setting pin 10 - 13 as digital output pin
  for(byte i=10;i<=13;i++) {
    pinMode(i,OUTPUT);
  }

  // Setting initial condition of serialEn pin to HIGH
  digitalWrite(serialEn,HIGH);

  // Begin serial communication with baudrate 9600
  Serial.begin(9600);

  // Clear internal junction counter of LSA08
  clearJunction();

}

void loop() {
  byte dummy = 0;   // Declare a dummy variable to store incoming data
  
  // Checking for junction crossing, if juction detected, 
  // keep m+oving forward
  if(digitalRead(junctionPulse)) {
    while(digitalRead(junctionPulse)) {
    
    }
    // Retrieve the junction count from LSA08
    // You can do whatever you want with the junction count
    junctionCount = getJunction();
  }
  
  digitalWrite(serialEn,LOW);   // Set serialEN to LOW to request UART data
  while(Serial.available() <= 0);   // Wait for data to be available
  dummy = Serial.read();    // Read incoming data and store in dummy
  digitalWrite(serialEn,HIGH);    // Stop requesting for UART data

  // Checking for sensor number 1 and 2, if line detected, move left
  if(bitRead(dummy,1) || bitRead(dummy,2))
 Serial.println("LEFT");

 
  // Checking for sensor number 5 and 6, if line detected, move right
  else if(bitRead(dummy,5) || bitRead(dummy,6))
 Serial.println("RIGHT");

  // Checking for sensors number 3 and 4, 
  // if line is detected by either of these sensor, move forward
  else if(bitRead(dummy,3)||bitRead(dummy,4))
 Serial.println("FORWARD");

  // If no line is detected, stay at the position
  else
 Serial.println("NO LINE DETECTED");

  // Put some delay to avoid the robot jig while making a turn
  delay(100);

}

// Function to clear internal junction counter of LSA08
void clearJunction() {
  char address = 0x01;
  char command = 'X';
  char data = 0x00;
  char checksum = address + command + data;

  Serial.write(address);
  Serial.write(command);
  Serial.write(data);
  Serial.write(checksum);
}

// Function to retrieve junction count from LSA08
int getJunction() {
  char address = 0x01;
  char command = 'X';
  char data = 0x01;
  char checksum = address + command + data;

  Serial.write(address);
  Serial.write(command);
  Serial.write(data);
  Serial.write(checksum);

  while(Serial.available() <= 0);
  return (int(Serial.read()));
}
