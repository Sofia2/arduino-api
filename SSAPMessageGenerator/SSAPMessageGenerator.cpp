
#include "SSAPMessageGenerator.h"
#include "aJSON.h"
#include "string.h"


SSAPMessage SSAPMessageGenerator::generateJoinMessage(char* user, char* password, char* instance){
	SSAPMessage joinMessage=SSAPMessage();
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body,"user", user);
	aJson.addStringToObject(body, "password", password);	
	aJson.addStringToObject(body, "instance", instance);

	char* bodyJson=aJson.print(body);
	
	char* bodyCopy=new char[strlen(bodyJson)+1];
	strcpy(bodyCopy, bodyJson);
	
	delete[] bodyJson;
	aJson.deleteItem(body);
	
	joinMessage.setBody(bodyCopy);
	joinMessage.setDirection(REQUEST);
	joinMessage.setMessageType(JOIN);

	
	return joinMessage;
}

SSAPMessage SSAPMessageGenerator::generateJoinByTokenMessage(char* token, char* instance){
	SSAPMessage joinMessage=SSAPMessage();
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body,"token", token);
	aJson.addStringToObject(body, "instance", instance);

	char* bodyJson=aJson.print(body);
	
	char* bodyCopy=new char[strlen(bodyJson)+1];
	strcpy(bodyCopy, bodyJson);
	
	delete[] bodyJson;
	aJson.deleteItem(body);
	
	joinMessage.setBody(bodyCopy);
	joinMessage.setDirection(REQUEST);
	joinMessage.setMessageType(JOIN);

	
	return joinMessage;
}

SSAPMessage SSAPMessageGenerator::generateLeaveMessage(char* sessionKey){
	SSAPMessage leaveMessage=SSAPMessage();

	leaveMessage.setSessionKey(sessionKey);
	leaveMessage.setDirection(REQUEST);
	leaveMessage.setMessageType(LEAVE);

	return leaveMessage;
}

SSAPMessage SSAPMessageGenerator::generateInsertMessage(char* sessionKey, char* ont, char* dat) {
	
	SSAPMessage insertMessage=SSAPMessage();
	

	char* sKey=new char[strlen(sessionKey)+1];
	
	strcpy(sKey, sessionKey);
	
	insertMessage.setSessionKey(sKey);
	
	
	char* datos=new char[strlen(dat)+1];
	strcpy(datos, dat);
	
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body, "data", datos);
	aJson.addStringToObject(body, "query", "");
	
	
	char* bodyJson=aJson.print(body);
	
	char* bodyCopy=new char[strlen(bodyJson)+1];
	strcpy(bodyCopy, bodyJson);
	
	delete[] bodyJson;
	
	
	delete[] datos;
	aJson.deleteItem(body);
	
	
	insertMessage.setBody(bodyCopy);
	
	
	insertMessage.setDirection(REQUEST);
	insertMessage.setMessageType(INSERT);
	
	char* ontologia=new char[strlen(ont)+1];
	strcpy(ontologia, ont);
	insertMessage.setOntology(ontologia);
	
	return insertMessage;
}

SSAPMessage SSAPMessageGenerator::generateUpdateMessage(char* sessionKey, char* ont, char* dat, char* quer){
	SSAPMessage updateMessage=SSAPMessage();

	updateMessage.setSessionKey(sessionKey);
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body, "data", dat);
	aJson.addStringToObject(body, "query", quer);
	
	updateMessage.setBody(aJson.print(body));
	
	updateMessage.setDirection(REQUEST);
	updateMessage.setMessageType(UPDATE);
	updateMessage.setOntology(ont);

	return updateMessage;
}

SSAPMessage SSAPMessageGenerator::generateRemoveMessage(char* sessionKey, char* ont, char* quer){
	SSAPMessage removeMessage=SSAPMessage();

	removeMessage.setSessionKey(sessionKey);
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body, "data", "");
	aJson.addStringToObject(body, "query", quer);

	removeMessage.setBody(aJson.print(body));
	
	removeMessage.setDirection(REQUEST);
	removeMessage.setMessageType(UPDATE);
	removeMessage.setOntology(ont);
	
	return removeMessage;
}

SSAPMessage SSAPMessageGenerator::generateQueryMessage(char* sessionKey, char* ont, char* quer){
	SSAPMessage queryMessage=SSAPMessage();
	
	queryMessage.setSessionKey(sessionKey);
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body, "data", "");
	aJson.addStringToObject(body, "query", quer);
	
	
	queryMessage.setBody(aJson.print(body));

	queryMessage.setDirection(REQUEST);
	queryMessage.setMessageType(QUERY);
	queryMessage.setOntology(ont);
	
	return queryMessage;
}

SSAPMessage SSAPMessageGenerator::generateSubscribeMessage(char* sessionKey, char* ont, int msRefresh, char* quer){
	SSAPMessage subscribeMessage=SSAPMessage();

	subscribeMessage.setSessionKey(sessionKey);
	
	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body, "query", quer);
	aJson.addNumberToObject(body, "msRefresh", msRefresh);
	
	
	subscribeMessage.setBody(aJson.print(body));
	subscribeMessage.setDirection(REQUEST);
	subscribeMessage.setMessageType(SUBSCRIBE);
	subscribeMessage.setOntology(ont);
	
	return subscribeMessage;
}

SSAPMessage SSAPMessageGenerator::generateUnsubscribeMessage(char* sessionKey, char* ont, char* idSuscripcion){
	SSAPMessage unsubscribeMessage=SSAPMessage();

	unsubscribeMessage.setSessionKey(sessionKey);

	aJsonObject *body;
	body=aJson.createObject();
	aJson.addStringToObject(body, "idSuscripcion", idSuscripcion);
	

	unsubscribeMessage.setBody(aJson.print(body));
	
	unsubscribeMessage.setDirection(REQUEST);
	unsubscribeMessage.setMessageType(UNSUBSCRIBE);
	unsubscribeMessage.setOntology(ont);
	
	return unsubscribeMessage;
}
