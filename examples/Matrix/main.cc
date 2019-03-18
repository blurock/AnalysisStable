/*  FILE     
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
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
/*  FILE     
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
//#define TEMPLATE_INSTANTIATION
#include "Basis/System.hh"
#include "Basis/Matrix.hh"
//#undef TEMPLATE_INSTANTIATION



static void EigenVectorTest();

static Matrix<double> ReadInMatrix(istream& in);
static vector<double> ReadInVector(istream& in);
static void ReadAndTranspose(istream& in);

static void PrintOutVector(vector<double> Vec);
static int BasicMatrixTest();
static void CloneTest(istream& in);

/*S Main Program
*/
 
/*F main
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
main (int argc, char *argv[])
{  
  /*
    
    int i, j, k;
    int DIM1, DIM2;
    int N;
    double x;
    int y;
    */     
  
  cout << "-----------------------------" << endl;
  cout << " begin test program for Matrix " << endl;
  cout << "-----------------------------" << endl;
  cout << "Number of Arguments: " << argc << "\n";
  
  if(argc == 1)
    {
      EigenVectorTest();
    }
  else
    {
      String test(argv[1]);
  
      if(test == "Basic")
	{
	  BasicMatrixTest();
	}
      else if(test == "Transpose")
	{
	  ifstream in("infile.inp");
	  ReadAndTranspose(in);
	}
      else if(test == "Clone")
	{
	  ifstream in("infile.inp");
	  CloneTest(in);
	}
    }
  
  return 0;
  
}
/*S Eigenvector Routines
*/
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void EigenVectorTest()
     {
       cout << "EigenVectorTest\n";
       
     ifstream myin("infile.inp");
     if(!myin) 
	  {
	  cout <<  "Cannot open file\n";
	  };
     Matrix<double> M1=ReadInMatrix(myin);

     Matrix<double> corr = M1 * M1.transpose();
     Matrix<double> M2 = M1.transpose();
     M1 = M2;

	cout << " -------------------- M1-------\n";

	cout << M1;
	M2 = M1.transpose();

	cout << " -------------------- M2-------\n";

	cout << M2;

/*
     Matrix<double> m1(corr.size(),corr.size());
     vector<double> v1(corr.size());
     int nrot;
     
     jacobi(corr,v1,m1,nrot);
     cout << v1;
     cout << m1;
*/
/*
     cout << "Original Matrix\n";
     cout << corr;
     
     cout << "\n EigenVector\n";
     EigenVectors eigen(corr,true,true);
     cout << eigen;
*/

     PCAAnalysis pca(M1);
     cout << pca;
     Matrix<double> trans = pca.GetTransformedCoordinates();
     cout << trans;
     
     }

