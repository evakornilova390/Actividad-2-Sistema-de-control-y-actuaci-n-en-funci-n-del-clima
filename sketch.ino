#include <DHT.h>
#include <LiquidCrystal.h>

// Pines sensores
#define DHTPIN 2
#define DHTTYPE DHT22
#define LDRPIN A0
#define VOCPIN A1
#define WINDPIN A2

// Pines actuadores
#define LED_HEAT 3
#define LED_COOL 4
#define LED_LIGHT1 5
#define LED_LIGHT2 6
#define LED_LIGHT3 13
#define LED_LIGHT4 A3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Promedio de temperatura
const int numLecturas = 5;
float temperaturas[numLecturas];
int indice = 0;

unsigned long tiempoUltimaLectura = 0;
const unsigned long intervaloLectura = 10000;
const unsigned long intervaloApagarLCD = 30000;
bool lcdEncendido = true;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Estacion Clima");
  delay(2000);
  lcd.clear();

  // Pines actuadores
  pinMode(LED_HEAT, OUTPUT);
  pinMode(LED_COOL, OUTPUT);
  pinMode(LED_LIGHT1, OUTPUT);
  pinMode(LED_LIGHT2, OUTPUT);
  pinMode(LED_LIGHT3, OUTPUT);
  pinMode(LED_LIGHT4, OUTPUT);
}

void loop() {
  unsigned long ahora = millis();

  if (ahora - tiempoUltimaLectura >= intervaloLectura) {
    tiempoUltimaLectura = ahora;

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    int luz = analogRead(LDRPIN);
    int voc = analogRead(VOCPIN);
    int viento = map(analogRead(WINDPIN), 0, 1023, 0, 360);

    // Guardar temperatura para promedio
    temperaturas[indice] = temp;
    indice = (indice + 1) % numLecturas;

    float suma = 0;
    for (int i = 0; i < numLecturas; i++) {
      suma += temperaturas[i];
    }
    float promedio = suma / numLecturas;

    // Encender pantalla si está apagada
    if (!lcdEncendido) {
      lcd.display();
      lcdEncendido = true;
    }

    // Control de temperatura
    if (temp < 22) {
      digitalWrite(LED_HEAT, HIGH);
      digitalWrite(LED_COOL, LOW);
    } else if (temp > 28) {
      digitalWrite(LED_COOL, HIGH);
      digitalWrite(LED_HEAT, LOW);
    } else {
      digitalWrite(LED_COOL, LOW);
      digitalWrite(LED_HEAT, LOW);
    }

    // Control de iluminación
    int nivel = map(luz, 0, 1023, 0, 5);

    digitalWrite(LED_LIGHT1, nivel > 0);
    digitalWrite(LED_LIGHT2, nivel > 1);
    digitalWrite(LED_LIGHT3, nivel > 2);
    digitalWrite(LED_LIGHT4, nivel > 3);

    // Presentación en LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print(temp, 1);
    lcd.print(" H:"); lcd.print(hum, 0);
    delay(3000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luz:"); lcd.print(luz);
    lcd.setCursor(0, 1);
    lcd.print("Dir:"); lcd.print(viento);
    lcd.print((char)223);
    delay(3000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("VOC:"); lcd.print(voc);
    lcd.setCursor(0, 1);
    lcd.print("T.prom:"); lcd.print(promedio, 1);
    delay(3000);

    if (temp < 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No cargar bat");
      lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.print(temp, 1);
      lcd.print(" C");
      delay(3000);
    }
  }

  // Apagar LCD cada 30 segundos
  if (millis() % intervaloApagarLCD < 100 && lcdEncendido) {
    lcd.noDisplay();
    lcdEncendido = false;
  }
}