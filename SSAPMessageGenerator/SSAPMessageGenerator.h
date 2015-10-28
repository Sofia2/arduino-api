#ifndef _SSAPMESSAGEGENERATOR_H_
#define _SSAPMESSAGEGENERATOR_H_

#include "ssapmessage.h"

class SSAPMessageGenerator
{
public:

	SSAPMessage generateJoinMessage(char* usuario, char* password, char* instance);
	
	SSAPMessage generateJoinByTokenMessage(char* token, char* instance);
	
	SSAPMessage generateLeaveMessage(char* sessionKey);
	
	SSAPMessage generateInsertMessage(char* sessionKey, char* ontologia, char* datos) ;
	
	SSAPMessage generateUpdateMessage(char* sessionKey, char* ontologia, char* datos, char* query);
	
	SSAPMessage generateRemoveMessage(char* sessionKey, char* ontologia, char* query);
	
	SSAPMessage generateQueryMessage(char* sessionKey, char* ontologia, char* query);

	SSAPMessage generateSubscribeMessage(char* sessionKey, char* ontologia, int msRefresh, char* query);

	SSAPMessage generateUnsubscribeMessage(char* sessionKey, char* ontologia, char* idSuscripcion);
	

protected:

private:

};

#endif // _SSAPMESSAGEGENERATOR_H_