/*S Basic Test Routines
*/
/*F BasicMatrixTest()
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static int BasicMatrixTest()
     {
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
     
     Matrix<double> M1=ReadInMatrix(myin);
     
     cout << " after reading matrix M1 " << endl;
     cout << " ----------------------------" << endl;
     cout << " M1.size() = " << M1.size() << endl;
     cout << " M1[0].size() = " << M1[0].size() << endl;
     cout << " ----------------------------" << endl;
     cout << M1;
     cout << " ----------------------------" << endl;
     Matrix<double> M2=ReadInMatrix(myin);
     
     cout << " after reading matrix M2 " << endl;
     cout << " ----------------------------" << endl;
     cout << " M2.size() = " << M2.size() << endl;
     cout << " M2[0].size() = " << M2[0].size() << endl;
     cout << " ----------------------------" << endl;
     cout << M2;
     cout << " ----------------------------" << endl;
     cout << " M1+M2 = " << M1+M2 << endl;
     cout << " ----------------------------" << endl;
     cout << " M1-M2 = " << M1+M2 << endl;
     cout << " ----------------------------" << endl;
     cout << " M1*M2 = " << M1*M2 << endl;
     cout << " ----------------------------" << endl;
     cout << " transposed M1  = " << M1.transpose() << endl;
     cout << " ----------------------------" << endl;
     cout << " ----------------------------" << endl;
     cout << " test for system of linear equations " << endl;
     Matrix<double> A1=ReadInMatrix(myin);
     vector<double> C1=ReadInVector(myin);
     cout << " ----------------------------" << endl;
     cout << " matrix of coefficients " << endl;
     cout << A1;
     cout << " ----------------------------" << endl;
     cout << " right-handside vector  " << endl;
     cout << C1;
     cout << " ----------------------------" << endl;
     A1.gauss_jordan(A1, C1, A1.size());
     cout << " vector of solutions " << endl;
     PrintOutVector(C1);
     cout << " ----------------------------" << endl; 
     cout << " end of Matrix test " << endl;
     myin.close();
	return 0;

     }
/*F mat = ReadInMatrix(in)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static Matrix<double> ReadInMatrix(istream& in)
     {
     String str1;
     String str2;
     String word1;
     int DIM1, DIM2;
     int i, j;
     
     cout << " read in DIM1"  << endl;
     cout << "----------------------------- \n";
     str1.ReadFullLine(in);
     str1.IsolateNextWord(word1, ' ');
     DIM1=word1.ToInteger();
     cout << "this is DIM1 "  << DIM1 << endl;
     cout << "----------------------------- \n";
     cout << " read in DIM2"  << endl;
     cout << "----------------------------- \n";
     // str1.IsolateNextWord(word1, ' ');
     DIM2=str1.ToInteger();
     cout << "this is DIM2 "  << DIM2 << endl;
     cout << "----------------------------- \n";
     cout << " constructing matrix with DIM1, DIM2 " << endl;
     Matrix<double> mat1(DIM1, DIM2);
     cout << " checking dimensions of matrix" << endl;
     cout << " DIM1=mat1.size()= " << mat1.size() << endl;
     cout << "----------------------------- \n";
     cout << " DIM2=mat1[0].size()= " << mat1[0].size() << endl;
     cout << "----------------------------- \n";
     cout << " read in matrix mat1 " << endl;
     cout << "----------------------------- \n";
     for(i=0;i<DIM1;i++)
	  {
	  str1.ReadFullLine(in);
	  cout << " str1 " << str1 << endl;
	  
	  for(j=0; j<DIM2-1; j++)
	       {
	       str1.IsolateNextWord(word1, ' ');
	       mat1[i][j]=word1.ToFloat(); 
	       };
	  mat1[i][j]=str1.ToFloat(); 
	  }; 
     cout << "----------------------------- \n";
     cout << " now print out matrix mat1 " << endl;
     cout << mat1;
     cout << " end of test" << endl;
     
     return mat1;
     
     
     }
 
/*F vec = ReadInVector(in)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static vector<double> ReadInVector(istream & in)

     {
     int i;
     
     int N;      
     double x;
     
     
     in>>N;
     cout << " dimension N  = " << N << endl; 
     vector<double> temp(N, Zero(x));
     cout << " dimension of constructed vector " << temp.size() << endl;
     
     
     for(i=0;i<N;i++)
	  in>>temp[i];
     
     cout << " dimension of vector after initiation " << temp.size() << endl;
     
     cout << " ------------------- " << endl;
     
     for(i=0;i<N;i++) 
	  cout << "temp[" << i << "]=" << temp[i] << endl;
     
     cout << " ------------------- " << endl;
     
     return temp;
     
     
     }
 
/*F ReadAndTranspose(in)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/	
static void ReadAndTranspose(istream& in)
     {
     
     cout << " ----------------------------\n ";
     cout << " test for transpose " << " \n";
     Matrix<double> a=ReadInMatrix(in);
     
     Matrix<double> tr_a=a.transpose();
     cout << " transposed " << endl;
     cout << tr_a;
     cout << " ----------------------------\n ";
     Matrix<double> res1=tr_a*a;
     cout << " transpose*original " << endl;
     cout << res1;
     cout << " ----------------------------\n ";
     Matrix<double> res2=a*tr_a;
     cout << " original*transpose " << endl;
     cout << res2;
     
     }

 
/*F PrintOutVector(Vec)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void PrintOutVector(vector<double> Vec)
     { 
     unsigned int i;
     
     for(i=0; i<=Vec.size()-1; i++)     
	  cout << "Vec[" << i << "]= " << Vec[i] << endl;
     
     }
 
 
/*F
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
static void CloneTest(istream& in)
{
  cout << "Clone Test\n";
  
  Matrix<double> mat = ReadInMatrix(in);
  cout << mat;
  
  Matrix<double> *cpy = mat.Clone();
  cout << *cpy;
}
