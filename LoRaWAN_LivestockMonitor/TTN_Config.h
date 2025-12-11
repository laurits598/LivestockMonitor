/* 

Laurits M. Jensen - s194279 

*/

#pragma once


/* Keeping the TTN credentials here - makes it easy to change*/

/*
Add int identifier to the definition, i.e. "#define DEVICE_LAURITS 1", in order to apply conditional logic checks. 

*/
#define DEVICE_LAURITS 1    
#define DEVICE_VICTORIA 2 
#define DEVICE_X 3

//#define DEVICE DEVICE_LAURITS
#define DEVICE DEVICE_X
#if DEVICE == DEVICE_LAURITS
inline const char* devAddr = "260BD334";
inline const char* nwkSKey = "6BC0EA87D08472B1A82D0476C1F85D36";
inline const char* appSKey = "E057544428F0BB294C93A0E874EB2A13";
inline const char* appEui = "0000000000000000";
inline const char* appKey = "6B9511F01BA522A813AA85B462190564";

#elif DEVICE == DEVICE_VICTORIA
inline const char* devAddr = "02017201";
inline const char* nwkSKey = "AE17E567AECC8787F749A62F5541D522";
inline const char* appSKey = "8D7FFEF938589D95AAD928C2E2E7E48F";
inline const char* appEui = "0000000000000000";
inline const char* appKey = "6B9511F01BA522A813AA85B462190564";

#elif DEVICE == DEVICE_X
extern const char *devAddr = "";
extern const char *nwkSKey = "";
extern const char *appSKey = "";
// OTAA: initOTAA(String AppEUI, String AppKey);
extern const char *appEui = "";
extern const char *appKey = "";

#endif
/* Declaring the file normally (const char *X =) would conflict in terms of multi-declaration - every *.cpp file would declare its own
   Hence it would be declared in this header and now also the *.cpp file.
*/
/* The extern storage-class specifier declares a variable without defining it - hence we would have to define it in the *.cpp file */
/* The inline specifier allows multiple definitions, meaning no multi-declaration conflict*/

/*
IN CASE IT GOES SOUTH, the definitions can be found below
Remove the definitions above, or remove calls to this library, and insert the commands below in the RN2483.cpp file (with your own credentials).   

// Lau's RN2483 Device 
const char *devAddr = "260BD334";
const char *nwkSKey = "6BC0EA87D08472B1A82D0476C1F85D36";
const char *appSKey = "E057544428F0BB294C93A0E874EB2A13";
// OTAA: initOTAA(String AppEUI, String AppKey);
const char *appEui = "0000000000000000";
const char *appKey = "6B9511F01BA522A813AA85B462190564";

*/

