void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2) == HIGH) {
    morseCodeGenerator("SIDHANT");
    delay(3000); // Delay between repetitions
  } else {
    digitalWrite(13, LOW);
    delay(100);
  }
}

void morseCodeGenerator(const char* name) {
  // Morse code for all 26 alphabets
  const char* morseCode[] = {
      ".-",   // A --0
      "-...", // B --1
      "-.-.", // C
      "-..",  // D
      ".",    // E
      "..-.", // F
      "--.",  // G
      "....", // H
      "..",   // I
      ".---", // J
      "-.-",  // K
      ".-..", // L
      "--",   // M
      "-.",   // N
      "---",  // O
      ".--.", // P
      "--.-", // Q
      ".-.",  // R
      "...",  // S
      "-",    // T
      "..-",  // U
      "...-", // V
      ".--",  // W
      "-..-", // X
      "-.--", // Y
      "--.."  // Z
  };

  for (int i = 0; name[i] != '\0'; i++) {
    if (name[i] == ' ') {
      delay(7 * 300);
    } else {
      int index = name[i] - 'A';
      if (index >= 0 && index < 26) {
        const char* letterCode = morseCode[index];
        for (int j = 0; letterCode[j] != '\0'; j++) {
          if (letterCode[j] == '.') {
            digitalWrite(13, HIGH);
            delay(300);
            digitalWrite(13, LOW);
          } else if (letterCode[j] == '-') {
            digitalWrite(13, HIGH);
            delay(900);
            digitalWrite(13, LOW);
          }
          delay(300);
        }
        delay(900);
      }
    }
  }
}
