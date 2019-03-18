/*  FILE     String.cc
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
*/
#include <iostream>
using namespace std;
#include "CommBuffer.hh"
#include "String.hh"

/*S Basic input and output routines
*/
/*
bool operator==(const String& s1, const String& s2)
{
  return s1.operator==(s2);
  //return (strcmp(s1.c_str(),s2.c_str()) == 0);
}
*/
/*F SkipCommentLines(in)  . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    in: param.
**    Routine SkipCommentLines(in) reads in a single string. If string 
**    is preceded by comment sign, it is ignored and input proceeds.
**
**  REMARKS
**      A comment line begins with '%'.
**
*/
SYS_RETURN String::SkipCommentLines(istream& in)
{
  erase((*this).begin(),(*this).end());
  SYS_RETURN ret = SYSTEM_NORMAL_RETURN;
  if(getline(in,*this,'\n'))
    {
      if(!in.eof())
	{
	  while((*this)[0] == '%')
	      getline(in,*this,'\n');
	}
      else
	ret = SYSTEM_ERROR_RETURN;
      push_back('\0');
    }
  else
    {
      push_back('\0');
      ret = SYSTEM_ERROR_RETURN;
    }
  return(ret);
}
/*F ReadFullLine(in)  . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    in: param.
**    Routine ReadFullLine(in) reads in a full line. If the last printed
**    character in the line is '\' ('backslash'), the next line is read in.
**    Comment lines are skipped.
**
**  REMARKS
**      A comment line begins with '%'.
**      Continued line ends with '\'.
**
*/
SYS_RETURN String::ReadFullLine(istream& in)
{
  String buffer;
  SYS_RETURN ret = SYSTEM_NORMAL_RETURN;
  erase((*this).begin(),(*this).end());
  push_back('\0');
  bool notdone = true;
  while(notdone) {
    ret = buffer.SkipCommentLines(in);
    if(ret == SYSTEM_NORMAL_RETURN) {
      if (buffer.size()>1) {
	int top = buffer.size();
	if(buffer[top-1]=='\\') {
	  String str = buffer.Isolate(0,top-2);
	  AppendToEnd(str);
	} else {
	  notdone = false;
	}
      }
    } else {
      notdone = false;
    }
  }
  (*this).AppendToEnd(buffer);
   return ret;
}
/*S String transformation and manilulation routines
*/
/*F EliminateLeadingBlanks()  . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    Removes leading blanks from string.
**
**  REMARKS
**
*/
SYS_RETURN String::EliminateLeadingBlanks()
{
  while((*this)[0] == ' ' || (*this)[0] == '\t')
    erase(begin());
  return(SYSTEM_NORMAL_RETURN);
}
/*F EliminateBlanks() . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    Removes blanks from string.
**
**  REMARKS
**
*/
SYS_RETURN String::EliminateBlanks()
{
  iterator i;
  i = remove(begin(),end(),' ');
  erase(i,end());
  i = remove(begin(),end(),'\t');
  erase(i,end());
  i = remove(begin(),end(),'\r');
  erase(i,end());
  return(SYSTEM_NORMAL_RETURN);
} 
/*F AppendToEnd(buffer) . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    buffer: param.
**    Appends buffer to the end of string. Blank charactes at the 
**    end of string are deleted. Syntax: String string1;
**    string1.AppendToEnd(buffer). 
**
**  REMARKS
**
*/
SYS_RETURN String::AppendToEnd(const String& buffer)
{
  erase(end()-1);
  append(buffer);
  return(SYSTEM_NORMAL_RETURN);
}

 
/*F IsolateNextWord(buffer,delim) . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    buffer: param.
**    delim: param.
**    Routine IsolateNextWord(buffer,delim) isolates first word within
**    string 'buffer', separated from the rest of string by delimiter 'delim'.
**
**  REMARKS
**
*/
SYS_RETURN String::IsolateNextWord(String& buffer, int delim)
{
  SYS_RETURN ret = SYSTEM_NORMAL_RETURN;
  buffer.erase(buffer.begin(),buffer.end());
  if(size() > 0) {
    unsigned int ptr1 = find(delim,0);
    if(ptr1 >= size()) {// i.e. delim not found
      buffer = ((*this).substr(0,ptr1)).c_str();
      erase(begin(),end());
      push_back('\0');
    } else {
      buffer = ((*this).substr(0,ptr1)).c_str();
      erase(begin(),begin()+ptr1+1);
    }  
  } else {
    buffer.push_back('\0');
  }
    ret = SYSTEM_ERROR_RETURN;
  return(ret);
}
 
