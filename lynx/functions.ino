String makePassword(int line)
{
  /* generate new password */
  Site_Password[line] = getPassword(pw);
  /* encrypt password */
  String encrypted = encryptDecrypt(Site_Password[line]);
  /* store encypted password in correct line number */
  Line[line] = encrypted;
}

void writeSD()
{
  /* open the file. note that only one file can be open at a time, */
  /* so you have to close this one before opening another. */
  myFile = SD.open("test.txt", FILE_WRITE);
  
  /* if the file opened okay, write to it: */
  if (myFile) {
    myFile.print(Line[0]);
    myFile.print("\n");
    myFile.print(Line[1]);
    myFile.print("\n");    
    myFile.print(Line[2]); 
    myFile.print("\n");    
    myFile.print(Line[3]); 
    myFile.print("\n");    
    myFile.print(Line[4]); 
    myFile.print("\n");    
    myFile.close();
  } else {
    /* reset arduino */
    asm volatile ("  jmp 0");
  }
}

String readFile(int line)
{
  myFile = SD.open("test.txt",FILE_READ);
  if(myFile)
  {
    String received = "";
    int cur = 0;
    char ch;
    while (myFile.available())
    {
      ch = myFile.read();
      if(ch == '\n') 
      {
        cur++;
        if(cur == line)
        {
          myFile.close();
          return String(received);
        }
        received = "";
      }
      else
      {
        received += ch;
      }
    }
  }
  return "";
}

String encryptDecrypt(String toEncrypt) {
    /*Any chars will work */
    char key[3] = {'D', 'T', 'H'}; 
    String output = toEncrypt;
    
    for (int i = 0; i < toEncrypt.length(); i++)
        output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    
    return output;
}
