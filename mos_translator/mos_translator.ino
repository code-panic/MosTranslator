
int ledPin = 12;
char* letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", ".." , // A-I
                   ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
                   "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
                  }; // S-Z
int dotDelay = 200;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
  Serial.println("mostranslater");
  while (1) {
    if (Serial.find("rebooting")) {
      Serial.println("rebooting");
      digitalWrite(ledPin, LOW);
      break;
    }
  }
}

void loop() {
  char ch;
  if (Serial.available()) {
    ch = Serial.read();
    Serial.print(ch);
    Serial.println(" -> Convert morse code");
    if (ch >= 'a' && ch <= 'z') { //소문자
      flashSequence(letters[ch - 'a']);
      Serial.println(letters[ch - 'a']);
    }
    else if (ch >= 'A' && ch <= 'Z') { //대문자
      flashSequence(letters[ch - 'A']);
      Serial.println(letters[ch - 'A']);
    }
    else if (ch <= ' ') //빈 문자
      delay(dotDelay * 4);
  }
}

void flashSequence(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
    flashDotOrDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);
}

void flashDotOrDash(char dotOrDash) {
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '.')
    delay(dotDelay);
  else
    delay(dotDelay * 3);
  digitalWrite(ledPin, LOW);
  delay(dotDelay);
}
