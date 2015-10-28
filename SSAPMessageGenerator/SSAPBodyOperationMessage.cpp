#include "SSAPBodyOperationMessage.h"

#include "aJSON.h"
#include "string.h"

/*
* data getter
*/
char* SSAPBodyOperationMessage::getData(){
	return data;
}

/*
* data setter
*/
void SSAPBodyOperationMessage::setData(char* d){
	/*data=new char[strlen(d)+1];
	strcpy(data, d);*/
	data=d;
}
	
/*
* query getter
*/
char* SSAPBodyOperationMessage::getQuery(){
	return query;

}

/*
* query setter
*/
void SSAPBodyOperationMessage::setQuery(char* q){
	/*query=new char[strlen(q)+1];
	strcpy(query, q);*/
	query=q;
}

/*
	toJson method convert this object to a json String
*/
char* SSAPBodyOperationMessage::toJson(){
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	if(data){//Not null
		aJson.addStringToObject(thisObject,"data", data);
	}else{
		aJson.addNullToObject(thisObject,"data");
	}
	
	if(query){//Not null
		aJson.addStringToObject(thisObject, "query", query);
	}else{
		aJson.addNullToObject(thisObject,"query");
	}

	return aJson.print(thisObject);
}

/*
	FromJSon method convert a json String to a SSAPBodyOperationMessage
*/
SSAPBodyOperationMessage SSAPBodyOperationMessage::fromJSonToSSAPMessage(char* jsonString){
	//Parses the String o an aJSon object
	aJsonObject *receivedObject=aJson.parse(jsonString);
	
	//Recover all properties
	aJsonObject* dat = aJson.getObjectItem(receivedObject , "data");
	aJsonObject* quer = aJson.getObjectItem(receivedObject , "query");
	
	
	//Creates the SSAPMessage to return
	SSAPBodyOperationMessage messageToReturn;
	
	//Sets Al properties
	messageToReturn.setData(dat->valuestring);
	messageToReturn.setQuery(quer->valuestring);
	
	return messageToReturn;
}

