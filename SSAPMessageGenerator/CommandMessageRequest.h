
#ifndef _COMMANDMESSAGEREQUEST_H_
#define _COMMANDMESSAGEREQUEST_H_

enum CommandType { DEVICE_STATUS=1, BATERY_STATUS=2};

class CommandMessageRequest
{
public:

	//MessageId getter and setter
	char* getMessageId ();
	void setMessageId (char* mId);

	//CommandType getter and setter
	CommandType getCommandType();
	void setCommandType(CommandType cType);

	//CommandMessage getter and setter
	char* getCommandMessage();
	void setCommandMessage(char* cMessage);

	//Converts this object to a JSon String
	char* toJson();
	

protected:

private:
	//MessageId
	char* messageId;

	//CommandType
	CommandType commandType;

	//CommandMessage
	char* commandMessage;

};

#endif // _COMMANDMESSAGEREQUEST_H_
