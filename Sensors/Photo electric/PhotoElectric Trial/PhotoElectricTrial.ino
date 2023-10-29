//sudo chmod a+rw /dev/ttyUSB0

#define PIN 33

long int pulseCount;
long int Depouncing_prev_time;
long int Detect_Element_prev_time;
long int current_time;
int flag_object;

void IRAM_ATTR pulseCounter() {
  // static long int_count=0;  //debug
// Serial.print("int count :");
  // Serial.println(int_count);


  current_time = millis();

  if ((flag_object == 0) && ((current_time - Depouncing_prev_time) >= 50)) {
    /*if condition to ensure that the detection signal is for another element*/
    /*this if condition is a solution for multi detection of the same element specially for glass elements*/
    // if ((current_time - Detect_Element_prev_time) >= 600) {
      flag_object = 1;
      Depouncing_prev_time = current_time;
      Detect_Element_prev_time = current_time;
      pulseCount++;
    // }
  } else if ((flag_object == 1) && ((current_time - Depouncing_prev_time) >= 50)) {
    flag_object = 0;
    Depouncing_prev_time = current_time;
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(PIN), pulseCounter, CHANGE);
}

void loop() {
  Serial.print("count :");
  Serial.println(pulseCount);
}
