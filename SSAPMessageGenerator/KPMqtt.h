
#ifndef _KPMQTT_H_
#define _KPMQTT_H_

#include "../PubSubClient/PubSubClient.h"
#include "ConnectionConfig.h"
#include "SSAPMessage.h"
#include "Listener4SIBIndicationNotifications.h"
#include "Listener4SIBCommandMessageNotifications.h"


class KPMqtt:public CallbackListener
{
public:
	
	/**
	* clientId setter
	*/
	void setClientId(char* cId);
	
	/**
	* clientId getter
	*/
	char* getClientId();

	/**
	 *Returs if the KP is currently connected to a SIB
	 */
	bool isConnected();
	
	/**
	 * Returns the SessionKey for the current connection with the SIB
	 * Returns null if not connected to a SIB
	 */
	char* getSessionKey();
	
	/**
	 * Connect this KP to a SIB (Sends a JOIN message)
	 */
	void connect();
	
	/**
	 * Makes a disconnect for the physical protocol
	 */
	void disconnect();
	

	/**
	 * Configuration parameters for the connection
	 */
	void setConnectionConfig(ConnectionConfig* config);
	
	/**
	 * Sends to the SIB a SSAP message
	 * @return
	 */
	SSAPMessage send(SSAPMessage* msg);
	
	/**
	*Sends to the SIB a SSAP message encryted using XXTea Algorithm
	*/
	SSAPMessage sendEncrypt(char* msgJson, unsigned char* key, int keyLength);
		
	/**
	 * Registers a  listener to listen notifications for subscriptions.
	 * @param listener
	 */
	void addListener4SIBNotifications(Listener4SIBIndicationNotifications listener);

	/**
	 * Unregister a  listener to listen notifications for subscriptions.
	 * @param listener
	 */
	 void removeListener4SIBNotifications(Listener4SIBIndicationNotifications listener);
	 
		
	/**
	 * Register a listener to recevice command messages from SIB
	 * @param listener
	 */
	void addListener4SIBCommandMessageNotifications(Listener4SIBCommandMessageNotifications listener);

	/**
	 * Unregister a listener to recevice command messages from SIB
	 * @param listener
	 */
	void removeListener4SIBCommandMessageNotifications(Listener4SIBCommandMessageNotifications listener);
	
	/**
	* Launches a loop to receive SIB notifications
	*/
	void loopMqtt();

	/**
	* Callback to receive SIB notifications
	*/
	void callback( char* topic, byte* payload, unsigned int length );
	
	
	int memoryTest();
protected:

private:
	char* clientId;
	char* sessionKey;
	bool connected;
	ConnectionConfig* connectionConfig;
	
	char* topicPublishForThisClient;
	char* topicIndicationForThisClient;
	char* topicCommandForThisClient;
	
	char* publishResponse;
	
	PubSubClient client;
	

};

#endif // _KPMQTT_H_
