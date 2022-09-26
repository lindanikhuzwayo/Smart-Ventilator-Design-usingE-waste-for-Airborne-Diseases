/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/
#include "TRIGGER_WIFI.h"               /*Includes ESP8266WiFi.h and WiFiClientSecure.h, just have these two libraries downloaded before*/
#include "TRIGGER_GOOGLESHEETS.h"       /*Library file for Google Sheets, has to be used after Wi-Fi Client Secure declaration, here everything is in Trigger_WIFI.h, so using it after Trigger_WIFI.h*/ 
#include "MHZ19.h"

const int LED1 =05; // Led in NodeMCU at pin GPIO16 (D0).
const int LED2 =04; // Led in NodeMCU at pin GPIO16 (D0).
const int rx_pin = 13; //Serial rx pin no
const int tx_pin = 15; //Serial tx pin no
const int threshold1 = 450;
const int threshold2 = 900;
/**********Google Sheets Definations***********/
char column_name_in_sheets[ ][20] = {"Co2_level"};          /*1. The Total no of column depends on how many value you have created in Script of Sheets;2. It has to be in order as per the rows decided in google sheets*/
String Sheets_GAS_ID = "AKfycbzXRzgxscNcOXL3BLLtks--GtuaQGSJHKwim2TBkLMq0D-tT-FhUKV7v3YulGX9tCE";                                         /* ( AKfycbzXRzgxscNcOXL3BLLtks--GtuaQGSJHKwim2TBkLMq0D-tT-FhUKV7v3YulGX9tCE) This is the Sheets GAS ID, you need to look for your sheets id*/
int No_of_Parameters = 1; 
MHZ19 *mhz19_uart = new MHZ19(rx_pin,tx_pin);


/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
    
    WIFI_Connect("hp_lindani","lindan1t1");                                                     /*Provide you Wi-Fi SSID and password to connect to Wi-Fi*/
    Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters ); 
    pinMode(LED2, OUTPUT); // set the digital pin as output.
    pinMode(LED1, OUTPUT); // set the digital pin as output.
    Serial.begin(115200);
    mhz19_uart->begin(rx_pin, tx_pin);
    mhz19_uart->setAutoCalibration(false);
    delay(300);
    Serial.print("MH-Z19 now warming up...  status:");
    Serial.println(mhz19_uart->getStatus());
    delay(100);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{ 
     float a = 1, b = 2, c = 3;
    measurement_t m = mhz19_uart->getMeasurement();
    //LED CONTROL AND DISPLAYING CO2 LEVELS.
    Serial.print("co2: ");    
    if (m.co2_ppm > threshold1) {
      digitalWrite(LED1, HIGH);
      Serial.println(m.co2_ppm);
      a=m.co2_ppm;
      Data_to_Sheets(No_of_Parameters,  a);
    } else {
      digitalWrite(LED1, LOW);
      Serial.println(m.co2_ppm);
      a=m.co2_ppm;
      Data_to_Sheets(No_of_Parameters,  a);
    }

    if (m.co2_ppm > threshold2) {
      digitalWrite(LED2, HIGH);
      Serial.println(m.co2_ppm);
      a=m.co2_ppm;
      Data_to_Sheets(No_of_Parameters,  a);
    } else {
      digitalWrite(LED2, LOW);
      Serial.println(m.co2_ppm);
      a=m.co2_ppm;
      Data_to_Sheets(No_of_Parameters,  a);
    }
    delay(10000);  
}

