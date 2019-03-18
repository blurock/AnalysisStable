#include "platform.hh"

#include "CommBuffer.hh"
#include "String.hh"
#include "Objects.hh"
#define TEMPLATE_INSTANTIATION
#include "Vector.hh"

static void ConstructTest(void);
static void ReadTest(void);
static void EncodeIt(CommBuffer& outbuffer);
static void DecodeIt(CommBuffer& outbuffer);
static void OperatorTest(CommBuffer& outbuffer);
static void NumVecTest(void);

int main()
{
  cout << "Construction Test\n";
  cout << "============================================\n\n";
  ConstructTest();
  cout << "\n\n\n";

  cout << "Read Test\n";
  cout << "============================================\n\n";
  ReadTest();
  cout << "\n\n\n";

  cout << "EncodeIt Test\n";
  cout << "============================================\n\n";
  CommBuffer outbuffer(COMM_BUFF_ENCODE,1000,2000);
  EncodeIt(outbuffer);
  cout << "\n\n\n";

  cout << "DecodeIt Test\n";
  cout << "============================================\n\n";
  DecodeIt(outbuffer);
  cout << "\n\n\n";

  cout << "Operator Test\n";
  cout << "============================================\n\n";
  OperatorTest(outbuffer);
  cout << "\n\n\n";

  cout << "VectorNumeric Test\n";
  cout << "============================================\n\n";
  NumVecTest();
  cout << "\n\n\n";

  return(0);
}


void ReadTest( void )
{
}

void ConstructTest( void )
{
  VectorSimple<int> vecEmpty(5);
  cout << "Empty vector(5)\n";
  vecEmpty.print(cout);
  cout << "\n";

  VectorSimple<double> vec0(5, 2);
  vec0.print(cout);
  cout << endl;

  VectorNumeric vecNum1(10);
  vecNum1[0] = 0;
  vecNum1[1] = 1;
  vecNum1[2] = 2;
  vecNum1[3] = 3;
  vecNum1[4] = 4;
  vecNum1[5] = 5;
  vecNum1.print(cout);
  cout << endl;

  //    double help = getVectorElement(vecNum1, 3);
  //    cout << "-------- getVecEl 3: " << help << endl;
  //    help = getVectorElement(vecNum1, 4);
  //    cout << "-------- getVecEl 4: " << help << endl;
  //    cout << "-------- dotprod vecNum1 . vecNum1: " << dot_product(vecNum1, vecNum1) << endl;

  VectorNumeric vecNum2(vecNum1);
  VectorNumeric vecNum3(5, 3.3);
  VectorNumeric vecNum4(vecNum3);
  vecNum4.ChangeTitle("Copy of vecNum3 ");
  vecNum2.print(cout);
  cout << "\n";
  vecNum3.print(cout);
  cout << "\n";
  vecNum4.print(cout);
  cout << "\n";


  VectorSimple<int> vec1;
  vec1.ChangeTitle("Vector1\n");
  vec1.ChangeDelimitor(", ");
  vec1.AddObject(1);
  vec1.AddObject(11);
  vec1.print(cout);
  cout << "\n";

  VectorSimple<int> vec1Copy(vec1);
  vec1Copy.ChangeTitle("CopyOfVector1\n");
  vec1Copy.print(cout);
  cout << "\n";

  VectorSimple<double> vec2(10);
  vec2.ChangeTitle("Vector2(10)\n");
  vec2.ChangeDelimitor(", ");
  vec2.print(cout);
  cout << "\n";

  VectorSimple<int> vec3("Vector3\n", ", ");
  vec3.AddObject(3);
  vec3.print(cout);
  cout << "\n";

  VectorFull<Identify> vecid;
  vecid.ChangeTitle("VectorId\n");
  vecid.ChangeDelimitor(", ");
  Identify id1(1,"One");
  Identify id2(2,"Two");
  vecid.AddObject(id1);
  vecid.AddObject(id2);
  vecid.print(cout);
  cout << "\n";

  VectorFull< VectorSimple<int> > vecvec;
  vecvec.ChangeTitle("VectorVector\n");
  vecvec.ChangeDelimitor(", ");
  VectorSimple<int> v1;
  v1.ChangeTitle("V1: ");
  v1.AddObject(1);
  v1.AddObject(1);
  VectorSimple<int> v2;
  v2.ChangeTitle("V2: ");
  v2.AddObject(2);
  v2.AddObject(2);
  v2.AddObject(2);
                
  vecvec.AddObject(v1);
  vecvec.AddObject(v2);
  vecvec.print(cout);
  cout << "\n";
}


