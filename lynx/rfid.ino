void check_for_rfid_card()
{
  /* if data available from reader */
  if(Serial.available() > 0) {  
    /* check for header */    
    if((val = Serial.read()) == 10) {   
      bytesread = 0; 
      /* read 10 digit code */
      while(bytesread<10) {              
        if( Serial.available() > 0) { 
          val = Serial.read(); 
          /* if header or stop bytes before the 10 digit reading */
          if((val == 10)||(val == 13)) { 
            /* stop reading */
            break;                       
          } 
          /* add the digit */ 
          code[bytesread] = val;
          /* ready to read next digit */          
          bytesread++;                   
        } 
      } 
      /* if 10 digit read is complete */
      if(bytesread == 10) {              
        int match_count = 0;
        for(int i = 0; i < 10; i++){
           if(code[i] == final_code[i]){
             match_count += 1;
           } 
        }
        if(match_count == 10){
          card_found = true;
        }
    
      } 
      bytesread = 0; 
      /* deactivate the RFID reader for a moment so it will not flood */
      digitalWrite(9, HIGH);  
      /* wait for a bit */      
      delay(1500);      
      /* Activate the RFID reader */      
      digitalWrite(9, LOW);                  
    } 
  } 
}
