#include "ssapmessage.h"
#include "string.h"
#include "aJSON.h"

	/*SSAPMessage::~SSAPMessage(){
		Serial.println("SSAPMessage.Destructor");
		//delete[] messageId;
		//delete[] ontology;
		
	}*/

	/* 
	 	MessageId getter
	 */
	char* SSAPMessage::getMessageId(){
		return messageId;
	}

	/* 
	 	MessageId setter
	 */
	void SSAPMessage::setMessageId(char* mId){
		/*messageId=new char[strlen(mId)+1];
		strcpy (messageId, mId );*/
		messageId=mId;
	}


	/*
	 	SessionKey getter
	 */
	char* SSAPMessage::getSessionKey(){
		return sessionKey;
	}

	/*
	 	SessionKey setter
	 */
	void SSAPMessage::setSessionKey(char* sKey){
		/*sessionKey=new char[strlen(sKey)+1];
		strcpy(sessionKey, sKey);*/
		sessionKey=sKey;
	}
	
	/*
	 	ontology getter
	 */
	char* SSAPMessage::getOntology(){
		return ontology;
	}

	/*
	 	ontology setter
	 */
	void SSAPMessage::setOntology(char* ont){
		/*ontology=new char[strlen(ont)+1];
		strcpy(ontology, ont);*/
		ontology=ont;
	}


	/*
	 	direction getter
	 */
	SSAPMessageDirection SSAPMessage::getDirection(){
		return direction;
	}

	/*
	 	direction setter
	 */
	void SSAPMessage::setDirection(SSAPMessageDirection dir){
		direction=dir;
	}
	

	/*
	 	messageType getter
	 */
	SSAPMessageTypes SSAPMessage::getMessageType(){
		return messageType;
	}

	/*
	 	direction setter
	 */
	void SSAPMessage::setMessageType(SSAPMessageTypes mType){
		messageType=mType;
	}


	/*
	 	persistenceType getter
	 */
	SSAPPersistenceType SSAPMessage::getPersistenceType(){
		return persistenceType;
	}

	/*
	 	persistenceType setter
	 */
	void SSAPMessage::setPersistenceType(SSAPPersistenceType pType){
		persistenceType=pType;
	}

	/*
	 	body getter
	 */
	char* SSAPMessage::getBody(){
		return body;
	}

	/*
	 	body setter
	 */
	void SSAPMessage::setBody(char* bod){
		/*body=new char[strlen(bod)+1];
		strcpy(body, bod);*/
		body=bod;
	}
	
	char* SSAPMessage::toJson(){
		
		aJsonObject *thisObject;
		thisObject=aJson.createObject();
		if(messageId){//Not null
			aJson.addStringToObject(thisObject,"messageId", messageId);
		}else{
			aJson.addNullToObject(thisObject,"messageId");
		}
		
		if(sessionKey){//Not null
			aJson.addStringToObject(thisObject, "sessionKey", sessionKey);
		}else{
			aJson.addNullToObject(thisObject,"sessionKey");
		}
		if(ontology){//Not null
			aJson.addStringToObject(thisObject, "ontology", ontology);
		}else{
			aJson.addNullToObject(thisObject,"ontology");
		}
		
		switch(direction){
			case REQUEST: 	
					aJson.addStringToObject(thisObject, "direction", "REQUEST");
					break;
			case RESPONSE:	
					aJson.addStringToObject(thisObject, "direction", "RESPONSE");
					break;
			case ERROR:
					aJson.addStringToObject(thisObject, "direction", "ERROR");
					break;
			default: 
					aJson.addNullToObject(thisObject,"direction");
		}
		
		switch(messageType){
			case JOIN: 	
					aJson.addStringToObject(thisObject, "messageType", "JOIN");
					break;
			case LEAVE:	
					aJson.addStringToObject(thisObject, "messageType", "LEAVE");
					break;
			case INSERT:
					aJson.addStringToObject(thisObject, "messageType", "INSERT");
					break;
			case UPDATE:
					aJson.addStringToObject(thisObject, "messageType", "UPDATE");
					break;
			case DELETE:
					aJson.addStringToObject(thisObject, "messageType", "DELETE");
					break;
			case QUERY:
					aJson.addStringToObject(thisObject, "messageType", "QUERY");
					break;
			case SUBSCRIBE:
					aJson.addStringToObject(thisObject, "messageType", "SUBSCRIBE");
					break;
			case UNSUBSCRIBE:
					aJson.addStringToObject(thisObject, "messageType", "UNSUBSCRIBE");
					break;
			case INDICATION:
					aJson.addStringToObject(thisObject, "messageType", "INDICATION");
					break;
			default: 
					aJson.addNullToObject(thisObject,"messageType");
		}
		
		switch(persistenceType){
			case MONGODB: 	
					aJson.addStringToObject(thisObject, "persistenceType", "MONGODB");
					break;
			case INMEMORY:	
					aJson.addStringToObject(thisObject, "persistenceType", "INMEMORY");
					break;
			default: 
					aJson.addNullToObject(thisObject,"persistenceType");
		}
		
		if(body){//Not null
			aJson.addStringToObject(thisObject, "body", body);
		}else{
			aJson.addNullToObject(thisObject,"body");
		}
		
	
		char* jsonString = aJson.print(thisObject);
		
		//Recovers memory space
		aJson.deleteItem(thisObject);
		
		return jsonString;
	}
	
	SSAPMessage SSAPMessage::fromJSonToSSAPMessage(char* jsonString){
		//Parses the String o an aJSon object
		aJsonObject *receivedObject=aJson.parse(jsonString);
		
		//Recover all properties
		aJsonObject* mId = aJson.getObjectItem(receivedObject , "messageId");
		aJsonObject* sKey = aJson.getObjectItem(receivedObject , "sessionKey");
		aJsonObject* ont = aJson.getObjectItem(receivedObject , "ontology");
		aJsonObject* dir = aJson.getObjectItem(receivedObject , "direction");
		aJsonObject* mType = aJson.getObjectItem(receivedObject , "messageType");
		aJsonObject* pers = aJson.getObjectItem(receivedObject , "persistenceType");
		aJsonObject* bod = aJson.getObjectItem(receivedObject , "body");
		
		//Creates the SSAPMessage to return
		SSAPMessage messageToReturn;
		
		//Sets Al properties
		//copies the char* to delete the aJsonObject
		char* mIdStr=new char[strlen(mId->valuestring)+1];
		strcpy(mIdStr, mId->valuestring);
		messageToReturn.setMessageId(mIdStr);
		
		char* sKeyStr=new char[strlen(sKey->valuestring)+1];
		strcpy(sKeyStr, sKey->valuestring);
		messageToReturn.setSessionKey(sKeyStr);
		
		char* ontStr=new char[strlen(ont->valuestring)+1];
		strcpy(ontStr, ont->valuestring);
		messageToReturn.setOntology(ontStr);
		
		
		
		
		if(dir->valuestring!=NULL){
			if(strcmp(dir->valuestring, "REQUEST")==0){ 	
				messageToReturn.setDirection(REQUEST);		
			}else if(strcmp(dir->valuestring, "RESPONSE")==0){
				messageToReturn.setDirection(RESPONSE);
			}else if(strcmp(dir->valuestring, "ERROR")==0){
				messageToReturn.setDirection(ERROR);	
			}
		}
			
			
		if((mType->valuestring)!=NULL){
			if(strcmp(mType->valuestring, "JOIN")==0){ 	
				messageToReturn.setMessageType(JOIN);
			}else if(strcmp(mType->valuestring, "LEAVE")==0){
				messageToReturn.setMessageType(LEAVE);
			}else if(strcmp(mType->valuestring, "INSERT")==0){
				messageToReturn.setMessageType(INSERT);
			}else if(strcmp(mType->valuestring, "UPDATE")==0){
				messageToReturn.setMessageType(UPDATE);
			}else if(strcmp(mType->valuestring, "DELETE")==0){
				messageToReturn.setMessageType(DELETE);
			}else if(strcmp(mType->valuestring, "QUERY")==0){
				messageToReturn.setMessageType(QUERY);
			}else if(strcmp(mType->valuestring, "SUBSCRIBE")==0){
				messageToReturn.setMessageType(SUBSCRIBE);
			}else if(strcmp(mType->valuestring, "UNSUBSCRIBE")==0){
				messageToReturn.setMessageType(UNSUBSCRIBE);
			}else if(strcmp(mType->valuestring, "INDICATION")==0){
				messageToReturn.setMessageType(INDICATION);
			}
		}
		

		if(pers->valuestring!=NULL){
			if(strcmp(pers->valuestring, "MONGODB")==0){ 	
				messageToReturn.setPersistenceType(MONGODB);
			}else if(strcmp(pers->valuestring, "INMEMORY")==0){ 	
				messageToReturn.setPersistenceType(INMEMORY);
			}
		}

		char* bodyStr=new char[strlen(bod->valuestring)+1];
		
		strcpy(bodyStr, bod->valuestring);
		messageToReturn.setBody(bodyStr);
		
		
		aJson.deleteItem(receivedObject);
					
		
		return messageToReturn;
	}

