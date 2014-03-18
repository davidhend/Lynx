void display_screen_number(int Screen_Number)
{
  /* if screen number is set to 1 && display hasnt been updated */
  if(Screen_Number == 1 && diplayed_screen_1 == false){
    /* clear the screen */
    smart_clear_screen();
    /* draw site select rectangle */
    Tft.fillRectangle(170,20,35,140,WHITE);
    /* draw select site text */
    Tft.drawString("Select Site", 178,155,2,BLACK); 
    /* if a site has been selected */
    if(current_site_number != 99){
      /* draw send password to PC rectangle */
      Tft.fillRectangle(110,20,35,140,WHITE);
      /* draw type Passoword text*/
      Tft.drawString("Type PW", 119,132,2,BLUE); 
    }
    /* set displayed screen 1 to true */
    diplayed_screen_1 = true;
  }  

  /* if screen number is set to 2 && display hasnt been updated */
  if(Screen_Number == 2 && diplayed_screen_2 == false){
    /* clear the screen */
    smart_clear_screen();
    /* if the current site is not 1 */
    if(current_site_number != 1){
      /* draw white rectangle */
      Tft.fillRectangle(10,170,35,135,WHITE);
    }
    /* if the current site is 1 */
    else if(current_site_number == 1){
      /* draw yellow rectangle */
      Tft.fillRectangle(10,170,35,135,YELLOW);
    }
    /* draw select site 1 text */
    Tft.drawString("Entry #1", 19,290,2,BLUE); 

    /* if the current site is not 2 */
    if(current_site_number != 2){
      /* draw white rectangle */
      Tft.fillRectangle(60,170,35,135,WHITE);
    }
    /* if the current site is 2 */
    else if(current_site_number == 2){
      /* draw yellow rectangle */
      Tft.fillRectangle(60,170,35,135,YELLOW);
    }
    /* draw select site 2 text */
    Tft.drawString("Entry #2", 69,290,2,BLUE); 

    /* if the current site is not 3 */
    if(current_site_number != 3){
      /* draw white rectangle */
      Tft.fillRectangle(110,170,35,135,WHITE);
    }
    /* if the current site is 3 */
    else if(current_site_number == 3){
      /* draw yellow rectangle */
      Tft.fillRectangle(110,170,35,135,YELLOW);
    }
    /* draw select site 3 text */
    Tft.drawString("Entry #3", 119,290,2,BLUE); 

    /* if the current site is not 4 */
    if(current_site_number != 4){ 
      /* draw white rectangle */
      Tft.fillRectangle(160,170,35,135,WHITE);
    }
    /* if the current site is 4 */
    else if(current_site_number == 4){
      /* draw yellow rectangle */
      Tft.fillRectangle(160,170,35,135,YELLOW);
    }
    /* draw select site 4 text */
    Tft.drawString("Entry #4", 169,290,2,BLUE); 

    /* draw back button rectangle */
    Tft.fillRectangle(10,10,35,35,RED);
    /* draw back symbol */
    Tft.drawChar('<', 20,32,2,WHITE);
    
    /* draw clear button rectangle*/
    Tft.fillRectangle(60,10,35,90,WHITE);
    /* clear site text */
    Tft.drawString("Clear", 68,90,2,RED); 
    
   /*  */
    if(current_site_number != 99){ 
      /* draw change password rectangle */
      Tft.fillRectangle(110,10,35,35,YELLOW);      
      /* draw exclimation symbol */
      Tft.drawChar('!', 120,30,2,WHITE);    
    }
    
    /* set displayed screen 2 to true */
    diplayed_screen_2 = true;
  }

}


