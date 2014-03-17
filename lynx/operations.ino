void replace_password_file()
{
  /* deleted old password file */
  SD.remove("test.txt");
  /* write new password file */
  writeSD();
  /* check to see which slots already have passwords */
  check_password_status();
  /* if the user selected yes to change password */
  if(password_changed == true){
    /* reset arduino */
    asm volatile ("  jmp 0");
  }
}

void read_password_file()
{
  /* Read SD card one line at a time */
  int i;
  for(i = 0; i < 5; i++){
    Line[i] = readFile(i+1);
  }
}


void select_site_number(int Site_Number)
{
   switch(Site_Number)
   {
     case 0:
       //Serial.println("Site #0 Selected.");
       current_site_number = 0;
       /* decrypt password from sd */
       decrypt_password_data(0);
       break;
     case 1:
       //Serial.println("Site #1 Selected.");
       current_site_number = 1;
       /* decrypt password from sd */
       decrypt_password_data(1);       
       break;
     case 2:
       //Serial.println("Site #2 Selected.");
       current_site_number = 2;
       /* decrypt password from sd */
       decrypt_password_data(2);       
       
       break;
     case 3:
       //Serial.println("Site #3 Selected.");
       current_site_number = 3;     
       /* decrypt password from sd */
       decrypt_password_data(3);       
       break;
     case 4: 
       //Serial.println("Site #4 Selected.");
       current_site_number = 4;
       /* decrypt password from sd */
       decrypt_password_data(4);         
       break;
     default:
       break;
   }
   
}

void decrypt_password_data(int Site_Number)
{
  Decrypted_Password[Site_Number] = encryptDecrypt(Line[Site_Number]);
}

void check_password_status()
{
  if(Line[0].length() <= 3){
    password_0_set = false;
  }else{
    password_0_set = true;
  }
  
  if(Line[1].length() <= 3){
    password_1_set = false;
  }else{
    password_1_set = true;
  }

  if(Line[2].length() <= 3){
    password_2_set = false;
  }else{
    password_2_set = true;
  }

  if(Line[3].length() <= 3){
    password_3_set = false;
  }else{
    password_3_set = true;
  }

  if(Line[4].length() <= 3){
    password_4_set = false;
  }else{
    password_4_set = true;
  }  
}

