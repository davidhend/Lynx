#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>
#include <SeeedTouchScreen.h> 
#include <Entropy.h>
#include <SD.h>

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3 

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3 

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3 

#endif

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2
/* touch screen */
TouchScreen ts = TouchScreen(XP, YP, XM, YM);
/* SD myFile */
File myFile;
/* used for password generation / decryption */
String Site_Password[5] = {"","","","",""};
String Decrypted_Password[5] = {"","","","",""};
String Line[5] = {"","","","",""};
/* site number vars */
int current_site_number = 99;
int current_screen_number = 1;
/* display flags */
boolean diplayed_screen_1 = false;
boolean diplayed_screen_2 = false;
/* display flags */
boolean yes_no_displayed = false;
boolean password_visible = false;
boolean password_changed = false;
/* used to keep track of which passwords have been set */
boolean password_0_set = false;
boolean password_1_set = false;
boolean password_2_set = false;
boolean password_3_set = false;
boolean password_4_set = false;
/* used for RFID */
char val; 
char code[10]; 
int bytesread = 0; 
/* This is the RFID card code; you will want this to be the same as your card */
char final_code[10] = {'0','2','0','0','4','6','A','9','2','E'};
/* rfid card flag */
boolean card_found = false;

char pw[9];
void setup()
{
  TFT_BL_ON;   
  /* serial begin */
  Serial.begin(2400);
  /* Set digital pin 9 as OUTPUT to connect it to the RFID /ENABLE pin */
  pinMode(9,OUTPUT);    
  /* Activate the RFID reader */
  digitalWrite(9, LOW);                  
  /* wait until you have the correct rfid code */
  while(card_found == false){
     check_for_rfid_card();
  }
  /* deactivate RFID reader */
  digitalWrite(9, HIGH);  
  
  /* init tft library */
  Tft.TFTinit();   
  /* init entropy */
  Entropy.Initialize();
  /* init sd card */
  pinMode(10, OUTPUT);
   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  
  /* read password file */
  read_password_file();
  /* check to see which slots already have passwords */
  check_password_status();
  
}


void loop()
{ 
  /* get user input */
  check_touch_screen();
  /* draw current screen if it needs to be done */
  display_screen_number(current_screen_number);
  /* delay needed for touch screen to work properly */
  delay(100);   
}