static void EncodeIt(CommBuffer& outbuffer)
{
  VectorSimple<int> vecint;
  vecint.ChangeTitle("VecInt\n");
  vecint.ChangeDelimitor(", ");

  vecint.AddObject(100);
  vecint.AddObject(200);
  vecint.AddObject(300);

  VectorSimple<double> vecdouble;
  vecdouble.ChangeTitle("VecDouble\n");
  vecdouble.ChangeDelimitor(", ");

  vecdouble.AddObject(100.1);
  vecdouble.AddObject(200.2);
  vecdouble.AddObject(300.3);

  VectorFull<Identify> vecid;
  vecid.ChangeTitle("VectorId\n");
  vecid.ChangeDelimitor(", ");
  Identify id1(1,"One");
  Identify id2(2,"Two");
  vecid.AddObject(id1);
  vecid.AddObject(id2);


  cout << "before encode:\n";
  vecint.print(cout);
  cout << "\n";
  vecdouble.print(cout);
  cout << "\n";
  vecid.print(cout);
  cout << "\n";

  vecint.EncodeThis(outbuffer);
  vecdouble.EncodeThis(outbuffer);
  vecid.EncodeThis(outbuffer);
}


static void DecodeIt(CommBuffer& outbuffer)
{
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());

  VectorSimple<int> veci;
  VectorSimple<double> vecd;
  VectorFull<Identify> vecident;

  veci.DecodeThis(inbuffer);
  vecd.DecodeThis(inbuffer);
  vecident.DecodeThis(inbuffer);

  cout << "after decode:\n";
  veci.print(cout); cout << "\n";
  vecd.print(cout); cout << "\n";
  vecident.print(cout); cout << "\n";

}


static void OperatorTest(CommBuffer& outbuffer)
{
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());

  VectorSimple<int> veci1;
  VectorSimple<double> vecd1;
        
  veci1.DecodeThis(inbuffer);
  vecd1.DecodeThis(inbuffer);


  cout << "Operator ==\n";
  cout << "--------------------------------------------\n\n";
  VectorSimple<int> veci2;
  veci2.ChangeTitle("Veci2\n");
  veci2.ChangeDelimitor(", ");
  veci2.AddObject(100);
  veci2.AddObject(200);
  veci2.AddObject(300);

  VectorSimple<double> vecd2;
  vecd2.ChangeTitle("Vecd2\n");
  vecd2.ChangeDelimitor(", ");
  vecd2.AddObject(100.1);
  vecd2.AddObject(200.2);
  vecd2.AddObject(300.3);

  veci1.print(cout); cout << "\n";
  veci2.print(cout); cout << "\n";
  if (veci1 == veci2)
    cout << "!!! They are equal\n\n";
  else
    cout << "!!! They are not equal\n\n";

  vecd1.print(cout); cout << "\n";
  vecd2.print(cout); cout << "\n";
  if (vecd1 == vecd2)
    cout << "!!! They are equal\n\n";
  else
    cout << "!!! They are not equal\n\n";

  VectorSimple<double> vecd3;
  vecd3.ChangeTitle("Vecd3\n");
  vecd3.ChangeDelimitor(", ");
  vecd3.AddObject(100.1);
  vecd3.AddObject(200.2);
  vecd3.AddObject(300.3);
  vecd3.AddObject(400.4);

  vecd1.print(cout); cout << "\n";
  vecd3.print(cout); cout << "\n";
  if (vecd1 == vecd3)
    cout << "!!! They are equal\n\n";
  else
    cout << "!!! They are not equal\n\n";

  VectorSimple<double> vecd4;
  vecd4.ChangeTitle("Vecd4\n");
  vecd4.ChangeDelimitor(", ");
  vecd4.AddObject(100.1);
  vecd4.AddObject(200.2);
        
  vecd1.print(cout); cout << "\n";
  vecd4.print(cout); cout << "\n";
  if (vecd1 == vecd4)
    cout << "!!! They are equal\n\n";
  else
    cout << "!!! They are not equal\n\n";

  cout << "Concatenate\n";
  cout << "--------------------------------------------\n\n";
  VectorSimple<int> veccon;
  veci1.print(cout); cout << "\n";
  veci2.print(cout); cout << "\n";
  veccon = veci1.Concatenate(veci2);
  veccon.ChangeTitle("Concatenation of above\n");
  veccon.ChangeDelimitor(", ");
  veccon.print(cout); cout << "\n\n";
        
  cout << "Operator < and Operator >\n";
  cout << "--------------------------------------------\n\n";
  vecd1.AddObject(0.7);
  vecd1.print(cout); cout << "\n";
  vecd2.print(cout); cout << "\n";
  if (vecd1 < vecd2)
    cout << "vecd1 < vecd2\n";
  if (vecd2 < vecd1)
    cout << "vecd2 < vecd1\n";
  if (vecd1 > vecd2)
    cout << "vecd1 > vecd2\n";
  if (vecd2 > vecd1)
    cout << "vecd2 > vecd1\n";
}


