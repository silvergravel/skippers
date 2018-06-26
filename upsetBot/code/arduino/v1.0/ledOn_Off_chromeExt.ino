#include <SoftwareSerial.h>

#define DEBUG true




SoftwareSerial esp8266(8, 9); // make RX Arduino line is pin 8, make TX Arduino line is pin 9.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different

  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  sendData("AT+RST\r\n", 2000, DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n", 1000, DEBUG); // configure as access point
  sendData("AT+CWLAP\r\n", 7000, DEBUG); // configure as station
  sendData("AT+CIPSTA=\"192.168.2.95\"\r\n", 10000, DEBUG);
  sendData("AT+CWJAP=\"zeb\",\"eaglehaslanded1964\"\r\n", 10000, DEBUG);
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80
}

void loop()
{
  if (esp8266.available()) // check if the esp is sending a message
  {

    Serial.println("i can see esp");


    if (esp8266.find("+IPD,"))
    Serial.println("esp is saying IPD");
    {

      if (esp8266.overflow()) {
        Serial.println("SoftwareSerial overflow!");
      }


      //
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns
      // the ASCII decimal value and 0 (the first decimal number) starts at 48


      esp8266.find("led="); // advance cursor to "pin="


      int command = (esp8266.read() - 48); // get number (either 0 or 1) 

     if(command == 0){
        digitalWrite(11,LOW);
        Serial.println("turn led OFF!");
      }else if (command == 1){
        digitalWrite(11,HIGH);
        Serial.println("turn led ON!");
        }

      // make close command
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";

      sendData(closeCommand, 1000, DEBUG); // close connection
    }
  }
}

/*
  Name: sendData
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  esp8266.print(command); // send the read character to the esp8266

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {

      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.println("*************************************");
    Serial.println("debug response is: ");
    Serial.print(response);
  }

  return response;
}
