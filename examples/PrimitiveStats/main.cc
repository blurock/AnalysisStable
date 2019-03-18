#define TEMPLATE_INSTANTIATION

#include "System.hh"
#include "Vector.hh"
#include "MatrixNumeric.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"
#include "PrimitiveStats.hh"


int PrimitiveStatTest(void);
int GeneralDistributionStatsTest(void);
int EvenDistributionStatsTest(void);
int GeneralDistributionStatsExceptTest(void);
int EvenDistributionStatsExceptTest(void);


//	creates Prim.St., Gen.Distr.St., EvenDistr.St. and encodes them
int EncodeItTest(CommBuffer& outbuffer);
//	decodes above
int DecodeItTest(CommBuffer& outbuffer);

int CountTest(void);


int main()
{
  PrimitiveStatTest();

  GeneralDistributionStatsTest();
  EvenDistributionStatsTest();
	
  GeneralDistributionStatsExceptTest();
  EvenDistributionStatsExceptTest();

  CommBuffer outbuffer(COMM_BUFF_ENCODE,50,200);
  EncodeItTest(outbuffer);
  DecodeItTest(outbuffer);

  CountTest();


  return(0);
}




int CountTest(void)
{
  unsigned int i,j;
  
  vector<char*> filename;
  filename.push_back("___0.txt");
  filename.push_back("___1.txt");
  filename.push_back("___2.txt");
  filename.push_back("___3.txt");
  filename.push_back("___4.txt");

  VectorNumeric numvec0;
  for (i=0; i<100; i++)
    numvec0.AddObject(7.2);
  EvenDistributionStats edstat0(numvec0);
  double intersiz = (edstat0.Max - edstat0.Min)/10;
  if (intersiz != 0)
    {
      edstat0.IntervalSize = intersiz;
      edstat0.CountFrequencies();
    }

  VectorNumeric numvec1;
  for (i=0; i<50; i++)
    numvec1.AddObject(0);
  for (i=50; i<100; i++)
    numvec1.AddObject(1);
  EvenDistributionStats edstat1(numvec1);
  intersiz = (edstat1.Max - edstat1.Min)/10;
  if (intersiz != 0)
    {
      edstat1.IntervalSize = intersiz;
      edstat1.CountFrequencies();
    }

  //  11 Intervalle 111
	VectorNumeric numvec2;
  for (i=0; i<50; i++)
    numvec2.AddObject(0);
  for (i=50; i<100; i++)
    numvec2.AddObject(2);
  for (i=100; i<150; i++)
    numvec2.AddObject(4);
  EvenDistributionStats edstat2(numvec2);
  intersiz = (edstat2.Max - edstat2.Min)/10;
  if (intersiz != 0)
    {
      edstat2.IntervalSize = intersiz;
      edstat2.CountFrequencies();
    }

  VectorNumeric numvec3;
  for (i=0; i<5; i++)
    numvec3.AddObject(0);
  for (i=5; i<10; i++)
    numvec3.AddObject(2);
  EvenDistributionStats edstat3(numvec3);
  intersiz = (edstat3.Max - edstat3.Min)/10;
  if (intersiz != 0)
    {
      edstat3.IntervalSize = intersiz;
      edstat3.CountFrequencies();
    }

  VectorNumeric numvec4;
  for (i=0; i<10; i++)
    numvec4.AddObject(1);
  EvenDistributionStats edstat4(numvec4);
  intersiz = (edstat4.Max - edstat4.Min)/10;
  if (intersiz != 0)
    {
      edstat3.IntervalSize = intersiz;
      edstat3.CountFrequencies();
    }

  Vector<EvenDistributionStats> vecedst;
  vecedst.AddObject(edstat0);
  vecedst.AddObject(edstat1);
  vecedst.AddObject(edstat2);
  vecedst.AddObject(edstat3);
  vecedst.AddObject(edstat4);

  for (j=0; j<filename.size(); j++)
    {
      cout << vecedst[j] << endl;

      ofstream myout(filename[j]);
      if(!myout) 
	{
	  cout <<  "Cannot open file\n";
	  return 1;
	}
      vecedst[j].WriteCounts2File(myout);
    }

  return 0;
}