/*  Isolate(left_margin, right_margin)  . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    left_margin: param.
**    right_margin: param.
**    Routine Isolate(left_margin,right_margin) isolates part of string within
**    'left_margin' and 'right_margin'.  
**    
**  REMARKS
**
*/
String String::Isolate(INDEX left_margin, INDEX right_margin)
{
  String *buf;
  //if(right_margin >= left_margin && left_margin >= 0 && right_margin < this->size()-1) {
  if(right_margin >= left_margin && right_margin < this->size()-1) {
    string b(right_margin-left_margin+1,' ');
    buf = new String(b.c_str());
    std::copy(begin()+left_margin,begin()+right_margin+1,buf->begin());
    } else {
      buf = new String("");
      cerr << "Isolate: illegal boundaries\n";
    }
  return *buf;
}
/*S EncodeDecode
 */
 
/*F ans = Encode(buffer,string) . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
**    buffer: The buffer
**    string: The string 
**    ans: True if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, String& string)
{
  return string.EncodeThis(buffer);
}

/*F ans = Decode(buffer,string) . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
**    buffer: The buffer
**    string: The string 
**    ans: True if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, String& string)
{
  return string.DecodeThis(buffer);
}

/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool String::EncodeThis(CommBuffer& buffer)
{
  if(size() != 0)
    {
      unsigned int size = (*this).size();
      char *copych = (char *) malloc(size);
      memcpy(copych,c_str(),size);
      return Encode(buffer,(char**)&copych);
    }
  else
    {
      char *copych = (char *) malloc(1);
      *copych = '\0';
      return Encode(buffer,(char**)&copych);
    }	  
}
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: True if successful
**
**  REMARKS
**
*/
bool String::DecodeThis(CommBuffer& buffer)
{
  char* ch;
  bool ans = Decode(buffer,&ch);
  if(ans)
    (*this) = ch;
  return ans;
}


/*F Float2String(num)  . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION  
**    num	double number that should be converted to String.
**    
**  REMARKS
**
*/
String Float2String(double num)
{
  //int siz = 100;
  //char* ch = new char[siz];
  //ostrstream ostrstr(ch, siz);
  stringstream ostrstr;
  ostrstr << num << '\0';

  return ostrstr.str().c_str();
}

/*F Int2String(num)  . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION  
**    num	int number that should be converted to String.
**    
**  REMARKS
**
*/
String Int2String(int num)
{
  //int siz = 100;
  //char* ch = new char[siz];
  //ostrstream ostrstr(ch, siz);
  stringstream ostrstr;

  ostrstr << num << '\0';
  //String str(ch);
  String str(ostrstr.str().c_str());
  //delete ch;
  return str;
}

/*IO out1 = operator<<(out,str)  . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
**    out,out1: The output stream
**    str: The class to be outputted
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const String& str)
{
  return str.print(out);
}
/*F str = PositveIntegerToString(c,prefix,places) . . . . .  filled in string
**
**  DESCRIPTION
**    c: The positive integer to convert
**    prefix: The prefix on the string
**    places: The number of place holders the string should have
**    str: The generated string
**   
**    This routine is mainly used to create names such that the order of the
**    names coincides with the numerical order.
**
**  REMARKS
**
*/
String PositveIntegerToString(unsigned int c, const String& prefix, unsigned int places)
{
  String str(prefix);
  String num = Int2String(c);
  String fill("0");
  unsigned int max = 1;
  for(unsigned int i=1; i != places;i++)
    {
      max = max *10;
    }
  // if(c >= max || c < 0)
  if(c >= max) {
      cerr << "PositveIntegerToString: places exceeded" << endl;
    } else {
      while(max > c) {
	    str.AppendToEnd(fill);
	      max = max / 10;
	}
    }
  str.AppendToEnd(num);
  
  return str;
}
/*F str = FillStringToLength(length,original) 
**
**  DESCRIPTION
**    length: The length of the output string
**    original: The original string
**    str: The output string
**  REMARKS
**
*/
String& FillStringToLength(const unsigned int length, const String& original)
{
  String *cpy = new String(original);
  int ss = length-original.size()+1;
  if(ss > 0) {
  string b((unsigned int) ss,' ');
  String b1(b.c_str());
  cpy->AppendToEnd(b1);
  }
  return *cpy;
}
/*f out = RepeatOutNTimes(out,c,n)  . . . . . . . . . . .  repeat a character
**
**  DESCRIPTION
**    out: The output stream
**    c: The character
**    n: The number of times to repeat
**
**  REMARKS
**
*/
extern ostream& RepeatOutNTimes(ostream& out, char c, int n)
{
  for(int i=0;i != n;i++)
    out << c;
  return out;
}
/*f out = OutputStringInWidth(out,w,str)  . . . . . . . . . . . output string
**
**  DESCRIPTION
**    out: The output stream
**    w: The width allowed
**    str: The string to output
**
**  REMARKS
**
*/
ostream& OutputStringInWidth(ostream& out,
				    const unsigned int w,
				    const String& str)
{
  if(w >= str.size()){
  unsigned int len = strlen(str.c_str());
  unsigned int r = (w-len)/2;
  unsigned int rest = w - (r*2 + len);
  
  RepeatOutNTimes(out,' ',r);
  out <<  str;
  RepeatOutNTimes(out,' ',r+rest);
  } else {
    out << str;
  }
  return out;
}
