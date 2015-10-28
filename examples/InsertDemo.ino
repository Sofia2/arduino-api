#include <aJSON.h>
#include <CommandMessageRequest.h>
#include <ConnectionConfig.h>
#include <KPMqtt.h>
#include <Listener4SIBCommandMessageNotifications.h>
#include <Listener4SIBIndicationNotifications.h>
#include <SSAPBodyJoinUserAndPasswordMessage.h>
#include <SSAPBodyOperationMessage.h>
#include <SSAPBodyQueryMessage.h>
#include <SSAPBodyReturnMessage.h>
#include <SSAPBodySubscribeMessage.h>
#include <SSAPBodyUnsubscribeMessage.h>
#include <SSAPMessage.h>
#include <SSAPMessageGenerator.h>

#include <SSAPMessageGenerator.h>
#include <SSAPBodyReturnMessage.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <KPMqtt.h>
#include <LightSensor.h>
#include <xxtea.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress ip( 192, 168, 1, 38 ); // Arduino IP
byte serverIp[] = { 168, 63, 107, 201 }; // Sofia2 Ip


boolean joined=false;

ConnectionConfig config;
KPMqtt kp;
SSAPMessageGenerator ssapGenerator;

int photoSensorPinIn = 0;//A0 input3

void setup() {
  Serial.begin( 9600 );
  
  config.setLocalMac(mac);
  config.setLocalIp(&ip);
  config.setServerIp(serverIp);
  
  kp.setClientId("Arduino");
  kp.setConnectionConfig(&config);
 
}

SSAPMessage joinMessage;


int vuelta=0;
void loop() {
  Serial.println("new Loop");
  Serial.print("Memoria antes de comenzar el loop()  : ");
  Serial.println(memoryTest());
  if(!joined){
    join();
  }
  Serial.println(joined);
  if(joined){
    meterValues();
  }

  Serial.print("End of Loop: ");
  Serial.println(vuelta);

 
  vuelta++;
  
  delay(1000);
}


void join(){
  if(!kp.isConnected()){
       Serial.println("connect");
       kp.connect();
    }
  
    Serial.println("Send join");
    joinMessage= ssapGenerator.generateJoinByTokenMessage("508454fc860b44b1a9075b71fe08cd67", "KPTestTemperatura:a1");

    SSAPMessage joinResponse=kp.send(&joinMessage);
    if(&joinResponse!=NULL){
        char* bodyJoin=joinMessage.getBody();
        
        delete[] bodyJoin;
        char* responseBody=joinResponse.getBody();
        
        SSAPBodyReturnMessage bodyMessage=SSAPBodyReturnMessage::fromJSonToSSAPMessage(responseBody);
        
        if(bodyMessage.isOk()){
          Serial.println("ok");
          joined=true;
        }else{
           Serial.println("ko");
          joined=false;
        }
        
        delete[] bodyMessage.getData();
        delete[] bodyMessage.getError();
        delete[] responseBody;
        delete[] joinResponse.getSessionKey();
        delete[] joinResponse.getMessageId();
        delete[] joinResponse.getOntology();
    }
}

SSAPMessage insertMessage;
void meterValues(){
    Serial.println("MeterValues");
    
	//Generates new SSAP INSERT message
    insertMessage = ssapGenerator.generateInsertMessage(kp.getSessionKey(), "TestSensorTemperatura", "{\"Sensor\":{ \"assetId\":\"string\",\"measure\":28.6}}");
   
    //Send the message to the SIB
    SSAPMessage insertResponse=kp.send(&insertMessage);
    
    char* responseBody=insertResponse.getBody();
    Serial.println(responseBody);
     
    //Free responseBody char*
    delete[] responseBody;
    
    //Free json char* memory
    delete[] sensorJson;
    delete[] insertMessage.getSessionKey();
    delete[] insertMessage.getBody();
    delete[] insertMessage.getOntology();
    
   delete[] insertResponse.getSessionKey();
   delete[] insertResponse.getMessageId();
   delete[] insertResponse.getOntology();
 
}

// this function will return the number of bytes currently free in RAM
int memoryTest() {
  int byteCounter = 0; // initialize a counter
  byte *byteArray; // create a pointer to a byte array
  // More on pointers here: http://en.wikipedia.org/wiki/Pointer#C_pointers

  // use the malloc function to repeatedly attempt allocating a certain number of bytes to memory
  // More on malloc here: http://en.wikipedia.org/wiki/Malloc
  while ( (byteArray = (byte*) malloc (byteCounter * sizeof(byte))) != NULL ) {
    byteCounter++; // if allocation was successful, then up the count for the next try
    free(byteArray); // free memory after allocating it
  }
  
  free(byteArray); // also free memory after the function finishes
  return byteCounter; // send back the highest number of bytes successfully allocated
}

