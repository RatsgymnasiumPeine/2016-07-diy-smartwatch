#include <U8glib.h>
#include "Time.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);


String days[]  = {
  "",String("Sonntag"), String("Montag"), String("Dienstag"), String("Mittwoch"), String("Donnerstag"), String("Freitag"), String("Samstag")};


void setupOLED(){
  /*
    Setup OLED module
   */
}

void loopOLED(){
  u8g.setRot180();
  u8g.firstPage();  
  do {
    if(displayState == 1){
      // Displaystate 1 means Watchface
      u8g.setFont(u8g_font_profont29r);
      u8g.setFontPosCenter();


      String hours;
      if(hour() < 10){
        hours = "0" + String(hour());
      }
      else{
        hours = String(hour());
      }

      String minutes;
      if(minute() < 10){
        minutes = "0" + String( minute());
      }
      else{
        minutes = String(minute());
      }

      String uhrzeit = String(hours) + ":" + String(minutes);
      int s = u8g.getStrWidth(uhrzeit.c_str());
      u8g.drawStr( 64 - s/2, 32, uhrzeit.c_str());
    }

    if(displayState == 0){
      // Displaystate 0 means Day, Month and Year

      u8g.setFont(u8g_font_unifontr);
      u8g.setFontPosBottom();
      String datum = String(day()) + "." + String(month()) + "." + String(year());
      int s2 = u8g.getStrWidth(datum.c_str());
      u8g.drawStr( 64 - s2/2, 42, datum.c_str());

      u8g.setFontPosBottom();
      String tag = days[weekday()];
      int s3 = u8g.getStrWidth(tag.c_str());
      u8g.drawStr( 64 - s3/2, 42 - 24, tag.c_str());

    }

    if(displayState == 2){
      u8g.setFont(u8g_font_profont11);

      int y = 10;
      int x = 0;
      u8g.setPrintPos(0,y);
      for(int i = 0; i < messageTxt.length(); i++){
        if(i > 2 && messageTxt[i-1] == ':' && messageTxt[i-2] == ' '){
          y += 5;
          x = 0;
        }
        else if(x%(21*6) == 0 && i != 0){
          y += 5;
          x = 0; 
        } 
        u8g.setPrintPos(x,y);
        u8g.write(messageTxt[i]);
        if( messageTxt[i] != ' ' || x != 0)
          x+=6;
      }
    }

    String pages = String();
    u8g.setFont(u8g_font_unifont_75r);
    u8g.setFontPosBottom();
    for(int i = 0; i < 3; i++){
      if(displayState == i){
        pages.concat("\x4f");
      }
      else{
        pages.concat("\x4b");
      }
    }
    int s3 = u8g.getStrWidth(pages.c_str());
    u8g.drawStr( 64 - s3/2, 64,pages.c_str());

    if(displayState != 0){
      u8g.drawStr( 4 - u8g.getStrWidth("\x40")/2, 64, "\x40");
    }
    if(displayState != 2){
      u8g.drawStr( 124 - u8g.getStrWidth("\x36")/2, 64, "\x36");
    }
  } 
  while( u8g.nextPage() );
}

