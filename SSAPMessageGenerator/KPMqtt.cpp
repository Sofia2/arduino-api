
#include "KPMqtt.h"
#include "../Ethernet/Ethernet.h"
#include "SSAPBodyReturnMessage.h"
#include "../xxtea/xxtea.h"
#include "Base64.h"

#define TOPIC_PUBLISH_PREFIX "/TOPIC_MQTT_PUBLISH"
#define TOPIC_SUBSCRIBE_INDICATION_PREFIX "/TOPIC_MQTT_INDICATION"
#define TOPIC_SIB_COMMANDER_PREFIX "/TOPIC_MQTT_SIB_COMMANDER"

#define MAX_RESPONSE_LOOP_RETRIES 10

/**
	Function that receives MQTT Server responses
*/
void KPMqtt::callback( char* topic, byte* payload, unsigned int length ){
	if(strcmp(topic, topicPublishForThisClient)==0){//Response of an SSAP message
		publishResponse=new char[length+1];
		for(int i=0;i<length;i++){
			publishResponse[i]=(char)payload[i];
		}
		publishResponse[length]='\0';
		
	}else if(strcmp(topic, topicIndicationForThisClient)==0){//Indication from subscription
		
		
	}else if(strcmp(topic, topicCommandForThisClient)==0){//Command from SIB
	}
	
}

/**
	Function to read notifications from SIB
*/
void KPMqtt::loopMqtt(){
	client.loop();
}

/**
 *Returs if the KP is currently connected to a SIB
 */
bool KPMqtt::isConnected(){
	return connected;
}

/**
 * Returns the SessionKey for the current connection with the SIB
 * Returns null if not connected to a SIB
 */
char* KPMqtt::getSessionKey(){
	return sessionKey;
}

/**
 * Connect physically this KP to a SIB
 */
void KPMqtt::connect(){
	if(connectionConfig){
		//Makes physical connection
		 if( Ethernet.begin( connectionConfig->getLocalMac() ) == 0 ) {
			Ethernet.begin( connectionConfig->getLocalMac(), *connectionConfig->getLocalIp() );
		}
		
		EthernetClient ethClient;
		client = PubSubClient( connectionConfig->getServerIp(), 1883, this, ethClient );
		client.connect(clientId);
		
		connected=true;

		//Once connected it subscribes to SIB notification topics
		topicPublishForThisClient=new char[strlen(TOPIC_PUBLISH_PREFIX) + strlen(clientId)+1];
		strcpy(topicPublishForThisClient, TOPIC_PUBLISH_PREFIX);
		strcat(topicPublishForThisClient, clientId);
		client.subscribe( topicPublishForThisClient);
		
		topicIndicationForThisClient=new char[strlen(TOPIC_SUBSCRIBE_INDICATION_PREFIX) + strlen(clientId)+1];
		strcpy(topicIndicationForThisClient, TOPIC_SUBSCRIBE_INDICATION_PREFIX);
		strcat(topicIndicationForThisClient, clientId);
		client.subscribe( topicIndicationForThisClient );
		
		topicCommandForThisClient=new char[strlen(TOPIC_SIB_COMMANDER_PREFIX) + strlen(clientId)+1];
		strcpy(topicCommandForThisClient, TOPIC_SIB_COMMANDER_PREFIX);
		strcat(topicCommandForThisClient, clientId);
		client.subscribe( topicCommandForThisClient );

	}
}

/**
 * Makes a disconnection of the physical protocol
 */
