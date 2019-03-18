/*  FILE     main.cpp
**  PACKAGE  MatrixNumeric    
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    test program for MatrixNumeric package
**
**  REFERENCES
**
*/
#define TEMPLATE_INSTANTIATION

#include "platform.hh"

#include "CommBuffer.hh"
#include "String.hh"
#include "Objects.hh"
#include "MixedClasses.hh"
#include "Vector.hh"

#include "System.hh"
#include "MatrixNumeric.hh"

// Prototypes
int constructionTest(ReactionSystemBase *g);
int encodeTest(ReactionSystemBase *g);
int encodeItTest(CommBuffer& outbuffer);
int decodeItTest(CommBuffer& outbuffer);
int operationTest(ReactionSystemBase *g);


class MatrixNumericTest : public ReactionSystemLevel1
{
public:

  // Constructor
       MatrixNumericTest(int argc, char *argv[]) 
       : ReactionSystemLevel1(argc, argv)
    {
      SingleSystemCommand constructtest("constructionTest",
					"Test of MatrixNumeric Constructions",
					&constructionTest);
      SingleSystemCommand encodetest("encodeTest",
				     "Test of Encoding and Decoding",
				     &encodeTest);
      SingleSystemCommand operationtest("operationTest",
					"Test of Operations",
					&operationTest);
      Commands.AddObject("constructionTest", constructtest);
      Commands.AddObject("encodeTest", encodetest);
      Commands.AddObject("operationTest", operationtest);
      cout << endl;
      PrintCommandList(this);
      cout << endl << endl;
    }
}; // MatrixNumericTest



int main(int argc, char *argv[])
{
  cout << "\n================= MatrixNumericTest ===============\n";
  MatrixNumericTest test(argc, argv);
  return test.Run(argc, argv);
}


int operationTest(ReactionSystemBase *)
{
  MatrixNumeric numMat1(3, 5);
  numMat1[2][4] = 1;
  numMat1[1][1] = 1;

  MatrixNumeric numMat2(2, 2);
  numMat2[0][0] = 2;
  numMat2[1][1] = 3;

  cout << "numMat1\n";
  numMat1.print(cout);
  cout << "\nnumMat2\n";
  numMat2.print(cout); cout << endl;
  
  VectorNumeric row = numMat1.getMatrixRow(0);
  cout << "row 0: ";
  row.print(cout); cout << endl;
  row = numMat1.getMatrixRow(1);
  cout << "row 1: ";
  row.print(cout); cout << endl;

  VectorNumeric col1 = numMat1.getMatrixColumn(1);
  cout << "col 1: ";
  col1.print(cout); cout << endl << endl;

  MatrixNumeric numMat3 = numMat1;
  cout << "numMat3 = numMat1\n";
  numMat3.print(cout); cout << endl;
	
  MatrixNumeric numMat4 = numMat1 + numMat1;
  cout << "numMat4 = numMat1 + numMat1\n";
  numMat4.print(cout); cout << endl;

  MatrixNumeric numMat5 = numMat4 - numMat1;
  cout << "numMat5 = numMat4 - numMat1\n";
  numMat5.print(cout); cout << endl;

  MatrixNumeric numMat6 = numMat4 + numMat2;
  cout << "numMat6 = numMat4 + numMat2\n";
  numMat6.print(cout); cout << endl;
  numMat6 = numMat4 - numMat2;
  cout << "numMat6 = numMat4 - numMat2\n";
  numMat6.print(cout); cout << endl;

  MatrixNumeric tempMat;
  tempMat = numMat5.transpose();
  cout << "numMat5 transpose " << endl;
  tempMat.print(cout); 
  cout << endl;

  MatrixNumeric numMat7help(3, 2);
  numMat7help[0][0] = 2;
  numMat7help[1][1] = 2;
  numMat7help[2][1] = 2;
		
  cout << "numMat2\n";
  numMat2.print(cout); cout << endl;
  cout << "numMat7help\n";
  numMat7help.print(cout); cout << endl;

  MatrixNumeric numMat7 = numMat7help * numMat2;
  cout << "numMat7 = numMat7help * numMat2\n";
  numMat7.print(cout); cout << endl;

  MatrixNumeric numMat8 =  numMat7help * 2;
  cout << "numMat8 = numMat7help * 2\n";
  numMat8.print(cout); cout << endl;

  return 0;
}

int constructionTest(ReactionSystemBase *)
{
  cout << "===== constructionTest =========================\n";
	
  MatrixNumeric numMat1;
  MatrixNumeric numMat2(2, 2);
  numMat2[0][0] = 2;
  numMat2[1][1] = 2;
  MatrixNumeric numMat3(3, 5);
  numMat3[2][4] = 3;
  numMat3[1][1] = 3;
  MatrixNumeric numMat4(numMat3);
  MatrixNumeric numMat5;
  numMat5 = numMat2;

  cout << "numMat1 0 x 0" << endl;
  numMat1.print(cout); cout << endl;
  cout << "numMat2 2 x 2" << endl;
  numMat2.print(cout); cout << endl;
  cout << "numMat3 3 x 5" << endl;
  numMat3.print(cout); cout << endl;
  cout << "copy of numMat3" << endl;
  numMat4.print(cout); cout << endl;
  cout << "numMat5 = numMat2" << endl;
  numMat5.print(cout); cout << endl;

  return 0;
}

int encodeTest(ReactionSystemBase *)
{
  cout << "===== encodeTest ===============================\n";

  CommBuffer outbuffer(COMM_BUFF_ENCODE,50,200);
  encodeItTest(outbuffer);
  decodeItTest(outbuffer);

  return 0;
}

int encodeItTest(CommBuffer& outbuffer)
{
  cout << "encodeItTest:___________________________________\n";

  MatrixNumeric numMat0;

  MatrixNumeric numMat1(2, 4);
  numMat1[0][0] = 11;
  numMat1[0][1] = 12;
  numMat1[0][2] = 13;
  numMat1[0][3] = 14;
  numMat1[1][0] = 21;
  numMat1[1][1] = 22;
  numMat1[1][2] = 23;
  numMat1[1][3] = 24;
	
  MatrixNumeric numMat2(3, 3);

  cout << "before encode:\n";
  cout << "--------------\n";
  numMat0.print(cout); cout << "\n";
  numMat1.print(cout); cout << "\n";
  numMat2.print(cout); cout << "\n";

  numMat0.EncodeThis(outbuffer);
  numMat1.EncodeThis(outbuffer);
  numMat2.EncodeThis(outbuffer);
  cout << "\n";
  cout << "___________________________________________\n";

  return 0;
}


int decodeItTest(CommBuffer& outbuffer)
{
  cout << "decodeItTest:___________________________________\n";
  CommBuffer inbuffer(outbuffer.GetBuffer(), outbuffer.GetBufferSize());

  MatrixNumeric nMat0;
  MatrixNumeric nMat1;
  MatrixNumeric nMat2;

  nMat0.DecodeThis(inbuffer);
  nMat1.DecodeThis(inbuffer);
  nMat2.DecodeThis(inbuffer);

  cout << "after decode:\n";
  cout << "-------------\n";
  nMat0.print(cout); cout << "\n";
  nMat1.print(cout); cout << "\n";
  nMat2.print(cout); cout << "\n";
  cout << "\n";
  cout << "___________________________________________\n";
  return 0;
}
