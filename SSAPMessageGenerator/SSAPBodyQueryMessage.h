#ifndef SSAPBodyQueryMessage_h
#define SSAPBodyQueryMessage_h


class SSAPBodyQueryMessage{

private:
	//query
	char* query;

public:
	
	/*
	* query getter and setter
	*/
	char* getQuery();
	void setQuery(char* q);
	
	/*
		toJson method convert this object to a json String
	*/
	char* toJson();
	
	/*
		FromJSon method convert a json String to a SSAPBodyQueryMessage
	*/
	static SSAPBodyQueryMessage fromJSonToSSAPMessage(char* jsonString);
};
#endif // SSAPBodyQueryMessage_h