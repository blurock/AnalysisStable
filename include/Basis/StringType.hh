/*  FILE     StringType.hh
**  PACKAGE  String
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "String" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef STURM_STRINGTYPE_HH
#define STURM_STRINGTYPE_HH

/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include <string>
/*C String  . . . . . . . . . . . . . . . . . .  String related operations.  
**
**  DESCRIPTION
**    Class string includes routines, which perform frequenly used string
**    operations.
**
**  REMARKS
**
*/
class String : public string
{
public:
  // Constructors
 
  String();
  String(const int s);
  String(const String& str);
  String(const char * str);
  
  // Destructor
       virtual ~String(void);

  // Strings compare

  inline bool operator<(const String& string);
  inline bool operator==(const String& str) const;
  inline bool operator==(const string& str) const;
  inline bool operator==(const char *str) const;
  
  // Output
  virtual ostream& print(ostream& out) const
  {
    if(size() > 0) {
      for(String::const_iterator c=begin();c!=end()-1;c++)
	out << *c;
    }
    return out;
  }
  
  // Basic input and output routines
  SYS_RETURN SkipCommentLines(istream& in);
  SYS_RETURN ReadFullLine(istream& in);
  //virtual istream& operator<<(ostream& out) { return string::operator<<(out) }
     
  // String transformation and manipulation routines
   
  SYS_RETURN EliminateBlanks();
  SYS_RETURN EliminateLeadingBlanks();
  SYS_RETURN AppendToEnd(const String& buffer);
  SYS_RETURN IsolateNextWord(String& buffer, int delim);     
  String Isolate(INDEX left_margin, INDEX right_margin);
  //  Conversion routines     
  inline int ToInteger();
  inline int ToInteger(INDEX left_margin, INDEX right_margin);
  inline double ToFloat();
  inline double ToFloat(INDEX left_margin, INDEX right_margin);  
  bool EncodeThis(CommBuffer& buffer);
  bool DecodeThis(CommBuffer& buffer);
  inline bool IsEmpty();
  bool XMLRead(istream& in);
  bool XMLWrite(ostream& out);
};
//ostream& operator<<(ostream& out, const String& str) { out << str.data(); return out; }
#endif
