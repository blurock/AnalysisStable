#ifdef _unix
#include "Basis/STL.h"
#include "iostream.h"
#include "fstream.h"
#endif
#include "stdlib.h"
#include "defines.hh"
#include "CommBuffer.hh"
#include <string>
#include "String.hh"

void manipulations();
void numbers();
void constructors();
void infromfile(char *);

int main(int argc, char *argv[]) {

  //constructors();
  //manipulations();
  //numbers();
  infromfile(argv[1]);
}

void infromfile(char *fn) {
   ifstream myin1(fn); 
   cout << "Read with 'SkipCommentLines'  from '" << fn << "'" << endl;
   if(myin1 != NULL) {
   String line;
   line.SkipCommentLines(myin1);
   cout << "Line 1: line.size()= " << line.size() << endl;
   cout << "'" << line << "'" << endl;
   line.SkipCommentLines(myin1);
   cout << "Line 2: line.size()= " << line.size() << endl;
   cout << "'" << line << "'" << endl;
   line.SkipCommentLines(myin1);
   cout << "Line 3: line.size()= " << line.size() << endl;
   cout << "'" << line << "'" << endl;
   myin1.close();

   ifstream myin1(fn); 
   cout << "Read with 'ReadFullLine'  from '" << fn << "'" << endl;
   String line1;
   line1.ReadFullLine(myin1);
   cout << "Line 1: line1.size()= " << line1.size() << endl;
   cout << "'" << line1 << "'" << endl;
   line1.ReadFullLine(myin1);
   cout << "Line 2: line1.size()= " << line1.size() << endl;
   cout << "'" << line1 << "'" << endl;
   line1.ReadFullLine(myin1);
   cout << "Line 3: line1.size()= " << line1.size() << endl;
   cout << "'" << line1 << "'" << endl;
   myin1.close();

   } else {
     cout << "could not find file" << endl;
   }
}
   

void numbers() {
  double d = 123.456;
  String num1 = Float2String(d);
  cout << "Float2String(" << d << ") = '" << num1 << "' size()= " << num1.size() << endl;
  int i = 123456;
  String num2 = Int2String(i);
  cout << "Int2String(" << i << ") = '" << num2 << "' size()= " << num2.size()  << endl;
  cout << "PositiveIntegerToString: " << i << endl;
  for(unsigned int p=1;p<10;p++) {
    String numa = PositveIntegerToString(i,"X",p);
    cout << p << " places: '" << numa << "' size()= " << numa.size() << endl;
  }
  
}
void constructors() {
    String emp;
    cout << "Empty: '" << emp << "' size() = " << emp.size() << endl;
    String emp1(emp);
    cout << "Copy of Empty: '" << emp1 << "' size() = " << emp1.size() << endl;
    String fromquote("123456789");
    cout << "From Quote: '" << fromquote << "' size() = " << fromquote.size() << endl;
    String cfromquote("123456789");
    cout << "Copy From Quote: '" << cfromquote << "' size() = " << cfromquote.size() << endl;
    
    unsigned int s=2;
    string s1(s,' ');
    String s2(s1.data());
    cout << "'" << s2 << "'" << endl;
}
  void manipulations() {
  String name("    Strin gX Name    ");
  cout << "Original String:        '" << name << "' size() = " << name.size() << endl;
  name.EliminateLeadingBlanks();
  cout << "Without Leading Blanks: '" << name << "'' size() = " << name.size() << endl;
  name.EliminateBlanks();
  cout << "With no Blanks: '" << name << "'' size() = " << name.size() << endl;

  cout << "Appending '2' to the end of '1' and looking at the characters:" << endl;
  String a("1"),b("2");
  a.AppendToEnd(b);
  for(int i=0;i<3;i++)
    cout << i << ": " << a[i] <<endl;

  String name2("X AnotherString");
  name.AppendToEnd(name2);
  cout << "Append '" << name2 << "' : '" << name << "' sizes= =" << name2.size() << ", " << name.size() << endl;
  String word1,word2,word3,word4;
  String nameagain(name);
  cout << "name = '" << name << "' size=" << name.size() << endl;
  cout << "Words separated by 'X'" << endl;
  name.IsolateNextWord(word1,'X');
  cout << "1: '" << word1 << "','" << name << "' word,name size=" << word1.size() << " " << name.size() << endl;
  name.IsolateNextWord(word2,'X');
  cout << "2: '" << word2 << "','" << name << "' word,name size=" << word2.size()  << " " << name.size()  << endl;
  name.IsolateNextWord(word3,'X');
  cout << "3: '" << word3 << "','" << name << "' word,name size=" << word3.size()  << " " << name.size()  << endl;
  name.IsolateNextWord(word4,'X');
  cout << "4: '" << word4 << "','" << name << "' word,name size=" << word4.size()  << " " << name.size() << endl;

  String word1again("A Sample");
  cout << "Starting Again with '" << nameagain << "' size() = " << nameagain.size() << endl;
  cout << "Words separated by 'X' (and word has '" << word1again << "' in it" << endl;
  nameagain.IsolateNextWord(word1again,'X');
  cout << "1: '" << word1again << "' word,name size=" << word1again.size() << " " << nameagain.size() << endl;

  String iso("0123456789abcdefghijklmnop");
  cout << "From '" << iso << "'" << endl;
  String wordi2 = iso.Isolate(0,5);
  cout << "Isolate(0,5) = '" << wordi2 << "' size()=" << wordi2.size() << endl;
  unsigned int ilimit = iso.size();
  for(unsigned int ii = ilimit - 6; ii < ilimit;ii++) {
    String wordi1 = iso.Isolate(ii,ii+3);
    cout << "Isolate(" << ii << "," << ii+3 << ") = '" << wordi1 << "' size()=" << wordi1.size() << endl;
  }
  cout << "Fill Test" << endl;
  String orig("12345");
  for(unsigned int i=3;i<10;i++) {
    String ns = FillStringToLength(i,orig);
    cout << "Fill to " << i << ": '" << ns << "' size()=" << ns.size() << endl;
  }

  cout << "output in Width" << endl;
  String wid("13245");
  for(unsigned int i=4; i<10 ;i++) {
    cout << i << ": '";
    OutputStringInWidth(cout,i,wid);
    cout << "'" << endl;
  }
}