void check_touch_screen()
{
  // a point object holds x y and z coordinates
  Point p = ts.getPoint();

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > __PRESURE) {
 
    //Serial.print("X = "); Serial.print(p.x);
    //Serial.print("\tY = "); Serial.print(p.y);
    //Serial.print("\tPressure = "); Serial.println(p.z);

    /* select site button */
    if(p.x >= 170 && p.y >= 15 && p.x <= 212 && p.y <= 160  && current_screen_number == 1){
      /* set site number to 2 */
      current_screen_number = 2;
      /* allow screen 2 to be re-drawn */
      diplayed_screen_2 = false;
    }
    
    /* type password button*/
    if(p.x >= 110 && p.y >= 15 && p.x <= 149 && p.y <= 156 && current_screen_number == 1  && current_site_number != 99){
      /* rfid authentication dialog */
      Tft.fillRectangle(50,20,35,135,WHITE);
      /* rfid authentication text */
      Tft.drawString("i.d. needed", 58,152,2,BLUE);       
      /* Activate the RFID reader */
      digitalWrite(9, LOW); 
      /* wait until you have the correct rfid code */
      while(card_found == false){
        check_for_rfid_card();
      }      
      /* deactivate RFID reader */
      digitalWrite(9, HIGH);
      /* reset card found flag */
      card_found = false;
      /* get password length */
      int sizeOfPW = Decrypted_Password[current_site_number].length();
      /* store the password in a new string temporarily */
      String pw = Decrypted_Password[current_site_number];
      /* create char array to hold password */
      char current_password[9];
      /* itterate over current passwrod */
      for(int i = 0; i <= sizeOfPW; i++){
         current_password[i] = pw[i];
      }
      /* draw password to screen */
      Tft.drawString(current_password, 19,300,2,BLUE); 
      /* draw clear screen button rectangle*/
      Tft.fillRectangle(50,20,35,135,WHITE);
      /* clear site text */
      Tft.drawString("Clear", 58,110,2,RED); 
      
      password_visible = true;
    }

    /* site 1 button */
    if(p.x >= 4 && p.y >= 167 && p.x <= 42 && p.y <= 305 && current_screen_number == 2){
      /* set site number to 1 */
      current_site_number = 1;
      /* get the password data for site 1 */  
      select_site_number(1);
      /* allow screen 2 to be re-drawn */
      diplayed_screen_2 = false;
    }

    /* site 2 button */
    if(p.x >= 60 && p.y >= 167 && p.x <= 95 && p.y <= 305 && current_screen_number == 2){
      /* set site number to 2 */
      current_site_number = 2;
      /* get the password data for site 2 */  
      select_site_number(2);
      /* allow screen 2 to be re-drawn */
      diplayed_screen_2 = false;
    }

    /* site 3 button */
    if(p.x >= 108 && p.y >= 167 && p.x <= 150 && p.y <= 305 && current_screen_number == 2){
      /* set site number to 3 */
      current_site_number = 3;
      /* get the password data for site 3 */  
      select_site_number(3);      
      /* allow screen 2 to be re-drawn */
      diplayed_screen_2 = false;
    }
    
    /* site 4 button */
    if(p.x >= 165 && p.y >= 165 && p.x <= 202 && p.y <= 305 && current_screen_number == 2){
      /* set site number to 4 */
      current_site_number = 4;
      /* get the password data for site 4 */  
      select_site_number(4);      
      /* allow screen 2 to be re-drawn */
      diplayed_screen_2 = false;
    }
    
    /* clear selection button*/
    if(p.x >= 57 && p.y >= 5 && p.x <= 96 && p.y <= 95 && current_screen_number == 2){
      /* set site number to 99 */
      current_site_number = 99;
      /* allow screen 2 to be re-drawn */
      diplayed_screen_2 = false;
    }
    
    /* clear screen button*/
    if(p.x >= 45 && p.y >= 14 && p.x <= 85 && p.y <= 136 && current_screen_number == 1 && password_visible == true){
      /* allow screen 2 to be re-drawn */
      diplayed_screen_1 = false;
    }
    
    /* change password buttons */
    if(p.x >= 111 && p.y >= 5 && p.x <= 146 && p.y <= 38 && current_screen_number == 2){
        Tft.fillRectangle(170,10,35,140,WHITE);
        Tft.drawString("i.d. needed", 178,145,2,BLACK);
        /* Activate the RFID reader */
        digitalWrite(9, LOW); 
        /* wait until you have the correct rfid code */
        while(card_found == false){
          check_for_rfid_card();
        }      
        /* deactivate RFID reader */
        digitalWrite(9, HIGH);
        /* reset card found flag */
        card_found = false;  
        Tft.fillRectangle(170,10,35,140,BLACK);
        
        /* no response box */
        Tft.fillRectangle(160,10,35,35,WHITE);
        /* no */ 
        Tft.drawString("No", 170,35,2,BLUE);
        /* yes response box*/
        Tft.fillRectangle(160,70,35,45,WHITE);
        /* yes */
        Tft.drawString("Yes", 170,110,2,BLUE);
        /* yes no displayed true */
        yes_no_displayed = true;
    }

    /* yes button*/
    if(p.x >= 165 && p.y >= 64 && p.x <= 202 && p.y <= 112 && current_screen_number == 2 && yes_no_displayed == true){
        /* generate new password for the site selected*/
        makePassword(current_site_number);
        /* set flag for password change */
        password_changed = true;
        /* write the chages to the SD card & re-read data file */
        replace_password_file();
        /* re-read password file */
        //read_password_file();     
        /* get the password data for site 1 */  
        //select_site_number(current_site_number);
        /* yes no displayed false */
        //yes_no_displayed = false; 
        /* allow screen 2 to be re-drawn */
        //diplayed_screen_2 = false;     
    }
    
    /* no button */
    if(p.x >= 163 && p.y >= 4 && p.x <= 202 && p.y <= 41 && current_screen_number == 2 && yes_no_displayed == true){
        /* allow screen 2 to be re-drawn */
        diplayed_screen_2 = false;
        /* yes no displayed false */
        yes_no_displayed = false;      
    }    

    /* back button*/
    if(p.x >= 5 && p.y >= 5 && p.x <= 44 && p.y <= 40 && current_screen_number == 2){
      /* set screen number to 1 */
      current_screen_number = 1; 
      /* allow screen 1 to be re-drawn */
      diplayed_screen_1 = false;
    }
  }
  
}

void smart_clear_screen()
{
  /* clear site select button*/
  Tft.fillRectangle(170,20,35,140,BLACK);
  /* type pw button */  
  Tft.fillRectangle(110,20,35,140,BLACK);
  /* clear clear screen button rectangle*/
  Tft.fillRectangle(50,20,35,135,BLACK);
  /* clear site 1 button*/
  Tft.fillRectangle(10,170,35,135,BLACK);
  /* clear site 2 button*/
  Tft.fillRectangle(60,170,35,135,BLACK);
  /* clear site 3 button*/
  Tft.fillRectangle(110,170,35,135,BLACK);
  /* clear site 4 button*/
  Tft.fillRectangle(160,170,35,135,BLACK);
  /* clear clear button*/  
  Tft.fillRectangle(60,10,35,90,BLACK);
  /* clear change password rectangle */
  Tft.fillRectangle(110,10,35,35,BLACK); 
  /* clear no response box */
   Tft.fillRectangle(160,10,35,35,BLACK);
  /* clear yes response box*/
  Tft.fillRectangle(160,70,35,45,BLACK);
  /* clear back button*/
  Tft.fillRectangle(10,10,35,35,BLACK);   
}