void NumVecTest( void )
{

  VectorNumeric numvec1;
  numvec1.ChangeTitle("NumVec1\n");
  numvec1.ChangeDelimitor(", ");
  numvec1.AddObject(1.1);
  numvec1.AddObject(1.1);
  numvec1.print(cout); cout << "\n";

  VectorNumeric numvec2;
  numvec2.ChangeTitle("NumVec2\n");
  numvec2.ChangeDelimitor(", ");
  numvec2.AddObject(1.1);
  numvec2.AddObject(1.1);
  numvec2.print(cout); cout << "\n";

  VectorNumeric numvecsum;
  numvecsum = numvec1 + numvec2;
  numvecsum.ChangeTitle("NumVecSum\n");
  numvecsum.ChangeDelimitor(", ");
  numvecsum.print(cout); cout << "\n";

  VectorNumeric numvecsub;
  numvecsub = numvecsum - numvec2;
  numvecsub.ChangeTitle("NumVecSum - NumVec2\n");
  numvecsub.ChangeDelimitor(", ");
  numvecsub.print(cout); cout << "\n";

  VectorNumeric numvecsub2;
  numvecsub2 = numvec2 - numvecsum;
  numvecsub2.ChangeTitle("NumVec2 - NumVecSum\n");
  numvecsub2.ChangeDelimitor(", ");
  numvecsub2.print(cout); cout << "\n";

  VectorNumeric numvecd;
  numvecd.AddObject(2.0);
  numvecd.AddObject(3.0);
  numvecd.ChangeTitle("NumVecD\n");
  numvecd.ChangeDelimitor(", ");
  numvecd.print(cout); cout << "\n";

  VectorNumeric ergVec;

  //    cout << "5 * NumVecd\n";
  //    ergVec = 5.0 * numvecd; 
  //    ergVec.print(cout); cout << "\n";
  cout << "NumVecd * 3\n";
  ergVec = numvecd * 3.0;
  ergVec.print(cout); cout << "\n";

  numvecd.print(cout); cout << "\n";
  //    cout << "2 / NumVecd\n";
  //    ergVec = 2.0 / numvecd; 
  //    ergVec.print(cout); cout << "\n";
  cout << "NumVecd / 3\n";
  ergVec = numvecd / 3.0; 
  ergVec.print(cout); cout << "\n\n";

  double dotprod;
  dotprod = numvec1 * numvec2;
  cout << dotprod << "\n";

  VectorNumeric n1;
  n1.AddObject(1);
  n1.AddObject(1);
  n1.print(cout); cout << "\n";

  VectorNumeric n2;
  n2.AddObject(2);
  n2.AddObject(2);
  n2.print(cout); cout << "\n";

  double dprod;
  dprod =  n1 * n2;
  cout << dprod << "\n";

}