void KPMqtt::disconnect(){
	if(connected){
	
		char* topicPublishForThisClient=new char[strlen(TOPIC_PUBLISH_PREFIX) + strlen(clientId)+1];
		strcpy(topicPublishForThisClient, TOPIC_PUBLISH_PREFIX);
		strcat(topicPublishForThisClient, clientId);
		client.unsubscribe( topicPublishForThisClient);
		
		
		char* topicIndicationForThisClient=new char[strlen(TOPIC_SUBSCRIBE_INDICATION_PREFIX) + strlen(clientId)+1];
		strcpy(topicIndicationForThisClient, TOPIC_SUBSCRIBE_INDICATION_PREFIX);
		strcat(topicIndicationForThisClient, clientId);
		client.unsubscribe( topicIndicationForThisClient );
		
		
		char* topicCommandForThisClient=new char[strlen(TOPIC_SIB_COMMANDER_PREFIX) + strlen(clientId)+1];
		strcpy(topicCommandForThisClient, TOPIC_SIB_COMMANDER_PREFIX);
		strcat(topicCommandForThisClient, clientId);
		client.unsubscribe( topicCommandForThisClient );

		client.disconnect();
		connected=false;
		
		//It is not necessary to destroy client Object
	}
	
}


/**
 * Configuration parameters for the connection
 */
void KPMqtt::setConnectionConfig(ConnectionConfig* config){
	connectionConfig=config;
}

/**
 * Sends to the SIB a SSAP message
 * @return
 */
SSAPMessage KPMqtt::send(SSAPMessage* msg){
	//The server does not need a topic
	char* msgJson=msg->toJson();
	
	client.publish( "", msgJson);
		
	delete[] msgJson;
	
	
	publishResponse=NULL;
	for(int i=0; i<MAX_RESPONSE_LOOP_RETRIES && publishResponse==NULL;i++){
		delay(1000);
		client.loop();
	}
	 
	if(publishResponse!=NULL){
		SSAPMessage response = SSAPMessage::fromJSonToSSAPMessage(publishResponse);
		delete[] publishResponse;
		publishResponse=NULL;
		if(response.getMessageType()==JOIN){
			char* responseBody=response.getBody();//Body lo borro en la funcion principal del programa
			
			SSAPBodyReturnMessage bodyMessage=SSAPBodyReturnMessage::fromJSonToSSAPMessage(responseBody);
			
			if(bodyMessage.isOk()){
				delete[] sessionKey;
				sessionKey=new char[strlen(bodyMessage.getData())+1];
				
				strcpy(sessionKey, bodyMessage.getData());
			}
			
			delete[] bodyMessage.getData();
			delete[] bodyMessage.getError();
			
		}
		
		return response;
	}
	

}



