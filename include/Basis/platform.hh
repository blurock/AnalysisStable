/*  FILE     platform.hh
**  PACKAGE  System
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Platform specific definitions
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
#ifndef PLATFORM_HH
#define PLATFORM_HH
#ifdef _msdos
#define STD_NAMESPACE std::
#else
#define STD_NAMESPACE
#endif

#endif
