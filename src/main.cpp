#include <arduino.h>
#include <wire.h>
#include <spi.h>
#include <GxEPD.h>


//remove for regular ESP32 development boards
// #define ESP32DRIVERBOARD

// remove if Black white RED display
//#define BWR_DISPLAY



#if !defined ESP32DRIVERBOARD
  #if defined BWR_DISPLAY
    #include <GxGDEW042Z15/GxGDEW042Z15.h>    // 4.2" b/w/r
  #else
    #include <GxGDEW042T2/GxGDEW042T2.h>      // 4.2" b/w
  #endif
#else
  #if defined BWR_DISPLAY
    #error BWR in 7.5inch not supported yet
  #else
    #include <GxGDEW075T7/GxGDEW075T7.h>      // 7.5" b/w 800x480
  #endif
#endif

#include GxEPD_BitmapExamples

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>


#if defined(ESP32)

#if !defined ESP32DRIVERBOARD
  #define PIN_BUSY  4   // Purple
  #define PIN_RST   16  // White
  #define PIN_DC    17  // Green
  #define PIN_CS    5   // Orange
  #define PIN_CLK   18  // Yellow
  #define PIN_DIN   23  // Blue
#else
  #define PIN_BUSY  25 
  #define PIN_RST   26
  #define PIN_DC    27
  #define PIN_CS    15 
  #define PIN_CLK   13
  #define PIN_DIN   12
  #define PIN_MISO  12
  #define PIN_MOSI  14
  #define PIN_SS    15 
#endif

//SPIClass displaySPI;  

GxIO_Class io(SPI, /*CS=5*/ PIN_CS, /*DC=*/ PIN_DC, /*RST=*/ PIN_RST); // arbitrary selection of 17, 16
GxEPD_Class display(io, /*RST=*/ PIN_RST, /*BUSY=*/ PIN_BUSY); // arbitrary selection of (16), 4

#endif


void showFont(const char name[], const GFXfont* f)
{
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
  delay(5000);
}

void showFontCallback()
{
  const char* name = "FreeMonoBold9pt7b";
  const GFXfont* f = &FreeMonoBold9pt7b;
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
}

void drawCornerTest()
{
  display.drawCornerTest();
  delay(5000);
  uint8_t rotation = display.getRotation();
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
    display.fillRect(display.width() - 18, 0, 16, 16, GxEPD_BLACK);
    display.fillRect(display.width() - 25, display.height() - 25, 24, 24, GxEPD_BLACK);
    display.fillRect(0, display.height() - 33, 32, 32, GxEPD_BLACK);
    display.update();
    delay(5000);
  }
  display.setRotation(rotation); // restore
}



#if defined(_GxGDEW042T2_H_)
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.fillScreen(GxEPD_WHITE);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif

#if defined(_GxGDEW042Z15_H_)
#define HAS_RED_COLOR
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  // draw black and red bitmap
  display.drawPicture(BitmapExample1, BitmapExample2, sizeof(BitmapExample1), sizeof(BitmapExample2));
  delay(5000);
  display.drawPicture(BitmapExample3, BitmapExample4, sizeof(BitmapExample3), sizeof(BitmapExample4));
  delay(5000);
  display.drawPicture(BitmapWaveshare_black, BitmapWaveshare_red, sizeof(BitmapWaveshare_black), sizeof(BitmapWaveshare_red));
  delay(5000);
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif


#if defined(_GxGDEW075T8_H_)
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.fillScreen(GxEPD_WHITE);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif

#if defined(_GxGDEW075Z09_H_)
#define HAS_RED_COLOR
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#elif defined(ARDUINO_GENERIC_STM32F103C)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#elif defined(ARDUINO_GENERIC_STM32F103V)
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExamplePicture_3C(BitmapPicture_3C, sizeof(BitmapPicture_3C));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.drawExamplePicture_3C(BitmapPicture_3C, sizeof(BitmapPicture_3C));
#endif
}
#endif

#if defined(_GxGDEW075T7_H_)
void showBitmapExample()
{
#if defined(__AVR)
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.drawExampleBitmap(BitmapExample3, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample4, sizeof(BitmapExample2));
  delay(5000);
  display.fillScreen(GxEPD_WHITE);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif

#if defined(_GxGDEW075Z08_H_)
#define HAS_RED_COLOR
void showBitmapExample()
{
#if defined(__AVR) || defined(MCU_STM32F103C8)
  // draw (part of) black bitmap, not enough space for red
  display.drawPicture(BitmapExample1, 0, sizeof(BitmapExample1), 0);
#else
  // draw black and red bitmap
  display.drawExamplePicture(BitmapExample1, BitmapExample2, sizeof(BitmapExample1), sizeof(BitmapExample2));
  //delay(5000);
  //display.drawPicture(BitmapExample1, 0, sizeof(BitmapExample1), 0);
  //delay(5000);
  //display.drawPicture(0, BitmapExample2, 0, sizeof(BitmapExample2));
  //delay(5000);
  //display.drawExamplePicture(BitmapExample1, 0, sizeof(BitmapExample1), 0);
  //delay(5000);
  //display.drawExamplePicture(0, BitmapExample2, 0, sizeof(BitmapExample2));
  //delay(5000);
  //display.fillScreen(GxEPD_WHITE);
  //display.drawBitmap(0, 0, BitmapExample1, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  //display.update();
  //delay(5000);
  //display.fillScreen(GxEPD_WHITE);
  //display.drawBitmap(0, 0, BitmapExample2, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  //display.update();
  //display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  //display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
#endif
}
#endif



void setup()
{

  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  display.init(115200); // enable diagnostic output on Serial
#if defined ESP32DRIVERBOARD
  SPI.end(); 
  SPI.begin(13, 12, 14, 15);
  //SPI.begin(PIN_CLK,PIN_MISO,PIN_MOSI, PIN_SS);
#endif

  Serial.println("setup done");
}

void loop()
{
  bool static once=false;
  if (!once)
  {
    showBitmapExample();
    delay(2000);
  #if !defined(__AVR)
    //drawCornerTest();
    showFont("FreeMonoBold9pt7b", &FreeMonoBold9pt7b);
    showFont("FreeMonoBold12pt7b", &FreeMonoBold12pt7b);
    showFont("FreeMonoBold18pt7b", &FreeMonoBold18pt7b);
    showFont("FreeMonoBold24pt7b", &FreeMonoBold24pt7b);
  #else
    display.drawCornerTest();
    delay(2000);
    display.drawPaged(showFontCallback);
  #endif
    delay(10000);
  }

  once = true;
}
