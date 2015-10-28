#include "SSAPBodyReturnMessage.h"

#include "aJSON.h"
#include "string.h"

/*SSAPBodyReturnMessage::~SSAPBodyReturnMessage(){
	Serial.println("SSAPBodyReturnMessage::~SSAPBodyReturnMessage()");
	delete[] data;
	delete[] error;
	free(ok);
}*/

/*
* data getter
*/
char* SSAPBodyReturnMessage::getData(){
	return data;
}

/*
* data setter
*/
void SSAPBodyReturnMessage::setData(char* d){
	/*data=new char[strlen(d)+1];
	strcpy(data, d);*/
	data=d;
}
	
/*
* ok getter
*/
bool SSAPBodyReturnMessage::isOk(){
	return ok;

}

/*
* query setter
*/
void SSAPBodyReturnMessage::setOk(bool o){
	ok=o;
}


/*
* error getter
*/
char* SSAPBodyReturnMessage::getError(){
	return error;

}

/*
* error setter
*/
void SSAPBodyReturnMessage::setError(char* err){
	/*error=new char[strlen(err)+1];
	strcpy(error, err);*/
	error=err;
}

/*
	toJson method convert this object to a json String
*/
char* SSAPBodyReturnMessage::toJson(){
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	if(data){//Not null
		aJson.addStringToObject(thisObject,"data", data);
	}else{
		aJson.addNullToObject(thisObject,"data");
	}
	
	if(ok){//true
		aJson.addTrueToObject(thisObject, "ok");
	}else{
		aJson.addFalseToObject(thisObject,"ok");
	}
	
	if(error){//Not null
		aJson.addStringToObject(thisObject, "error", error);
	}else{
		aJson.addNullToObject(thisObject,"error");
	}

	char* jsonString=aJson.print(thisObject);
	
	//Recovers memory space
	aJson.deleteItem( thisObject);
	
	return jsonString;
}

/*
	FromJSon method convert a json String to a SSAPBodyReturnMessage
*/
SSAPBodyReturnMessage SSAPBodyReturnMessage::fromJSonToSSAPMessage(char* jsonString){
	//Parses the String o an aJSon object
	aJsonObject *receivedObject=aJson.parse(jsonString);

	//Recover all properties
	aJsonObject* dat = aJson.getObjectItem(receivedObject , "data");
	aJsonObject* o = aJson.getObjectItem(receivedObject , "ok");
	aJsonObject* err = aJson.getObjectItem(receivedObject , "error");
	
	//Creates the SSAPBodyReturnMessage to return
	SSAPBodyReturnMessage messageToReturn;

	//Sets Al properties
	//copies the char* to delete the aJsonObject
	char* dataStr=new char[strlen(dat->valuestring)+1];
	strcpy(dataStr, dat->valuestring);
	messageToReturn.setData(dataStr);
	
	if((bool)o->valuebool){
		messageToReturn.setOk(true);
	}else{
		messageToReturn.setOk(false);
	}
	
	char* errorStr=new char[strlen(err->valuestring)+1];
	strcpy(errorStr, err->valuestring);
	messageToReturn.setError(errorStr);

	aJson.deleteItem(receivedObject);
	
	return messageToReturn;
}