int PrimitiveStatTest(void)
{
  cout << "PrimitiveStatTest:__________________________\n";

  VectorNumeric numvec;
  numvec.ChangeTitle("primstatnumvec: \n");

  numvec.AddObject(1.2);
  numvec.AddObject(2.2);
  numvec.AddObject(4.2);
  numvec.AddObject(3.2);
  numvec.AddObject(2.2);

  numvec.print(cout); cout << endl;

  PrimitiveStats primstat(numvec);
  cout << "primstat: \n" <<  primstat << endl;

  primstat.AddValue(13);
  primstat.AddValue(13);
  primstat.AddValue(17);
  primstat.AddValue(13);
  cout << "primstat: \n" <<  primstat << endl;

  primstat.RemoveValue(7, false);
  primstat.RemoveValue(13, false);
  cout << "primstat: \n" <<  primstat << endl;
  primstat.RemoveValue(13, true);
  cout << "primstat: \n" <<  primstat << endl;

  cout << "___________________________________________\n";
  return 0;
}


int GeneralDistributionStatsTest(void)
{
  cout << "GeneralDistributionStatsTest:__________________________\n";
  VectorNumeric numvec;

  numvec.AddObject(1.1);
  numvec.AddObject(4.3);
  numvec.AddObject(4.3);
  numvec.AddObject(8.4);
  numvec.AddObject(5.8);
  numvec.AddObject(9.2);
  numvec.AddObject(3.9);
  numvec.AddObject(9.9);
  numvec.AddObject(19.9);
  numvec.AddObject(29.9);
  numvec.AddObject(19.9);

	
  GeneralDistributionStats gdst0;
  cout << "0-----------\n" << gdst0 << endl;
  GeneralDistributionStats gdst1(numvec);
  cout << "1-----------\n" << gdst1 << endl;

	
  cout << "___________________________________________\n";
  return 0;
}


int GeneralDistributionStatsExceptTest(void)
{
  cout << "GeneralDistributionStatsExceptTest:__________________________\n";
	
  GeneralDistributionStatsExcept gdstnumex0;
  cout << "0-----------\n" << gdstnumex0<< endl;

  VectorNumeric numvec;
  numvec.AddObject(1);
  numvec.AddObject(2);
  numvec.AddObject(4);
  numvec.AddObject(3);
  numvec.AddObject(5);
  numvec.AddObject(7);


  GeneralDistributionStatsExcept gdstnumex(numvec);
  cout << "1-----------\n" << gdstnumex << endl;
  GeneralDistributionStatsExcept gdstex(numvec);
  cout << "1-vec-------\n" << gdstex << endl;
	
  gdstex.AddException(1);
  gdstex.AddException(1);
  gdstex.AddException(8.1);
  gdstex.AddException(17.1);
  gdstex.AddException(17.1);
  gdstex.AddException(2);
  cout << "2-***-------\n" << gdstex << endl;

  gdstex.RemoveException(2.0);
  gdstex.RemoveException(17.2);
  cout << "3-----------\n" << gdstex << endl;


  VectorNumeric excnumvec;
  excnumvec.AddObject(1);
  excnumvec.AddObject(3);
  excnumvec.AddObject(8);
	

  GeneralDistributionStatsExcept gdstnumex4(numvec, excnumvec);
  cout << "4-----------\n" << gdstnumex4 << endl;

  VectorNumeric left(5);
  left[0] = 1.1;
  left[1] = -2;
  left[2] = 19.9;
  left[3] = 19.9;
  left[4] = 4.3;

  VectorNumeric right(5);
  right[0] = 4.3;
  right[1] = 2;
  right[2] = 19.9;
  right[3] = 20;
  right[4] = 19.9;
	
  GeneralDistributionStatsExcept gdstex6(numvec, left, right, excnumvec);
  cout << "6-----------\n" << gdstex6 << endl;

  gdstex6.AddExceptionsFrom(5);
  cout << "AddExcept from 5---\n" << gdstex6<< endl;

  gdstex6.AddExceptionsTo(3.9);
  cout << "AddExcept to 3.9---\n" << gdstex6<< endl;

  gdstex6.RemoveExceptionsFrom(5.5);
  cout << "RemoveExceptions from 5.5---\n" << gdstex6<< endl;

  gdstex6.RemoveExceptionsTo(2);
  cout << "RemoveExceptions to 2---\n" << gdstex6<< endl;
	
  gdstex6.RemoveAllExceptions();
  cout << "RemoveAllExceptions---\n" << gdstex6<< endl;
  cout << "___________________________________________\n";
	
  return 0;
}


