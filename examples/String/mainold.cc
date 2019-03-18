

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


int isemptytest();

void EncodeTest();

int routinesTest();

int showNbs(const String& info, const String& instr, ostream out = cout);





int main(int argc, char *argv[])

{



	for (int i=0; i<10; i++)

	{

		String str1 = Int2String(i);

		cout << str1 << endl;

	}







	EncodeTest();



	isemptytest();



	routinesTest();



	return 0;



	 ifstream myin1("infile2.inp");

     if(!myin1) 

	  {

	  cout <<  "Cannot open file\n";

	  return 1;

	  }

     else

	  {

	  String line;

	  line.ReadFullLine(myin1);

	  cout << line << "\n";

	  line.ReadFullLine(myin1);

	  cout << line << "\n";

	  line.ReadFullLine(myin1);

	  cout << line << "\n";

	  line.ReadFullLine(myin1);

	  cout << line << "\n";

	  line.ReadFullLine(myin1);

	  cout << line << "\n";

	  }

     ifstream myin("infile.inp");

     if(!myin) 

	  {

	  cout <<  "Cannot open file\n";

	  return 1;

	  };

     

     

     ofstream myout("outfile");

     if(!myout) 

	  {

	  cout <<  "Cannot open file\n";

	  return 1;

	  };

     cout << " this was pre-stage \n";

     

    

     String instra = "12345";

     String instrb = "abcde";     



     cout << "AppendToEnd\n";

     instra.AppendToEnd(instrb);

     cout << instra;

     cout << "\n";

	  

     String instr1;

     cout << " operator>> " << " \n";

     myin >> instr1;

     cout << " --------------------- " << "\n";

     cout << instr1 << "\n";

     cout << " --------------------- " << "\n";

     cout << " size of string instr1 " << instr1.size() << endl;

     cout << " --------------------- " << "\n";



     cout << " SkipCommentLines " << " \n";

     instr1.SkipCommentLines(myin);

     cout << " --------------------- " << "\n";

     cout << instr1 << "\n";

     cout << " --------------------- " << "\n";

     cout << " size of string instr1 " << instr1.size() << endl;

     cout << " --------------------- " << "\n";

 

     cout << " ReadFullLine " << " \n";

     instr1.ReadFullLine(myin);

     cout << " --------------------- " << "\n";

     cout << instr1 << "\n";

     cout << " --------------------- " << "\n";

     cout << " size of string instr1 " << instr1.size() << endl;

     cout << " --------------------- " << "\n";

 





     cout << "========================================\n";

     String instr2 = instr1.Isolate(5, 10);

     cout << " this is part of instr1 (characters 5-10)" << " \n";

     cout << instr2 << "\n";

     cout << " --------------------- " << "\n";



     cout << "*************\n";

     String instrwh = instr1.Isolate(5, 5);

     cout << " this is part of instr1 (characters 5-5)" << " \n";

     cout << instrwh << "\n";

     cout << "*************" << "\n";

     

     String instr3;

     instr1.IsolateNextWord(instr3, ' ');

     cout << " this is also part of instr1 - word1 " << " \n";

     cout << instr3 << "\n";

     cout << " --------------------- " << "\n";



     String instr4;

     instr1.IsolateNextWord(instr4, ' ');

     cout << " this is also part of instr1 - word2 " << " \n";

     cout << instr4 << "\n";

     cout << " --------------------- " << "\n";



     cout << " --------------------- " << "\n";

     cout << " size of string instr1 " << instr1.size() << endl;

     cout << " --------------------- " << "\n";



/*     

     cout << " this is the remainder of instr1 " << " \n";

     cout << instr1 << "\n";

     cout << " --------------------- " << "\n";



*/



/*     instr1.ReadFullLine(cin);

     

     cout << " this is new instr1 " << " \n";

     cout << " --------------------- " << "\n";

     cout << instr1 << "\n";

     cout << " --------------------- " << "\n";



*/

 

/* 

     instr4.SkipCommentLines(cin);

     cout << " this is instr4 " << endl;

     cout << " --------------------- " << "\n";

     cout << instr4 << endl;

*/



     return(0);

     

}





void EncodeTest()

