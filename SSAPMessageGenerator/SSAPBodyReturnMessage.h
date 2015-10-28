#ifndef SSAPBodyReturnMessage_h
#define SSAPBodyReturnMessage_h


class SSAPBodyReturnMessage{

private:
	//data
	char* data;
	
	//ok
	bool ok;
	
	//error
	char* error;

public:
	//~SSAPBodyReturnMessage();
	/*
	* data getter and setter
	*/
	char* getData();
	void setData(char* d);
	
	/*
	* Ok getter and setter
	*/
	bool isOk();
	void setOk(bool o);
	
	/*
	* error getter and setter
	*/
	char* getError();
	void setError(char* e);
	
	/*
		toJson method convert this object to a json String
	*/
	char* toJson();
	
	/*
		FromJSon method convert a json String to a SSAPBodyReturnMessage
	*/
	static SSAPBodyReturnMessage fromJSonToSSAPMessage(char* jsonString);
};
#endif // SSAPBodyReturnMessage_h