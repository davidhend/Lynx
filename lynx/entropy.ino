/* This routine will convert a 6 bit value (0-63) to an acceptible password character */
char mapChar(uint32_t parm)
{
  char retval;
  /* map 0..9 to ascii 0..9 */
  if (parm < 10)           
    retval = char(48 + parm);
  /* map 10 to - */  
  else if (parm < 11)      
    retval = '-';
  /* map 11 to + */  
  else if (parm < 12)      
    retval = '.';
  /* map 12 to 37 to ascii A..Z */  
  else if (parm < 38)      
    retval = char(53 + parm);
  /* map 38 to 63 to ascii a..z */  
  else if (parm < 64)      
    retval = char(59 + parm);
  else
    /* if parm is invalid return null */  
    retval = 0;             
  return(retval);
}

/* This routine uses the Entropy library to obtain truly random 6 bit values */
/* and to map that to an eight character cryptographically secure password */
char *getPassword(char *pw)
{
  char ch;
  int indx;
  uint32_t tmp;
    
  for (indx=0; indx<8; indx++)
  { 
    tmp = mapChar(Entropy.random(64));
    pw[indx] = (char) tmp;
  }
  pw[8] = 0;
  return(pw);
}

