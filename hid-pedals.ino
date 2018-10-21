uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */

#define PIN_LEFT_CTRL 5

int state = 1;
int prevState = 1;

void setup() 
{
  Serial.begin(9600);
  pinMode(PIN_LEFT_CTRL, INPUT);
  // enable internal pull-ups
  digitalWrite(PIN_LEFT_CTRL, 1); 

  delay(200);
}

void loop() 
{
  state = digitalRead(PIN_LEFT_CTRL);

  // rising edge
  if (state == 0 && prevState == 1) {
    pressKey();
  }
  // falling edge
  else if (state == 1 && prevState == 0) {
    releaseKey();
  }

  prevState = state;
}

void pressKey() {
  buf[2] = 0xe0;   // Left CTRL key
  Serial.write(buf, 8); // Send keypress
}
void releaseKey() {
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}
