int dotDelay = 10;
int sensorPin = A0;
int sensorValue = 0;
int referenceValue = 0;
int countElectric = 1;
int countNaught = 1;
int tmp = 0;
String string = "";
String stringSum = "";
char* letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", ".." , // A-I
                   ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
                   "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
                  }; // S-Z

int approximateValue(int a, int b, int value) {            //근사값을 구해주는 함수
  if (abs(a - value) < abs(b - value)) {
    return a;
  } else if (abs(a - value) > abs(b - value)) {
    return b;
  }
}

int approximateValueQuad(int a, int b, int c, int d, int value) {
  return approximateValue(approximateValue(a, b, value), approximateValue(c, d, value), value);
}

void setup() {
  Serial.begin(9600);
  Serial.println("mos_reverse_translator");
  int  sensorValueBeforeRebooting = analogRead(sensorPin);
  Serial.print("sensorValueBeforeRebooting:");    Serial.println(sensorValueBeforeRebooting);

  while (1) {
    if (Serial.find("rebooting")) {
      Serial.println("rebooting");
      break;
    }
  }

  int sensorValueAfterRebooting = analogRead(sensorPin);
  Serial.print("sensorValueAfterRebooting: ");  Serial.println(sensorValueAfterRebooting);
  referenceValue = (sensorValueBeforeRebooting + sensorValueAfterRebooting ) / 2;
  Serial.print("referenceValue: ");  Serial.println(referenceValue);
}
void loop() {
  sensorValue = analogRead(sensorPin);
  if (countElectric - countNaught == 1) {
    if (approximateValueQuad(dotDelay, dotDelay * 4, dotDelay * 5, dotDelay * 6, tmp) == dotDelay) {
    } else if (approximateValueQuad(dotDelay, dotDelay * 4, dotDelay * 5, dotDelay * 6, tmp) == dotDelay * 4) {
      for (int j = 0; j < 26; j++) {
        String str(letters[j]);
        if (string.equals(str) == 1) {
          char c = 'a' + j;
          Serial.print("converted morse code -> ");  Serial.println(c);
          stringSum.concat(c);
          break;
        }
      }
      string.remove(0);
    } else if (approximateValueQuad(dotDelay, dotDelay * 4, dotDelay * 5, dotDelay * 6, tmp) == dotDelay * 5) {
      Serial.print("converted morse code -> ");   Serial.println("' '");
    }
  } else if (countNaught - countElectric == 1) {
    if (approximateValue(dotDelay, dotDelay * 3, tmp) == dotDelay) {
      Serial.print(".");
      string.concat('.');
    } else if (approximateValue(dotDelay, dotDelay * 3, tmp) == dotDelay * 3) {
      Serial.print("-");
      string.concat('-');
    }
  }

  if (sensorValue > referenceValue) {
    tmp = countNaught;
    countNaught = 0;
    countElectric++;
  } else if (sensorValue < referenceValue) {
    tmp = countElectric;
    countElectric = 0;
    countNaught++;
  }

  if (approximateValueQuad(dotDelay, dotDelay * 4, dotDelay * 5, dotDelay * 6, countNaught) == dotDelay * 6 && string.length() > 0) {
    for (int j = 0; j < 26; j++) {
      String str(letters[j]);
      if (string.equals(str) == 1) {
        char c = 'a' + j;
        Serial.print("converted morse code -> ");  Serial.println(c);
        stringSum.concat(c);
        break;
      }
    }
    string.remove(0);
    Serial.println("converted sentence ->");  Serial.print(stringSum);
    stringSum.remove(0);
  }
  delay(20);
}