int EvenDistributionStatsExceptTest(void)
{
  cout << "EvenDistributionStatsExceptTest:__________________________\n";
  EvenDistributionStatsExcept edstnumex0;
  cout << "0-----------\n" << edstnumex0<< endl;

  VectorNumeric numvec;
  numvec.AddObject(1);
  numvec.AddObject(1);
  numvec.AddObject(4);
  numvec.AddObject(3);
  numvec.AddObject(5);
  numvec.AddObject(7);
  numvec.AddObject(2);


  EvenDistributionStatsExcept edstnumex(numvec);
  cout << "1-----------\n" << edstnumex << endl;
  EvenDistributionStatsExcept edstex(numvec);
  cout << "1-vec-------\n" << edstex << endl;
	
  edstex.AddException(1);
  edstex.AddException(1);
  edstex.AddException(8.1);
  edstex.AddException(17.1);
  edstex.AddException(17.1);
  edstex.AddException(2);
  edstex.AddException(1);
  cout << "2-***-------\n" << edstex << endl;

  edstex.RemoveException(2.0);
  edstex.RemoveException(17.2);
  cout << "3-----------\n" << edstex << endl;

  VectorNumeric excnumvec;
  excnumvec.AddObject(1);
  excnumvec.AddObject(3);
  excnumvec.AddObject(8);
	
  EvenDistributionStatsExcept edstnumex4(numvec, excnumvec);
  cout << "4-----------\n" << edstnumex4 << endl;

  EvenDistributionStatsExcept edstnumex5(numvec, 2, excnumvec);
  cout << "5-----------\n" << edstnumex5 << endl;

  EvenDistributionStatsExcept edstex6(edstnumex5);
  cout << "Copy of 5---\n" << edstex6<< endl;

  edstex6.AddExceptionsFrom(5);
  cout << "AddExcept from 5---\n" << edstex6<< endl;

  edstex6.AddExceptionsTo(3.9);
  cout << "AddExcept to 3.9---\n" << edstex6<< endl;

  edstex6.RemoveExceptionsFrom(5.5);
  cout << "RemoveExceptions from 5.5---\n" << edstex6<< endl;

  edstex6.RemoveExceptionsTo(2);
  cout << "RemoveExceptions to 2---\n" << edstex6<< endl;

  edstex6.RemoveAllExceptions();
  cout << "RemoveAllExceptions---\n" << edstex6<< endl;
  cout << "___________________________________________\n";
  return 0;
}


