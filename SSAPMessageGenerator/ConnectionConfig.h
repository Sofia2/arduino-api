
#ifndef _CONNECTIONCONFIG_H_
#define _CONNECTIONCONFIG_H_
#include <Arduino.h>
#include <IPAddress.h>

class ConnectionConfig
{
public:

	//getter and setter for localMac
	byte* getLocalMac();
	void setLocalMac(byte* lMac);

	//getter and setter for localIp
	IPAddress* getLocalIp();
	void setLocalIp(IPAddress* lIp);

	//getter and setter for serverIp
	byte* getServerIp();
	void setServerIp(byte* sIp);

protected:

private:

	//MAC address for the Ethernet Shield connected to this Arduino
	byte* localMac;
	
	//Local IP to assign  this Arduino
	IPAddress* localIp;
	
	//IP for the MQTT server
	byte* serverIp;
	
};

#endif // _CONNECTIONCONFIG_H_
