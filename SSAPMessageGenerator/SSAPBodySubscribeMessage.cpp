#include "SSAPBodySubscribeMessage.h"

#include "aJSON.h"
#include "string.h"


/*
* msRefresh getter
*/
int SSAPBodySubscribeMessage::getMsRefresh(){
	return msRefresh;
}

/*
* msRefresh setter
*/
void SSAPBodySubscribeMessage::setMsRefresh(int refr){
	msRefresh=refr;
}
	
/*
* query getter
*/
char* SSAPBodySubscribeMessage::getQuery(){
	return query;

}

/*
* query setter
*/
void SSAPBodySubscribeMessage::setQuery(char* q){
	/*query=new char[strlen(q)+1];
	strcpy(query, q);*/
	query=q;
}



/*
	toJson method convert this object to a json String
*/
char* SSAPBodySubscribeMessage::toJson(){
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	
	aJson.addNumberToObject(thisObject,"msRefresh", msRefresh);
	
	if(query){//Not null
		aJson.addStringToObject(thisObject, "query", query);
	}else{
		aJson.addNullToObject(thisObject,"query");
	}

	return aJson.print(thisObject);
}

/*
	FromJSon method convert a json String to a SSAPBodySubscribeMessage
*/
SSAPBodySubscribeMessage SSAPBodySubscribeMessage::fromJSonToSSAPMessage(char* jsonString){
	//Parses the String o an aJSon object
	aJsonObject *receivedObject=aJson.parse(jsonString);
	
	//Recover all properties
	aJsonObject* mRef = aJson.getObjectItem(receivedObject , "msRefresh");
	aJsonObject* quer = aJson.getObjectItem(receivedObject , "query");
	
	
	//Creates the SSAPBodySubscribeMessage to return
	SSAPBodySubscribeMessage messageToReturn;
	
	//Sets Al properties
	messageToReturn.setMsRefresh(mRef->valueint);
	messageToReturn.setQuery(quer->valuestring);
	
	return messageToReturn;
}

