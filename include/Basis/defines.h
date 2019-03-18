#ifndef DEFINES_H
#define DEFINES_H

/*---------------------------------------------
  Basic Type Defines
   SHORT      -  meant to be 0 to 256
   INT        -  standard integer
   UNSIGNED   -  standard unsigned integer
   SYS_RETURN -  Standard return value for normal and errors
   INDEX      -  standard index value in vector objects
   LONG       -  longer (or the same as) the standard integer
   FLAG       -  a flag variable (a small integer)
-----------------------------------------------*/
//#define SHORT unsigned short
//#define INT int
//#define UNSIGNED unsigned int
//#define LONG long
#define SYS_RETURN short
#define INDEX unsigned int
#define FLAG unsigned int
#define COMPARE_RETURN unsigned int
//#define FLOAT double

//#define CHAR char
/*---------------------------------------------
 System Return Flags
-----------------------------------------------*/

#define SYSTEM_NORMAL_RETURN   0
#define SYSTEM_ERROR_RETURN    1
#define SYSTEM_FATAL_RETURN    2
#define FATAL                  1

/*---------------------------------------------
 Compare Return Flags
-----------------------------------------------*/
#define COMPARE_EQUAL  0
#define COMPARE_LESS_THAN  -1
#define COMPARE_GREATER_THAN  1
#define COMPARE_NOT_EQUAL 2
/*---------------------------------------------
 Debug Definitions
-----------------------------------------------*/
extern int DEBUGPRINT;
#define DEBUG0 0
#define DEBUG1 1
#define DEBUG2 2
#define DEBUG3 3

/*---------------------------------------------
 Some standard characters
-----------------------------------------------*/
#define ENDOFLINE  '\n'
#define BLANK ' '
#define ENDOFSTRING '\0'
#define LEFTBRACKET '['
#define RIGHTBRACKET ']'
#define COLON ':'
#define COMMA ','
#define DASH  '-'

#endif
