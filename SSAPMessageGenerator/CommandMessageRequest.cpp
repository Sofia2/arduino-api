
#include "CommandMessageRequest.h"
#include "string.h"
#include "aJSON.h"

/**
 	messageId getter
 */
char* CommandMessageRequest::getMessageId (){
	return messageId;
}

/**
 	messageId setter
 */
void CommandMessageRequest::setMessageId (char* mId){
	/*messageId=new char[strlen(mId)+1];
	strcpy(messageId, mId);*/
	messageId=mId;
}

/**
 	commandType getter
 */
CommandType CommandMessageRequest::getCommandType(){
	return commandType;
}

/**
 	commandType setter
 */
void CommandMessageRequest::setCommandType(CommandType cType){
	commandType=cType;
}

/**
 	commandMessage getter
 */
char* CommandMessageRequest::getCommandMessage(){
	return commandMessage;
}

/**
 	commandMessage setter
 */
void CommandMessageRequest::setCommandMessage(char* cMessage){
	/*commandMessage=new char[strlen(cMessage)+1];
	strcpy(commandMessage, cMessage);*/
	commandMessage=cMessage;
}

/*
 	Returns this object as a JSon String
 */
char* CommandMessageRequest::toJson(){
		
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	if(messageId){//Not null
		aJson.addStringToObject(thisObject,"messageId", messageId);
	}else{
		aJson.addNullToObject(thisObject,"messageId");
	}
	
	
	
	switch(commandType){
		case DEVICE_STATUS: 	
				aJson.addStringToObject(thisObject, "commandType", "DEVICE_STATUS");
				break;
		case BATERY_STATUS:	
				aJson.addStringToObject(thisObject, "commandType", "BATERY_STATUS");
				break;
		default: 
				aJson.addNullToObject(thisObject,"commandType");
	}
	

	
	if(commandMessage){//Not null
		aJson.addStringToObject(thisObject, "commandMessage", commandMessage);
	}else{
		aJson.addNullToObject(thisObject,"commandMessage");
	}
	

	return aJson.print(thisObject);
}


