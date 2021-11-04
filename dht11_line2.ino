#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <SimpleDHT.h>
#include <TridentTD_LineNotify.h>

//----------請修改以下參數---------------------------------
//char ssid[] = "PLKADAS";
//char password[] = "12345678";

char ssid[] = "info_office";
char password[] = "info_551";
String LINE_TOKEN = "ztNYlM9iMfGiTxdYD1NBUrk7ks4mumlPQJFvT2p0Udp";
int pinDHT11 = 4;//DHT11 接在腳位GPIO4
//---------------------------------------------------------
SimpleDHT11 dht11(pinDHT11);
//WiFiClientSecure client;
//char host[] = "notify-api.line.me";

void setup() {
  Serial.begin(115200);
  //連線到指定的WiFi SSID
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  //連線成功，顯示取得的IP
  Serial.println("");
  Serial.print("IP位址:");
  Serial.println(WiFi.localIP()); //讀取IP位址
  Serial.print("WiFi RSSI:");
  Serial.println(WiFi.RSSI()); //讀取WiFi強度
//  client.setInsecure(); // 若使用ESP32 1.0.6 版核心須加上這句避免SSL 問題
}

void loop() {

  //嘗試讀取溫濕度內容
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }
  //..........讀取成功，將溫濕度顯示在序列視窗...................
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");

  //..........設定觸發LINE訊息條件為溫度超過25或濕度超過80............
  if ((int)temperature >= 25 || (int)humidity >= 80) {
     // 顯示 Line版本
    Serial.println(LINE.getVersion());
    LINE.setToken(LINE_TOKEN);
    
    //傳遞Line訊息
    String message = "檢測環境發生異常，請協助儘速派人查看處理，目前環境狀態：";
    String tempe="溫度:"+String(temperature)+"℃";   
    String humid="濕度:"+String(humidity)+"％";
    Serial.println(message);Serial.print(tempe);Serial.println(humid);
    
    LINE.notify("\n"  + message + "\n"  + tempe + " ；" + humid);
      
  // 每1分鐘發送一次(delay120000)
    delay(10000);
  }
    else {
      //傳送失敗
      Serial.println("connected fail");
    }
  
  //每5秒讀取一次溫濕度
  delay(5000);
}