{
  unsigned int i;
  
/*

cout << "0----------1\n";   

     CommBuffer outbuffer(COMM_BUFF_ENCODE,1,2);

	 

	 int cntout = outbuffer.GetBufferSize();

	 cout << "Size of buffer: " << cntout << "\n";

cout << "0----------2\n";   



     String strin = "12345678901234567890", strout;

cout << strin << endl;   

     

	  Encode(outbuffer,strin);

cout << "0----------3\n";   



	  cntout = outbuffer.GetBufferSize();

cout << "0----------4\n";   

	  cout << "Size of buffer: " << cntout << "\n";

cout << "0----------5\n";   

     

     CommBuffer inbuffer(outbuffer.GetBuffer(),

			 outbuffer.GetBufferSize());



	  unsigned int cntin = inbuffer.GetBufferSize();

cout << "Size of buffer: " << cntin << "\n";



	 Decode(inbuffer,strout);

cout << strout << endl;   



*/

cout << "**********************" << endl;



     CommBuffer outbuffer2(COMM_BUFF_ENCODE,2,1);

     char test1[] = "abcdefghijklmnop";

     char test2[] = "won't come back";

     char *test11,*test21;

     test11 = (char *) malloc(19);

     for(i=0;i<19;i++)

	  *(test11 + i) = test1[i];

     test21 = (char *) malloc(16);

     for(i=0;i<16;i++)

	  *(test21+i) = test2[i];

     

     cout << "The two strings written out are:\n";

     cout << test11;

     cout << "\n";

     cout << test21;

     cout << "\n";

     cout << "and now encoding\n";

     

     Encode(outbuffer2,&test11);

     Encode(outbuffer2,&test21);



     cout << " and decoding\n";

     cout << "The size of the buffer is:  ";

     cout << outbuffer2.GetBufferSize();

     cout << "\n";

     

     cout << "The first ten objects in the buffer are:\n";

     char *c = outbuffer2.GetBuffer();

     

     for(unsigned int cnt = 0; cnt < 30; cnt++)

       {

	 if(!(cnt % 10))

	   cout << "\n";

	 int num = (int) *c;

	 cout << cnt << "  " << num << "  ";

	 

	 c++;

       }

     

       

     CommBuffer inbuffer2(outbuffer2.GetBuffer(),

			 outbuffer2.GetBufferSize());

     char *intest1,*intest2;
     intest1 = (char *) malloc(16);
     intest2 = (char *) malloc(16);

     Decode(inbuffer2,&intest1);

     cout << "The first string is\n";

     cout << intest1;

     cout << "\n";

     Decode(inbuffer2,&intest2);

     cout << "The second string is\n";

     cout << intest2;

     cout << "\n";



}     





int isemptytest(void)

{

	cout << "-----------------\n";

	String str1 = "";

	cout << str1 << endl;

	cout << str1.size() << endl;

	if (str1.IsEmpty() == true)

		cout << "true: " << str1.IsEmpty() << endl;

	else

		cout << "false: " << str1.IsEmpty() << endl;



	cout << "-----------------\n";

	String str2 = "1";

	cout << str2 << endl;

	cout << str2.size() << endl;

	if (str2.IsEmpty() == true)

		cout << "true: " << str2.IsEmpty() << endl;

	else

		cout << "false: " << str2.IsEmpty() << endl;



	cout << "------------------\n\n";



	return 0;

}





int routinesTest()

{

	String line, lineCopy, word;



    ifstream myin("infile.inp");

    if(!myin) 

	{

		cout <<  "Cannot open file\n";

		return 1;

	};



	for (unsigned int i=0; i<6; i++)

		line.ReadFullLine(myin);



	showNbs("Original Line", line);



	lineCopy = line;

	lineCopy.EliminateLeadingBlanks();

	showNbs("Original Line EliminateLeadingBlanks", lineCopy);

	cout << endl;



	lineCopy = line;

	lineCopy.EliminateBlanks();

	showNbs("Original Line EliminateBlanks", lineCopy);

	cout << endl;



	lineCopy = line;

	lineCopy.EliminateLeadingBlanks();

	lineCopy.IsolateNextWord(word, ' ');

	showNbs("Original Line EliminateLeadingBlanks and IsolateNextWord m. ' '", word);

	showNbs("Rest of Line", lineCopy);

	cout << endl;



	lineCopy.EliminateLeadingBlanks();

	lineCopy.IsolateNextWord(word, ' ');

	showNbs("Once More EliminateLeadingBlanks and IsolateNextWord m. ' '", word);

//	showNbs("Rest of Line", lineCopy);// only ok if one delim is behind

	cout << endl;



	return 0;

}





int showNbs(const String& info, const String& instr, ostream out)

{

	String str = instr;

	String::iterator iterStr;

	int nbNulls, nbBlanks, nbTabs;

	nbNulls = 0;

	nbBlanks = 0;

	nbTabs = 0;



	for(iterStr=str.begin(); iterStr<str.end(); iterStr++)

	{

		if (*iterStr == '\0')

			nbNulls++;

		if (*iterStr == '\t')

			nbTabs++;

		if (*iterStr == ' ')

			nbBlanks++;

	}



	out << info << endl;

	out << str << endl;

	out << "Number of Blanks: " << nbBlanks << endl;

	out << "Number of Tabs: " << nbTabs << endl;

	out << "Number of Nulls: " << nbNulls << endl;





	return 0;

}

