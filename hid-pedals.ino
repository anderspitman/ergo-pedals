 
#define NUM_SWITCHES 2

#define CODE_LEFT_CTRL 0xe0
#define CODE_LEFT_SHIFT 0xe1
#define CODE_LEFT_META 0xe3

#define PIN_LEFT_CTRL 5
#define PIN_LEFT_SHIFT 4

#define DEBOUNCE_MS 10

#define HIGH 0
#define LOW 1

class Key {
  private:
    byte _state = 0;
    bool _changed = false;
    byte _pin = 4;
    int _code = 0;
    
  public:

    Key(byte pin, int code) {

      this->_pin = pin;
      this->_code = code;
    }

    void init() {
      pinMode(this->_pin, INPUT);
      // enable internal pull-ups
      digitalWrite(this->_pin, 1);
    }
    
    void update() {
      byte state = digitalRead(this->_pin);
      
      if (state != this->_state) {
        //Serial.print("Change: ");
        //Serial.println(this->_pin);
        //Serial.println(this->_state);
        //Serial.println(state);
        
        this->_changed = true;
        this->_state = state;
      }  
    }

    byte state() {
      return this->_state;
    }

    bool changed() {
      const bool changed = this->_changed;
      this->_changed = false;
      return changed;
    }

    int code() {
      return this->_code;
    }
};

// Keyboard report buffer
uint8_t buf[8] = { 0 };

const Key KEYS[NUM_SWITCHES] = { Key(PIN_LEFT_CTRL, CODE_LEFT_CTRL), Key(PIN_LEFT_SHIFT, CODE_LEFT_SHIFT) };

void setup() 
{
  Serial.begin(9600);

  for (int i = 0; i < NUM_SWITCHES; i++) {
    KEYS[i].init();
  }

  delay(200);
}

void loop() {

  bool atLeastOneChanged = false;

  for (int i = 0; i < NUM_SWITCHES; i++) {
    
    KEYS[i].update();
    
    if (KEYS[i].changed()) {
      atLeastOneChanged = true;
      break;
      //Serial.println(buf[i + 2]);
    }
  }

  if (atLeastOneChanged) {
    if (KEYS[0].state() == HIGH && KEYS[1].state() == HIGH) {
      buf[2] = CODE_LEFT_META;
    }
    else if (KEYS[0].state() == HIGH) {
      buf[2] = CODE_LEFT_CTRL;
    }
    else if (KEYS[1].state() == HIGH) {
      buf[2] = CODE_LEFT_SHIFT;
    }
    else {
      buf[2] = 0;
    }
    sendUpdate();
  }
}

void sendUpdate() {
  Serial.write(buf, 8);
  //Serial.println(buf[2]);
  //Serial.println(buf[3]);
}
