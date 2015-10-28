
#ifndef _SSAPMESSAGE_H_
#define _SSAPMESSAGE_H_



enum SSAPMessageTypes { JOIN=1, LEAVE=2, INSERT=3, UPDATE=4, DELETE=5, QUERY=6, SUBSCRIBE=7, UNSUBSCRIBE=8, INDICATION=9};
enum SSAPMessageDirection { REQUEST=1, RESPONSE=2, ERROR=3 };
enum SSAPPersistenceType {MONGODB=1, INMEMORY=2};

class SSAPMessage
{

private:

	/*
	 * Unique identifier for a request
	 */
	char* messageId;
	
	/*
	 * Identifier for the session with a SIB
	 */
	char* sessionKey;
	
	/*
	 * Identifier of the ontology that the message references
	 */
	char* ontology;

	/*
	 * Direction of the  message
	 */
	SSAPMessageDirection direction;
	
	/*
	 * Type of message
	 */
	SSAPMessageTypes messageType;

	/*
	 * Type of persistence
	 */
	SSAPPersistenceType persistenceType;
	
	/*
	 * Body for the message
	 */
	char* body;


	
public:
	
	//~SSAPMessage();
	
	
	/* 
	 	MessageId getter and setter
	 */
	char* getMessageId();
	void setMessageId(char* mId);


	/*
	 	SessionKey getter and setter
	 */
	char* getSessionKey();
	void setSessionKey(char* sKey);
	
	/*
	 	ontology getter and setter
	 */
	char* getOntology();
	void setOntology(char* ont);


	/*
	 	direction getter and setter
	 */
	SSAPMessageDirection getDirection();
	void setDirection(SSAPMessageDirection dir);
	

	/*
	 	messageType getter and setter
	 */
	SSAPMessageTypes getMessageType();
	void setMessageType(SSAPMessageTypes mType);


	/*
	 	persistenceType getter and setter
	 */
	SSAPPersistenceType getPersistenceType();
	void setPersistenceType(SSAPPersistenceType pType);

	/*
	 	body getter and setter
	 */
	char* getBody();
	void setBody(char* body);
	
	/*
		toJson method convert this object to a json String
	*/
	char* toJson();
	
	/*
		FromJSon method convert a json String to a SSAPMessage
	*/
	static SSAPMessage fromJSonToSSAPMessage(char* jsonString);

protected:


};

#endif // _SSAPMESSAGE_H_
