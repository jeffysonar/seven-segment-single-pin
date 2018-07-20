void setup() {
  // put your setup code here, to run once:
  // begin uart with 9600 baud rate
  Serial.begin(9600);
}

// bit - data array
int point[4] {0, 0, 0, 0};

void loop() {
  // put your main code here, to run repeatedly:
  // increment least bit by 1
  point[0] ++;
  // if least bit exceeds 9, reset it
  if(point[0] > 9) {
    int i = 0;
    // reset values till higher bit
    while(point[i] > 9) {
      point[i] = 0;
      Serial.write(i);    // send position
      Serial.write(0);    // send value - 0
      i ++;
      point[i] ++;
    }
    Serial.write(i);      // send position
    Serial.write(point[i]);    // update higher bit value
  }
  Serial.write(0);      // normal operation - send 0th position
  Serial.write(point[0]); // update bit value
  delay(1000);          // 1 second delay
}
