#define Button1_Pin 12
#define Button2_Pin 11
#define Button3_Pin 10
#define Button4_Pin 9
#define Button5_Pin 8
#define Rst_Pin 7
#define LED 13

unsigned long StartTime;
unsigned long Button1_Time;
unsigned long Button2_Time;
unsigned long Button3_Time;
unsigned long Button4_Time;
unsigned long Button5_Time;
char SerialMsg[128];


// Reset statistic
void reset() {
  StartTime = millis();
  Button1_Time = 0;
  Button2_Time = 0;
  Button3_Time = 0;
  Button4_Time = 0;
  Button5_Time = 0;
  digitalWrite(LED, LOW);
}

// Handy func
bool Button_Pressed(int Pin) {
  if (digitalRead(Pin) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

void Serial_Update() {
  sprintf(SerialMsg, "%lu|%lu|%lu|%lu|%lu|%lu", StartTime, Button1_Time, Button2_Time, Button3_Time,Button4_Time ,Button5_Time);
  Serial.println(SerialMsg);
}

// Init
void setup() {
  // Initiate pinMode for buttons
  pinMode(Button1_Pin, INPUT_PULLUP);
  pinMode(Button2_Pin, INPUT_PULLUP);
  pinMode(Button3_Pin, INPUT_PULLUP);
  pinMode(Button4_Pin, INPUT_PULLUP);
  pinMode(Button5_Pin, INPUT_PULLUP);
  pinMode(Rst_Pin, INPUT_PULLUP);
  // Enable internal LED
  pinMode(LED, OUTPUT);
  // Initiate serial connection
  Serial.begin(115200);
  // Initiate values
  reset();
}

void loop() {
  if (Button_Pressed(Rst_Pin) && (Button1_Time + Button2_Time + Button3_Time + Button4_Time + Button5_Time) != 0) {
    reset();
    Serial_Update();
  }
  else {
    if (Button_Pressed(Button1_Pin) && Button1_Time == 0) {
      Button1_Time = millis();
      digitalWrite(LED, HIGH);
      Serial_Update();
    }
    if (Button_Pressed(Button2_Pin) && Button2_Time == 0) {
      Button2_Time = millis();
      digitalWrite(LED, HIGH);
      Serial_Update();
    }
    if (Button_Pressed(Button3_Pin) && Button3_Time == 0) {
      Button3_Time = millis();
      digitalWrite(LED, HIGH);
      Serial_Update();
    }
    if (Button_Pressed(Button4_Pin) && Button4_Time == 0) {
      Button4_Time = millis();
      digitalWrite(LED, HIGH);
      Serial_Update();
    }
    if (Button_Pressed(Button5_Pin) && Button5_Time == 0) {
      Button5_Time = millis();
      digitalWrite(LED, HIGH);
      Serial_Update();
    }
  }
}