SSAPMessage KPMqtt::sendEncrypt(char* msgJson, unsigned char* key, int keyLength){
	
	//The server does not need a topic
	//char* msgJson=msg->toJson();
	//Serial.println(msgJson);
	

	xxtea_long len=strlen(msgJson);
	xxtea_long encryptedLength=0;
	
	unsigned char *result=new unsigned char[690];
	
	//Serial.println("Antes de encriptar");
	unsigned char* encryptedMsg = xxtea_encrypt((unsigned char *)msgJson, len, key, keyLength, &encryptedLength, result);
	//Serial.print("Despues de encriptar, Longitud: ");
	//Serial.println(encryptedLength);
	//Codificado en Base64, ya no es necesario con los cambios hechos en la libreria
	
	delete[] msgJson;
	
	//Serial.print("Memoria antes de codificar a base64: ");
	//Serial.println(memoryTest());
	
	char* encodedOutput=new char[690];
	int codedLength = base64_encode(encodedOutput, reinterpret_cast<char*>(encryptedMsg), encryptedLength);
	//Serial.println("Despues de codificar, Longitud: ");
	//Serial.println(codedLength);
	
	//Serial.print("Memoria despues de codificar a base64: ");
	//Serial.println(memoryTest());
	
	delete[] encryptedMsg;
	
	char* adjustedEncodedOutput=new char[codedLength+1];
	for(int i=0;i<codedLength;i++){
		adjustedEncodedOutput[i]=encodedOutput[i];
	}
	adjustedEncodedOutput[codedLength]='\0';
	
	delete[] encodedOutput;
	
	//Serial.println("Antes de publicar");
	client.publish("", (uint8_t*)adjustedEncodedOutput, codedLength, false);
	//Serial.println("Despues de publicar");
	delete[] adjustedEncodedOutput;
	
	publishResponse=NULL;
	
	
	for(int i=0; i<MAX_RESPONSE_LOOP_RETRIES && publishResponse==NULL;i++){
		delay(1000);
		client.loop();
		//Serial.println("Esperando respuesta");
	}
	
	//Serial.println("Antes de comprobar el nulo:");
	//Serial.println(publishResponse);
	
	//Hasta aqui no se pierde memoria en memory leaks
	if(publishResponse!=NULL){
		char* decodedOutput=new char[690];
		int decodedLenght = base64_decode(decodedOutput, publishResponse, strlen(publishResponse));
		delete[] publishResponse;
		
		
		Serial.print("Longitud decodificado");
		Serial.println(decodedLenght);
		Serial.println("##################################");
		unsigned char* adjustedDecodedOutput=new unsigned char[decodedLenght];
		for(int i=0;i<decodedLenght;i++){
			adjustedDecodedOutput[i]=(unsigned char)decodedOutput[i];
			Serial.print((int) adjustedDecodedOutput[i]);
		}
		Serial.println("\n##################################");
	
		delete[] decodedOutput;
		
		
		xxtea_long *ret_len;
		Serial.println("Antes de descifrar");
		//intentar eso, pasar el argumento del resultado por parametros, y que se declare antes para que no lo haga el malloc
		unsigned char *result2=new unsigned char[690];
		unsigned char * decryptedMsg = xxtea_decrypt(adjustedDecodedOutput, decodedLenght, key, keyLength, ret_len, result2);
		/*Serial.println("Parte del desencriptado");
		for(int i=0;i<100;i++){
			Serial.print((char)result2[i]);
		}
		Serial.println("Parte del desencriptado");*/
		
	/*	Serial.println("Despues de descifrar");

		Serial.println("Longitud Respuesta descifrada: ");
		Serial.println((int)ret_len);
		
		Serial.println("Respuesta descifrada: ");
		Serial.println((char*)decryptedMsg);
		
		delete[] adjustedDecodedOutput;*/
		
		/*
		SSAPMessage response = SSAPMessage::fromJSonToSSAPMessage((char*)decryptedMsg);
		delete[] decryptedMsg;
		
		if(response.getMessageType()==JOIN){
			char* responseBody=response.getBody();//Body lo borro en la funcion principal del programa
			SSAPBodyReturnMessage bodyMessage=SSAPBodyReturnMessage::fromJSonToSSAPMessage(responseBody);
			if(bodyMessage.isOk()){
				delete[] sessionKey;
				sessionKey=new char[strlen(bodyMessage.getData())+1];
				strcpy(sessionKey, bodyMessage.getData());
			}
			
			delete[] bodyMessage.getData();
			delete[] bodyMessage.getError();
		}
		return response;*/
	}

}

/**
* clientId setter
*/
void KPMqtt::setClientId(char* cId){
	/*clientId=new char[strlen(cId)+1];
	strcpy(clientId, cId);*/
	clientId=cId;
}

/**
* clientId getter
*/
char* KPMqtt::getClientId(){
	return clientId;
}
	
/**
 * Registers a  listener to listen notifications for subscriptions.
 * @param listener
 */
void KPMqtt::addListener4SIBNotifications(Listener4SIBIndicationNotifications listener){
}

/**
 * Unregister a  listener to listen notifications for subscriptions.
 * @param listener
 */
 void KPMqtt::removeListener4SIBNotifications(Listener4SIBIndicationNotifications listener){
 }
 
	
/**
 * Register a listener to recevice command messages from SIB
 * @param listener
 */
void KPMqtt::addListener4SIBCommandMessageNotifications(Listener4SIBCommandMessageNotifications listener){
}

/**
 * Unregister a listener to recevice command messages from SIB
 * @param listener
 */
 void KPMqtt::removeListener4SIBCommandMessageNotifications(Listener4SIBCommandMessageNotifications listener){
 }
	 


// this function will return the number of bytes currently free in RAM
int KPMqtt::memoryTest() {
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