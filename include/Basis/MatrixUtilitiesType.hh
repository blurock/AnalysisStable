/*  FILE     MatrixUtilitiesType.hh
**  PACKAGE  MatrixUtilities
**
**  CONTENT
**    Definitions for the "Matrix" package.
**
**  OVERVIEW
**    Class MatrixNumeric is designed to perform
**    some typical operations with matrices
**    Each matrix is represented as a set
**    (namely Vector) of  Vectors (rows), 
**    which in turn, contain the elements
**    of type double
**    Class uses data type VectorNumeric
**
**    
**  REFERENCES
**
*/
#ifndef BASIS_MATRIXUTILITIESTYPE_HH
#define BASIS_MATRIXUTILITIESTYPE_HH

/*C MatrixUtilities
**
**  DESCRIPTION
**    This class implements some basic matrix utilities
**	  
**  REMARKS
**
*/
class MatrixUtilities : public MatrixNumeric
{

public:
  // Constructors
       MatrixUtilities();
  MatrixUtilities(int dim1, int dim2);
  MatrixUtilities(const MatrixUtilities& numUtil);
  // Conversion
       MatrixUtilities(const MatrixNumeric& mat)
       : MatrixNumeric(mat)
    {
    }

  // Utilities Functions
       double determinant(MatrixNumeric& A, VectorNumeric& c, int n);
  void order_rows(MatrixNumeric& A, Vector<int>& order, VectorNumeric& scale, unsigned int z);
  void pivot(MatrixNumeric& A, Vector<int>& order, VectorNumeric& scale, 
	     unsigned int z, unsigned int k);
  void eliminate(MatrixNumeric& A, VectorNumeric& c,	Vector<int>& order, 
		 VectorNumeric& scale, unsigned int z);
  void eliminate_invert(MatrixNumeric& A, MatrixNumeric& INVERT, VectorNumeric& c, 
			Vector<int>& order, VectorNumeric& scale, unsigned int z);
  void pivot_and_count(MatrixNumeric& A, Vector<int>& order, VectorNumeric& scale,
		       unsigned int z, unsigned int k, int& count1);
  void eliminate_gauss(MatrixNumeric& A, VectorNumeric& c, Vector<int>& order, 
		       VectorNumeric& scale, int z, int& count1);
  void gauss_jordan_invert(MatrixNumeric& A, MatrixNumeric& INVERT, VectorNumeric& c, int n);
  void gauss_jordan(MatrixNumeric& A, VectorNumeric& c, int n);

};	// class MatrixUtilities

/*C BaseLeastSquares  . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    Class BaseLeastSquares provides base class facilities.
**  Its pure virtual function UserFitFunction is a subject to change
**  in the inheriting classes. Routine Calculate provides least squares 
**  fitting procedure for user designed fit function. User fit function
**  should be a linear combination of user-chosen basic functions. 
**
**  REMARKS
**
*/
class BaseLeastSquares
     {
 protected:
     int PolyProdNumber;
     
   
 public:
     
       BaseLeastSquares();
       BaseLeastSquares(int N);
       virtual ~BaseLeastSquares() {}

     virtual void UserFitFunction(const double& x, VectorNumeric& basis_values)=0;
     
     void Calculate(VectorNumeric x_exp, VectorNumeric y_exp, VectorNumeric& sigmas, VectorNumeric& params);
     
     };
/*C PolyLeastSquares  . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    Class PolyLeastSquares inherits base class BaseLeastSquares.
**  UserFitFunction of this class is the sum of power products
**  over x. 
**
**  REMARKS
**
*/
class PolyLeastSquares : public BaseLeastSquares
     {
     
 public:
     
     PolyLeastSquares();
     PolyLeastSquares(int N);
     void UserFitFunction(const double& x, VectorNumeric& basis_values);
     
     };
/*C LogLeastSquares . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    Class PolyLeastSquares inherits base class BaseLeastSquares.
**  UserFitFunction is a0+a1*ln(1+x)+a2*x (a0-a2 coefficients to find).
**
**  REMARKS
**
*/
class LogLeastSquares : public BaseLeastSquares
     {
     
 public:
     
       LogLeastSquares();
     LogLeastSquares(int N);
     void UserFitFunction(const double& x, VectorNumeric& basis_values);
     
     };
/*C Coefficients  . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    Container class for coefficients stored in form 
**    of vector.
**
**  REMARKS
**
*/
class Coefficients : public VectorNumeric
     {
     
 public:
     
       Coefficients();
       Coefficients(int N);
       virtual ~Coefficients(){};
       virtual void CopyClone(Identify *coeffs);
     virtual Coefficients *Clone();
     virtual ostream& print(ostream& out) const;
     virtual bool EncodeThis(CommBuffer& buffer);
     virtual bool DecodeThis(CommBuffer& buffer);
     };


#endif