int EvenDistributionStatsTest(void)
{
  cout << "EvenDistributionStatsTest:__________________________\n";
  VectorNumeric numvec;

  numvec.AddObject(0);
  numvec.AddObject(2);
  numvec.AddObject(2.1);
  numvec.AddObject(3);
  numvec.AddObject(2);
  numvec.AddObject(5.5);
  numvec.AddObject(4);
  numvec.AddObject(10);
  numvec.AddObject(0.1);

	
  EvenDistributionStats edst41(numvec);
  edst41.IntervalSize = 3;
  edst41.CountFrequencies();
  cout << "41-----------\n" << edst41 << endl;


  EvenDistributionStats edst0;
  cout << "0------------\n" << edst0 << endl;
  EvenDistributionStats edst11(numvec);
  cout << "11-----------\n" << edst11 << endl;

  EvenDistributionStats edst21(numvec, 1);
  cout << "21-----------\n" << edst21 << endl;

  EvenDistributionStats edst31(edst21);
  cout << "Copy of 21---\n" << edst31 << endl;

  cout << "___________________________________________\n";
  return 0;
}


int EncodeItTest(CommBuffer& outbuffer)
{
  cout << "EncodeItTest:___________________________________\n";

  VectorNumeric numvec;
  numvec.ChangeTitle("Values: \n");
  numvec.AddObject(4.3);
  numvec.AddObject(7.2);
  numvec.AddObject(8.4);
  numvec.AddObject(5.8);
  numvec.AddObject(9.2);
  numvec.AddObject(3.9);
  PrimitiveStats primstat(numvec);

  VectorNumeric numvec2;
  numvec2.ChangeTitle("Values2: \n");
  numvec2.AddObject(1.1);
  numvec2.AddObject(4.3);
  numvec2.AddObject(7.2);
  numvec2.AddObject(8.4);
  numvec2.AddObject(5.8);
  numvec2.AddObject(9.2);
  numvec2.AddObject(3.9);
  numvec2.AddObject(9.9);
  numvec2.AddObject(19.9);
  numvec2.AddObject(29.9);
  numvec2.AddObject(19.9);
  GeneralDistributionStats gdst2(numvec2);
	
  VectorNumeric numvec3;
  numvec3.ChangeTitle("Values3: \n");
  numvec3.AddObject(0);
  numvec3.AddObject(2);
  numvec3.AddObject(3);
  numvec3.AddObject(2);
  numvec3.AddObject(5);
  numvec3.AddObject(4);
  numvec3.AddObject(10);
  EvenDistributionStats edst3(numvec3, 1);

  GeneralDistributionStatsExcept gdstexc(numvec2);
  gdstexc.AddException(4.3);
  EvenDistributionStatsExcept edstexc(numvec2);
  edstexc.AddException(4.3);
	
  cout << "before encode:\n";
  cout << "--------------\n";
  cout << primstat << "\n\n";
  cout << gdst2 << "\n\n";
  cout << edst3 << "\n\n";
  cout << gdstexc << "\n\n";
  cout << edstexc << "\n\n";

  Encode(outbuffer, primstat);
  Encode(outbuffer, gdst2);
  Encode(outbuffer, edst3);
  Encode(outbuffer, gdstexc);
  Encode(outbuffer, edstexc);
  cout << "\n\n";
  cout << "___________________________________________\n";

  return 0;
}


int DecodeItTest(CommBuffer& outbuffer)
{
  cout << "DecodeItTest:___________________________________\n";
  CommBuffer inbuffer(outbuffer.GetBuffer(), outbuffer.GetBufferSize());

  PrimitiveStats prst;
  GeneralDistributionStats gdst;
  EvenDistributionStats edst;
  cout << "-33------------\n";
  GeneralDistributionStatsExcept gdex;
  cout << "-44------------\n";
  EvenDistributionStatsExcept edex;
  cout << "after decode:\n";
  cout << "-------------\n";

  Decode(inbuffer,prst);
  cout << prst << "\n\n";
  Decode(inbuffer,gdst);
  cout << gdst << "\n\n";
  Decode(inbuffer,edst);
  cout << edst << "\n\n";
  Decode(inbuffer,gdex);
  cout << gdex << "\n\n";
  Decode(inbuffer,edex);
  cout << edex << "\n\n";

  cout << "\n\n";
  cout << "___________________________________________\n";
  return 0;
}
