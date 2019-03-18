/*  FILE     NonStandard.hh
**  PACKAGE  NonStandard
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Prototypes for the "NonStandard" package in the CoreObjects environment
**
**  COPYRIGHT (C) 1997 Edward S. Blurock
*/
 
#ifndef CoreObjects_NONSTANDARD_HH
#define CoreObjects_NONSTANDARD_HH

/*I  . . . INCLUDES . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
#include "NonStandardType.hh"

extern String DefaultEndDelimitor;
extern String NoStructure;

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
*/
bool XMLReadBool(istream& in, bool *b);
bool ReadBool(istream& in, bool *b);
bool XMLWriteBool(ostream& out,bool b);
bool WriteBool(ostream& out,bool b);

bool XMLReadSimple(istream& in, int *b);
bool ReadSimple(istream& in, int *b);
bool XMLWriteSimple(ostream& out,int b);
bool WriteSimple(ostream& out,int b);

bool XMLReadSimple(istream& in, unsigned int *b);
bool ReadSimple(istream& in, unsigned int *b);
bool XMLWriteSimple(ostream& out,unsigned int b);
bool WriteSimple(ostream& out,unsigned int b);




#endif
