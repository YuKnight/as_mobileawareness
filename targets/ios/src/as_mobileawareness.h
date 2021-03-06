#ifndef _AS_MOBILEAWARENESS_H_
#define _AS_MOBILEAWARENESS_H_

// Copyright 2019 J Forristal LLC
// Copyright 2016 Addition Security Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <CoreFoundation/CoreFoundation.h>
#include <stdint.h>
#include <uuid/uuid.h>

/*
** Some macros usable from Objective-C:
**
*/

#define AS_CALLBACK(nom) void nom(const int msgid, const int msgsubid, const CFDataRef data1, const CFDataRef data2)

#define AS_UUID_DEFAULT_IDFV(varnom) \
	uuid_t varnom; \
	[[UIDevice currentDevice].identifierForVendor getUUIDBytes:varnom];





#if __cplusplus
extern "C" {
#endif


/*
** Main initialization function(s) and their return codes
**
*/
int AS_Initialize( const uuid_t deviceid, void (*callback)(int,int,CFDataRef,CFDataRef) );
int AS_Initialize_Direct( const uuid_t deviceid, 
	const uint8_t *config, uint32_t config_len,
        const uint8_t *defs, uint32_t defs_len, 
	void(*callback)(int,int,uint8_t*,uint32_t,uint8_t*,uint32_t) );
#define AS_INIT_SUCCESS		0
#define AS_INIT_ERR_GENERAL	-1
#define AS_INIT_ERR_LICENSE	-2
#define AS_INIT_ERR_INTEGRITY	-3
#define AS_INIT_ERR_OLDCONFIG	-5
#define AS_INIT_ERR_ALREADYINIT	-6


int AS_Register_Identity( const char *identity );
int AS_Send_Message( uint32_t id, const char *data );
int AS_Device_Identity(uuid_t uuid);
#define AS_SUCCESS		0
#define AS_ERR_GENERAL		-1


long AS_Heartbeat( long input );
void AS_Login_Status( int status );
void AS_Network_Reachability();
uint32_t AS_Version();

uint32_t AS_Security_Posture();
#define AS_SECURITY_INITCOMPLETED(v)	(v & 0x0001)
#define AS_SECURITY_JAILBROKEN(v)	(v & 0x0004)
#define AS_SECURITY_HACKINGTOOL(v)	(v & 0x0020)
#define AS_SECURITY_SECURITYVIOLATION(v) (v & 0x0080)
#define AS_SECURITY_DEBUGGER(v)		(v & 0x0100)
#define AS_SECURITY_TAMPERING(v)	(v & 0x0200)
#define AS_SECURITY_NETWORK(v)		(v & 0x0400)
#define AS_SECURITY_MALWARE(v)		(v & 0x0800)
#define AS_SECURITY_GAMECHEATTOOL(v)	(v & 0x1000)
#define AS_SECURITY_DEVBUILD(v)		(v & 0x2000)


#if __cplusplus
}
#endif

#endif
