/*  FILE     CommBuffer.hh
**  PACKAGE  CommBuffer
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Definitions for the "CommBuffer" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
**
**
**
*/
#ifndef REACTION_COMMBUFFER_HH
#define REACTION_COMMBUFFER_HH
 
#define COMMBUFF_DEFAULT_BUFFER_SIZE 5000
#define COMM_DIRECTION_TYPE unsigned int
#define COMM_BUFF_ENCODE XDR_ENCODE
#define COMM_BUFF_DECODE XDR_DECODE
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include <iostream>
using namespace std;

#ifdef _msdos_stl
#include <fstream>
#include <string>
#pragma warning(disable:4786)

#endif



#ifdef _unix
#include <fstream>
#include "STL.h"
#endif


#include <stdlib.h>
#include "defines.hh" 


#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#ifdef _noxdr
#define XDR_ENCODE 1
#define XDR_DECODE 0
typedef struct xdr_struct {
	char *Buffer;
	unsigned int BufferUsed;
	unsigned int BufferLeft;
	COMM_DIRECTION_TYPE Direction;
} XDR;
#else
#include <sys/socket.h>
#include "rpc/rpc.h"
#endif
#ifdef __cplusplus
}
#endif
 
#include "CommBufferType.hh" 


 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
extern bool Pack(CommBuffer& buffer, char** string);
extern bool Pack(CommBuffer& buffer, char** string, unsigned int length);
extern bool Unpack(CommBuffer& buffer, char** string);
extern bool Pack(CommBuffer& buffer, int i);
extern bool Unpack(CommBuffer& buffer, int& i);
extern bool Pack(CommBuffer& buffer, unsigned int i);
extern bool Unpack(CommBuffer& buffer, unsigned int& i);
extern bool Pack(CommBuffer& buffer, short i);
extern bool Unpack(CommBuffer& buffer, short& i);
extern bool Pack(CommBuffer& buffer, float i);
extern bool Unpack(CommBuffer& buffer, float& i);
extern bool Pack(CommBuffer& buffer, double i);
extern bool Unpack(CommBuffer& buffer, double& i);
	  
extern bool Encode(CommBuffer& buffer, char** string);
extern bool Decode(CommBuffer& buffer, char** string);
extern bool Encode(CommBuffer& buffer, int i);
extern bool Decode(CommBuffer& buffer, int &i);
extern bool Encode(CommBuffer& buffer, unsigned int i);
extern bool Decode(CommBuffer& buffer, unsigned int &i);
extern bool Encode(CommBuffer& buffer, short i);
extern bool Decode(CommBuffer& buffer, short &i);
extern bool Encode(CommBuffer& buffer, float i);
extern bool Decode(CommBuffer& buffer, float &i);
extern bool Encode(CommBuffer& buffer, double i);
extern bool Decode(CommBuffer& buffer, double &i);
void xdrmem_create(XDR *xdrs,char * addr_Buffer,unsigned int  size,unsigned int  op);

bool XMLReadBegin(std::istream& in,char *key); 
bool XMLReadEnd(std::istream& in,char *key); 
bool XMLWriteBegin(std::ostream& in,const char *key); 
bool XMLWriteEnd(std::ostream& in,const char *key); 

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CommBuffer.icc"
#endif

