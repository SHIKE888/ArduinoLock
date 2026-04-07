#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <unoqrcode.h>
#include "Web.h"
#include "Websettings.h"      //Web配网
char setWiFi_Flag;            // 配网标志位
String otpkey = "1234567890"; // 本地OTP密钥
String base32 = "";
HTTPClient http;
QRCode qrcode;


// const char* ssid = "";
// const char* password = "";
// 强制门户Web配网

void setWiFi()
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 15, "WiFi Configuration");
    u8g2.drawStr(0, 30, "Press [#] to cancel");
    u8g2.drawStr(0, 45, "SSID: ");
    u8g2.setCursor(35, 45); // 设置显示位置
    u8g2.print(AP_NAME);
    u8g2.drawStr(0, 60, "CONNECT 192.168.4.1");
    u8g2.sendBuffer();
    setWiFi_Flag = 1;
    initSoftAP();
    initWebServer();
    initDNS();
    while (setWiFi_Flag)
    {
        server.handleClient();
        dnsServer.processNextRequest();
        char key = get_key(); // 获取按键
        if (key == '#')
        {
            beep(3);
            setWiFi_Flag = 0;
            server.stop();
            Serial.println("WiFi configuration cancelled.");
            ESP.restart();
        }
    }
}
// 删除保存的wifi信息
void get_otp()
{
    String json = "";
    String url = "http://api.absozero.cn/TOTP.php?auth=" + otpkey;
    Serial.println(url);
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            json = http.getString();
            Serial.println(json);
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        Serial.println("Failed to get OTP code!");
        otp1 = "-1";
        otp2 = "-1";
        http.end();
        return;
    }
    delay(1000);
    http.end();
    StaticJsonDocument<200> doc;
    deserializeJson(doc, json);
    otp1 = doc["key1"].as<String>();
    otp2 = doc["key2"].as<String>();
    return;
}
void get_qrcode()
{
    // String json = "";
    // String url = "http://api.absozero.cn/TOTP.php?auth=" + otpkey;
    // http.begin(url);
    // int httpCode = http.GET();
    // if (httpCode > 0)
    // {
    //     // HTTP header has been send and Server response header has been handled
    //     Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    //     // file found at server
    //     if (httpCode == HTTP_CODE_OK)
    //     {
    //         json = http.getString();
    //         Serial.println(json);
    //     }
    // }
    // else
    // {
    //     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    //     Serial.println("Failed to get OTP code!");
    //     http.end();
    //     return;
    // }
    // delay(1000);
    // http.end();
    // StaticJsonDocument<200> doc;
    // deserializeJson(doc, json);
    // base32 = doc["base32"].as<String>();
    // url = "otpauth://totp/?secret=" + base32 + "&issuer=Lock";
    // uint8_t qrcodeData[qrcode_getBufferSize(3)];
    // qrcode_initText(&qrcode, qrcodeData, 3, ECC_LOW, url.c_str());
    // uint8_t x0 = (128 - qrcode.size * 2) / 2;
    // uint8_t y0 = (64 - qrcode.size * 2) / 2;
    // // get QR code pixels in a loop
    // u8g2.firstPage();
    // do
    // {
    //     // get the draw starting point,128 and 64 is screen size
    //     uint8_t x0 = (128 - qrcode.size * 2) / 2;
    //     uint8_t y0 = (64 - qrcode.size * 2) / 2;

    //     // get QR code pixels in a loop
    //     for (uint8_t y = 0; y < qrcode.size; y++)
    //     {
    //         for (uint8_t x = 0; x < qrcode.size; x++)
    //         {
    //             // Check this point is black or white
    //             if (qrcode_getModule(&qrcode, x, y))
    //             {
    //                 u8g2.setColorIndex(1);
    //             }
    //             else
    //             {
    //                 u8g2.setColorIndex(0);
    //             }
    //             // Double the QR code pixels
    //             u8g2.drawPixel(x0 + x * 2, y0 + y * 2);
    //             u8g2.drawPixel(x0 + 1 + x * 2, y0 + y * 2);
    //             u8g2.drawPixel(x0 + x * 2, y0 + 1 + y * 2);
    //             u8g2.drawPixel(x0 + 1 + x * 2, y0 + 1 + y * 2);
    //         }
    //     }

    // } while (u8g2.nextPage());
    // return;
}
