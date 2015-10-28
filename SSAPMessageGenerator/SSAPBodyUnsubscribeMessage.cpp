#include "SSAPBodyUnsubscribeMessage.h"

#include "aJSON.h"
#include "string.h"


/*
* idSuscripcion getter
*/
char* SSAPBodyUnsubscribeMessage::getIdSuscripcion(){
	return idSuscripcion;
}

/*
* idSuscripcion setter
*/
void SSAPBodyUnsubscribeMessage::setIdSuscripcion(char* id){
	/*idSuscripcion=new char[strlen(id)+1];
	strcpy(idSuscripcion, id);*/
	idSuscripcion=id;
}


/*
	toJson method convert this object to a json String
*/
char* SSAPBodyUnsubscribeMessage::toJson(){
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	
	if(idSuscripcion){//Not null
		aJson.addStringToObject(thisObject, "idSuscripcion", idSuscripcion);
	}else{
		aJson.addNullToObject(thisObject,"idSuscripcion");
	}

	return aJson.print(thisObject);
}

/*
	FromJSon method convert a json String to a SSAPBodyUnsubscribeMessage
*/
SSAPBodyUnsubscribeMessage SSAPBodyUnsubscribeMessage::fromJSonToSSAPMessage(char* jsonString){
	//Parses the String o an aJSon object
	aJsonObject *receivedObject=aJson.parse(jsonString);
	
	//Recover all properties
	aJsonObject* id = aJson.getObjectItem(receivedObject , "idSuscripcion");
	
	
	//Creates the SSAPBodyUnsubscribeMessage to return
	SSAPBodyUnsubscribeMessage messageToReturn;
	
	//Sets Al properties
	messageToReturn.setIdSuscripcion(id->valuestring);
	
	return messageToReturn;
}

