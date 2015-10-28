#include "SSAPBodyQueryMessage.h"

#include "aJSON.h"
#include "string.h"

	
/*
* query getter
*/
char* SSAPBodyQueryMessage::getQuery(){
	return query;

}

/*
* password setter
*/
void SSAPBodyQueryMessage::setQuery(char* q){
	/*query=new char[strlen(q)+1];
	strcpy(query, q);*/
	query=q;
}

/*
	toJson method convert this object to a json String
*/
char* SSAPBodyQueryMessage::toJson(){
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	
	if(query){//Not null
		aJson.addStringToObject(thisObject, "query", query);
	}else{
		aJson.addNullToObject(thisObject,"query");
	}

	return aJson.print(thisObject);
}

/*
	FromJSon method convert a json String to a SSAPBodyQueryMessage
*/
SSAPBodyQueryMessage SSAPBodyQueryMessage::fromJSonToSSAPMessage(char* jsonString){
	//Parses the String o an aJSon object
	aJsonObject *receivedObject=aJson.parse(jsonString);
	
	//Recover all properties
	aJsonObject* quer = aJson.getObjectItem(receivedObject , "query");
	
	//Creates the SSAPMessage to return
	SSAPBodyQueryMessage messageToReturn;
	
	//Sets Al properties
	messageToReturn.setQuery(quer->valuestring);
	
	return messageToReturn;
}

