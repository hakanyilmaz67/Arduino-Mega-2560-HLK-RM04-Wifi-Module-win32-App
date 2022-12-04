#include <WiFiRM04.h>

int keyIndex = 0;                 // your network key Index number (needed only for WEP)

char ssid[] = "......d";
char pass[] = "......";

int status = WL_IDLE_STATUS;
WiFiRM04Server server(8090);





void setup() {
  Serial.begin(57600);      // initialize serial communication
  pinMode(7, OUTPUT);      // set the LED pin mode
  pinMode(8, OUTPUT);      // set the LED pin mode
  pinMode(9, OUTPUT);      // set the LED pin mode

  digitalWrite(7, LOW); 
  digitalWrite(8, LOW);  
  digitalWrite(9, LOW);  


  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    while(true);        // don't continue
  } 

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                

   
    status = WiFi.begin(ssid, pass);
   
    delay(4000);
  } 
  server.begin();                           // start the web server on port 80
 
}

void loop() {
  WiFiRM04Client client = server.available();   // listen for incoming clients

  if (client) {                             
    Serial.println("new client");          
    String currentLine = "";               
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    

        
          if (currentLine.length() == 0) {  
             break;         
          } 
          else {      
            currentLine = "";
          }
        }     
        else if (c != '\r') {    
          currentLine += c;     
        }

        
        if (currentLine.endsWith("A1")) {
          digitalWrite(7, HIGH);               
        }
        if (currentLine.endsWith("A0")) {
          digitalWrite(7, LOW);                
        }
        
         if (currentLine.endsWith("B1")) {
           digitalWrite(8, HIGH);               
         }
         if (currentLine.endsWith("B0")) {
           digitalWrite(8, LOW);                
         }
       
         if (currentLine.endsWith("C1")) {
           digitalWrite(9, HIGH);               
         }
         if (currentLine.endsWith("C0")) {
           digitalWrite(9, LOW);                
         }




      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}




