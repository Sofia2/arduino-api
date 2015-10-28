#ifndef SSAPBodyOperationMessage_h
#define SSAPBodyOperationMessage_h


class SSAPBodyOperationMessage{

private:
	//data
	char* data;
	
	//query
	char* query;

public:
	/*
	* data getter and setter
	*/
	char* getData();
	void setData(char* d);
	
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
		FromJSon method convert a json String to a SSAPBodyOperationMessage
	*/
	static SSAPBodyOperationMessage fromJSonToSSAPMessage(char* jsonString);
};
#endif // SSAPBodyOperationMessage_h