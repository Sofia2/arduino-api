
#include "ConnectionConfig.h"
#include <Arduino.h>


#include "string.h"


/*
 	Getter for hostSIB
 */
byte* ConnectionConfig::getLocalMac(){
	return localMac;
}

/*
	Setter for hostSIB
 */
void ConnectionConfig::setLocalMac(byte* lMac){
	localMac=lMac;
}

/*
 	Getter for portSIB
 */
IPAddress* ConnectionConfig::getLocalIp(){
	return localIp;
}

/*
 	Setter for portSIB
 */
void ConnectionConfig::setLocalIp(IPAddress* lIp){
	localIp=lIp;
}

/*
 	Getter for timeoutConnectionSIB
 */
byte* ConnectionConfig::getServerIp(){
	return serverIp;
}

/*
 	Setter for timeoutConnectionSIB
 */
void ConnectionConfig::setServerIp(byte* sIp){
	serverIp=sIp;
}