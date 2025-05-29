# Actividad-2-Sistema-de-control-y-actuaci-n-en-funci-n-del-clima

Componentes utilizados:

  - Arduino UNO
  - Sensor DHT22 (temperatura y humedad)
  - LDR (sensor de iluminacion)
  - 2 Potenciómetros (calidad de aire y direccion del viento)
  - Pantalla LCD 16X2
  - 6 leds -> 2 para calefaccion y enfriamiento y 4 para control de iluminacion
  - 6 resistencias de 220 ohm
  - Protoboard

Funcionalidades:

Mide y muestra en la LCD las siguientes variables cada 3 segundos:

- Temperatura (dht.readTemperature()) y humedad (dht.readHumidity()):

![image](https://github.com/user-attachments/assets/8012a1cc-5ee0-4160-b040-327d10e25eda)

- Luz (analogRead(LDRPIN)) y direccion del viento (potenciómetro):

![image](https://github.com/user-attachments/assets/be1336c6-e01a-45e5-9a7c-d34de55dd4fe)

- Calidad del aire (potenciómetro) y promedio de temperatura (últimas 5 lecturas):

![image](https://github.com/user-attachments/assets/1927502d-27f1-430d-8720-44889008ab5b)

- Mensaje de advertencia si la temperatura es menor que 0ºC:

![image](https://github.com/user-attachments/assets/ccc9929e-3136-4dc0-9fb3-2f45a9de75fc)

El LCD cambia de mensaje cada 3 segundos para mostrar los datos. Se usa lcd.clear() para borrar la pantalla antes de escribir de nuevo y lcd.setCursor(x,y) para posicionar el cursor en la pantalla.
Si pasan 30 segundos sin actualizar datos la LCD se apaga para ahorrar energía.


Se ha implementado un control ON-OFF de la temperatura:

if (temp > 28) {
  digitalWrite(LED_ENFRIAR, HIGH);
  digitalWrite(LED_CALENTAR, LOW);
} else if (temp < 22) {
  digitalWrite(LED_CALENTAR, HIGH);
  digitalWrite(LED_ENFRIAR, LOW);
} else {
  digitalWrite(LED_CALENTAR, LOW);
  digitalWrite(LED_ENFRIAR, LOW);
}

- Temperatura <22ºC encendemos led rojo para calefaccion:

![image](https://github.com/user-attachments/assets/f82a261b-54ff-4109-8eaa-20678b469fed)

- Temperatura >28ºC encendemos led azul para refrigeración:

![image](https://github.com/user-attachments/assets/8e0952c1-2936-4e58-b4e1-65a94c021ae0)

- En caso contrario (22-28ºC) permancen ambos apagados:

![image](https://github.com/user-attachments/assets/f3a61908-6523-4b22-8c52-ab823b03dd25)

Se ha implementado tambien un control de la iluminacion con 4 LEDs. Se encienden según el nivel de iluminacion, a menor luz, más LEDs encendidos habrá:

digitalWrite(LED1, nivelLuz < umbral * 4);
digitalWrite(LED2, nivelLuz < umbral * 3);
digitalWrite(LED3, nivelLuz < umbral * 2);
digitalWrite(LED4, nivelLuz < umbral);

![image](https://github.com/user-attachments/assets/3c1859de-9f93-453f-a64a-cc0c81e93272)


