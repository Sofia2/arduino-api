#ifndef SSAPBodyUnsubscribeMessage_h
#define SSAPBodyUnsubscribeMessage_h


class SSAPBodyUnsubscribeMessage{

private:
	
	//idSuscripcion
	char* idSuscripcion;
	
public:
	/*
	* idSuscripcion getter and setter
	*/
	char* getIdSuscripcion();
	void setIdSuscripcion(char* id);
	
	
	/*
		toJson method convert this object to a json String
	*/
	char* toJson();
	
	/*
		FromJSon method convert a json String to a SSAPBodyUnsubscribeMessage
	*/
	static SSAPBodyUnsubscribeMessage fromJSonToSSAPMessage(char* jsonString);
};
#endif // SSAPBodyUnsubscribeMessage_h