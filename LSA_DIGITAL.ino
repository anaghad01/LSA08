void setup() {
  // Setting pin 0 - 7 as digital input pin
  for(byte i=0;i<=7;i++) {
    pinMode(i,INPUT);
  }
  
  // Setting pin 10 - 13 as digital output pin
  for(byte i=10;i<=13;i++) {
    pinMode(i,OUTPUT);
  }
  
}

void loop() {
  // Checking for junction crossing, if juction detected, 
  // keep moving forward
  if(digitalRead(2) && digitalRead(5))
  println("FORWARD");
  
  // Checking for sensor number 1 and 2, if line detected, move left
  else if(digitalRead(1) || digitalRead(2)
  println("LEFT");

  // Checking for sensor number 5 and 6, if line detected, move right
  else if(digitalRead/(5) || digitalRead(6))
 println("RIGHT");

  // Checking for sensors number 3 and 4, 
  // if line is detected by either of these sensor, move forward
  else if(digitalRead(3) || digitalRead(4))
  println("FORWARD");
  
  // If no line is detected, stay at the position
  else
  println("NO LINE ");

  // Put some delay to avoid the robot jig while making a turn
  delay(100);

}
