#include "SSAPBodyJoinUserAndPasswordMessage.h"

#include "aJSON.h"
#include "string.h"

/*
* user getter
*/
char* SSAPBodyJoinUserAndPasswordMessage::getUser(){
	return user;
}

/*
* user setter
*/
void SSAPBodyJoinUserAndPasswordMessage::setUser(char* u){
	/*user=new char[strlen(u)+1];
	strcpy(user, u);*/
	user=u;
}
	
/*
* password getter
*/
char* SSAPBodyJoinUserAndPasswordMessage::getPassword(){
	return password;

}

/*
* password setter
*/
void SSAPBodyJoinUserAndPasswordMessage::setPassword(char* p){
	/*password=new char[strlen(p)+1];
	strcpy(password, p);*/
	password=p;
}

/*
* instance getter
*/
char* SSAPBodyJoinUserAndPasswordMessage::getInstance(){
	return instance;
}

/*
* instance setter
*/
void SSAPBodyJoinUserAndPasswordMessage::setInstance(char* i){
	instance=i;
}

/*
	toJson method convert this object to a json String
*/
char* SSAPBodyJoinUserAndPasswordMessage::toJson(){
	aJsonObject *thisObject;
	thisObject=aJson.createObject();
	if(user){//Not null
		aJson.addStringToObject(thisObject,"user", user);
	}else{
		aJson.addNullToObject(thisObject,"user");
	}
	
	if(password){//Not null
		aJson.addStringToObject(thisObject, "password", password);
	}else{
		aJson.addNullToObject(thisObject,"password");
	}
	
	if(instance){//Not null
		aJson.addStringToObject(thisObject, "instance", instance);
	}else{
		aJson.addNullToObject(thisObject,"instance");
	}

	return aJson.print(thisObject);
}

/*
	FromJSon method convert a json String to a SSAPBodyJoinUserAndPasswordMessage
*/
SSAPBodyJoinUserAndPasswordMessage SSAPBodyJoinUserAndPasswordMessage::fromJSonToSSAPMessage(char* jsonString){
	//Parses the String o an aJSon object
	aJsonObject *receivedObject=aJson.parse(jsonString);
	
	//Recover all properties
	aJsonObject* usr = aJson.getObjectItem(receivedObject , "user");
	aJsonObject* psw = aJson.getObjectItem(receivedObject , "password");
	aJsonObject* kpId = aJson.getObjectItem(receivedObject , "instance");
	
	
	//Creates the SSAPMessage to return
	SSAPBodyJoinUserAndPasswordMessage messageToReturn;
	
	//Sets Al properties
	messageToReturn.setUser(usr->valuestring);
	messageToReturn.setPassword(psw->valuestring);
	messageToReturn.setInstance(kpId->valuestring);
	
	return messageToReturn;
}

