#ifndef SSAPBodySubscribeMessage_h
#define SSAPBodySubscribeMessage_h


class SSAPBodySubscribeMessage{

private:
	//msRefresh
	int msRefresh;
	
	//query
	char* query;
	
public:
	/*
	* msRefresh getter and setter
	*/
	int getMsRefresh();
	void setMsRefresh(int refr);
	
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
		FromJSon method convert a json String to a SSAPBodySubscribeMessage
	*/
	static SSAPBodySubscribeMessage fromJSonToSSAPMessage(char* jsonString);
};
#endif // SSAPBodySubscribeMessage_h