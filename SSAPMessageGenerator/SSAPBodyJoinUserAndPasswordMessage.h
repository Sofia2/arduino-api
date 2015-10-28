#ifndef SSAPBodyJoinUserAndPasswordMessage_h
#define SSAPBodyJoinUserAndPasswordMessage_h


class SSAPBodyJoinUserAndPasswordMessage{

private:
	//username
	char* user;
	
	//password
	char* password;
	
	//kp identifier
	char* instance;

public:
	/*
	* user getter and setter
	*/
	char* getUser();
	void setUser(char* u);
	
	/*
	* password getter and setter
	*/
	char* getPassword();
	void setPassword(char* p);
	
	/**
	* instance getter and setter
	*/
	char* getInstance();
	void setInstance(char* i);
	
	/*
		toJson method convert this object to a json String
	*/
	char* toJson();
	
	/*
		FromJSon method convert a json String to a SSAPBodyJoinUserAndPasswordMessage
	*/
	static SSAPBodyJoinUserAndPasswordMessage fromJSonToSSAPMessage(char* jsonString);
};
#endif // SSAPBodyJoinUserAndPasswordMessage_h