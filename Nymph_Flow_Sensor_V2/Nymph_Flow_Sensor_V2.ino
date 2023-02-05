#define BLYNK_TEMPLATE_ID           "TMPL8jDCuksv"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "8bZsZjIv3S1WwrRwBPcIC0UlKEf8bhZn"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk sunucusu ile bağlantı kurmak için kullanılacak Wi-Fi bilgileri
char ssid[] = "ice_family_ZYXEL_2-4G";
char pass[] = "emrebuzInternet";

// Su akış sensörü pin ataması
int flowSensorPin = D2;

// Su akış hızı değişkeni
float flowRate = 0;
float volume;
// Su akış sensöründen okunan verilerin sayımı


// Son veri zamanı
unsigned long lastFlowReport = 0;

// Su akış sensöründen okunan bir impulsun kaç ml su olduğu
volatile long mlPerPulse;

void setup() {
  // Seri bağlantı ayarları
  pinMode(flowSensorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), increase, RISING);
  
  // WiFi bağlantısını kur
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Blynk sunucusu ile bağlantı kur
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  
  // Su akış sensörü verilerini oku

  
  // Su akış hızını hesapla
  // 1000 ms önceki veriler ile karşılaştırıldı
   volume = 2.663 * mlPerPulse / 1000 * 30;
  if (millis() - lastFlowReport > 2000) {
    mlPerPulse = 0;
    lastFlowReport = millis();
  }
  Serial.print(volume);
  Serial.println(" L/m");
    
    // Verileri Blynk uygulamasına gönder
    Blynk.virtualWrite(V1, volume);
    
    // Değişkenleri sıfırla
    //lastFlowReport = millis();

  
}
ICACHE_RAM_ATTR void increase() {
  mlPerPulse++;
}