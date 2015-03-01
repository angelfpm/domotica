/*Note: this code is a demo for how to using gprs shield to send sms message, dial a voice call and 
 send a http request to the website, upload data to pachube.com by TCP connection,

 The microcontrollers Digital Pin 7 and hence allow unhindered
 communication with GPRS Shield using SoftSerial Library. 
 IDE: Arduino 1.0 or later
 Replace the following items in the code:
 1.Phone number, don't forget add the country code
 2.Replace the Access Point Name
 3. Replace the Pachube API Key with your personal ones assigned
 to your account at cosm.com
 */
#include <SoftwareSerial.h>
#include <String.h>
SoftwareSerial mySerial(7, 8);
void setup()
{
 mySerial.begin(19200);               // the GPRS baud rate   
 Serial.begin(9600);    // the GPRS baud rate 
 delay(500);
 Serial.println("preparado");
}
void loop()
{
 //after start up the program, you can using terminal to connect the serial of gprs shield,
 //if you input 't' in the terminal, the program will execute SendTextMessage(), it will show how to send a sms message,
 //if input 'd' in the terminal, it will execute DialVoiceCall(), etc.
  /*if (Serial.available())
   switch(Serial.read())
  {
    case 't':
      SendTextMessage();
      break;
    case 'r':
      RecieveTextMessage();//This program code by directive'r'to receive, by receiving the information after the return to call the function 
                           //to verify receiving function. But it can not display the received content in SIM.
      DialVoiceCall();
      break;
    case 'd':
      DialVoiceCall();
      break;
    case 'h':
      SubmitHttpRequest();
      break;

  } */
 /*if (mySerial.available())
   Serial.write(mySerial.read());*/
   
         SubmitHttpRequest();
}
///SendTextMessage()
///this function is to send a sms message
 void SendTextMessage()
{
 mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
 delay(100);
 mySerial.println("AT + CMGS = \"+34665237327\"");//send sms message, be careful need to add a country code before the cellphone number
 delay(100);
 mySerial.println("A test message!");//the content of the message
 delay(100);
 mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
 delay(100);
 mySerial.println();
}
 void RecieveTextMessage()
  {
  //mySerial.print("AT+CMGF=1\r"); //Because we want to recieve the SMS in text mode
 //delay(100);
   mySerial.print("AT+CMGR=1\r");//Because we want to recieve the SMS in text mode
   delay(100);
   mySerial.println("AT + CSCA = \"+34665237327\"");//recieve sms message, be careful need to add a country code before the cellphone number
   delay(100);
   mySerial.println("A test message!");//the content of the message
   delay(100);
   mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
   delay(100);
   mySerial.println();
 //return r;
 }
///DialVoiceCall
///this function is to dial a voice call
void DialVoiceCall()
{
 mySerial.println("ATD + +34665237327;");//dial the number
 delay(100);
 mySerial.println();
}
///SubmitHttpRequest()
///this function is submit a http request
///attention:the time of delay is very important, it must be set enough 
void SubmitHttpRequest()
{
 mySerial.println("AT+CSQ");
 delay(100);
 ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
 mySerial.println("AT+CGATT?");
 delay(100);
 ShowSerialData();
 mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
 delay(1000);
 ShowSerialData();
 mySerial.println("AT+SAPBR=3,1,\"APN\",\"gprs-service.com\"");//setting the APN, the second need you fill in your local apn server
 delay(4000);
 ShowSerialData();
 mySerial.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
 delay(2000);
 ShowSerialData();
 mySerial.println("AT+HTTPINIT"); //init the HTTP request
 delay(2000); 
 ShowSerialData();
 mySerial.println("AT+HTTPPARA=\"URL\",\"http://sltp.es/prots.php?estado=66*\"");// setting the httppara, the second parameter is the website you want to access
 delay(1000);
 ShowSerialData();
 mySerial.println("AT+HTTPACTION=0");//submit the request 
 delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
 //while(!mySerial.available());
 ShowSerialData();
 mySerial.println("AT+HTTPREAD");// read the data from the website you access
 delay(300);
 ShowSerialData();
 mySerial.println("");
 delay(100);
}
void ShowSerialData()
{
 while(mySerial.available()!=0)
   Serial.write(mySerial.read());
}
