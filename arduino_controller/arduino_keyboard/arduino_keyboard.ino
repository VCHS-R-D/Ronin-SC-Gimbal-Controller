void setup() {

  // open the serial port:

  Serial.begin(9600);

  // initialize control over the keyboard:

}

void loop() {

  // check for incoming serial data:

  if (Serial.available() > 0) {

    // read incoming serial data:

    int num = Serial.read();

    Serial.println(num);

  }
}
