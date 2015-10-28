

#ifndef _SIBCOMMANDMESSAGENOTIFICATIONS_H_
#define _SIBCOMMANDMESSAGENOTIFICATIONS_H_

#include "CommandMessageRequest.h"

class Listener4SIBCommandMessageNotifications
{
public:
	void onCommandMessage(CommandMessageRequest commandMessage);

protected:

private:

};

#endif // _SIBCOMMANDMESSAGENOTIFICATIONS_H_
