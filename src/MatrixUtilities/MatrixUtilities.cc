/*  FILE     MatrixUtilities.cpp
**  PACKAGE  MatrixUtilities    
**
**  CONTENT
**    
**
**  REFERENCES
**
*/
#define TEMPLATE_INSTANTIATION
#include "defines.hh"
#include "BasisSystem.hh"

#include "CommBuffer.hh"
#include "String.hh"
#include "Objects.hh"
#include "MixedClasses.hh"
#include "Vector.hh"
#include "MatrixNumeric.hh"

#include "MatrixUtilities.hh"

template class Vector<double>;

/*S EncodeDecode
*/
/*S EncodeDecode
*/
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . .  Coefficients
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool Coefficients::EncodeThis(CommBuffer& buffer)
     {
     return Encode(buffer,(VectorNumeric&) *this);
     }
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . .  Coefficients
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool Coefficients::DecodeThis(CommBuffer& buffer)
     {
     return Decode(buffer,(VectorNumeric&) *this);
     }
/*F Coefficients()  . . . . . . . . . . Class Coefficients empty constructor.
**
**  DESCRIPTION
**    Empty constructor.
**    
**  REMARKS
**
*/
inline Coefficients::Coefficients()
     {
     }
/*F Coefficients(N) . . . . . . . . . . . . . Class Coefficients constructor.
**
**  DESCRIPTION
**    N: param.
**
**    Class coefficients constructor. Constructs vector of size N.
**    
**  REMARKS
**
*/
Coefficients::Coefficients(int N) : VectorNumeric (N)
     {
     }
/*F c = SolveLinearSystemOfEquations(mat,vec) . . . . . . . solve vec = c*mat
**
**  DESCRIPTION
**    mat: The matrix of know xs
**    vec: The vector of know ys
**    c: The final coefficient matrix
**
**    - vec_m    (1,n) : ys as row
**    - t_vec_m  (n,1) : ys as column
**    - mat      (n,m) : each row is an equation
**    - t_mat    (m,n) : each column is an equation
**    - alpha    (m,m) : correlation matrix
**    - beta     (n,n) : pairwise ys
**    - vec_beta (1,n) : column of beta
**    
**  REMARKS
**
*/
VectorNumeric SolveLinearSystemOfEquations(MatrixNumeric& mat, 
					   VectorNumeric& vec)
{
  MatrixNumeric t_mat = mat.transpose();
  MatrixNumeric alpha = t_mat * mat;

  MatrixNumeric vec_m(1,vec.size());
  copy(vec.begin(),vec.end(),vec_m[0].begin());
  MatrixNumeric t_vec_m = vec_m.transpose();
  MatrixNumeric beta = t_mat * t_vec_m;
  
  unsigned int nsize = alpha.size();
  MatrixUtilities mutil;
  MatrixNumeric unit(nsize,nsize);
  VectorNumeric c(nsize);
  for(unsigned int j1=0;j1<nsize;j1++)
    {
      for(unsigned int j2=0;j2<nsize;j2++)
	{
	  unit[j1][j2] = 0.0;
	}
      unit[j1][j1] = 1.0;
      c[j1] = 0.0;
    }
  MatrixNumeric alpcopy = alpha;

  mutil.gauss_jordan_invert(alpha,unit,c,nsize);
  cout << "==================================================" << endl;
  alpcopy.print(cout);
  cout << "\n--------------------------------------------------" << endl;
  unit.print(cout);
  cout << "\n--------------------------------------------------" << endl;
  MatrixNumeric u = unit * alpcopy;
  u.print(cout);
  cout << "\n--------------------------------------------------" << endl;

  MatrixNumeric ans1 = unit *  beta;
  VectorNumeric vec_beta(nsize);
  for(unsigned i=0; i<nsize; i++)
    vec_beta[i]=ans1[i][0];

  return vec_beta;
}
/*F Calculate(x_exp, y_exp, sigmas, params) . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    x_exp: param.
**    y_exp: param.
**    sigmas: param.
**    params: param.
**
**    Routine BaseLeastSquares::Calculate(x_exp, y_exp, sigmas, params) 
**    allows to perform linear least squares fit of the experimental data
**    (given in the form : independent  variable x_exp(i); corresponding
**    depending variable y_exp(i) )  and the user defined fit function with
**    the set of parameters, which are calculated by the routine.
**   
**  REMARKS
**
*/  
void BaseLeastSquares::Calculate(VectorNumeric x_exp, VectorNumeric y_exp, VectorNumeric&, VectorNumeric& params)

{ 
 unsigned int i;
 double x;

 MatrixNumeric a(x_exp.size(), params.size());
 VectorNumeric basis_values(params.size(), Zero(x));
 VectorNumeric b(x_exp.size(), Zero(x));
 for(i=0; i<a.size(); i++)
      fill(a[i].begin(), a[i].end(), Zero(x));
 for(i=0; i<a.size(); i++)
      {
      UserFitFunction(x_exp[i], basis_values);
      a[i]= basis_values;
      };
 for(i=0; i<b.size(); i++)
      b[i]=y_exp[i];
 MatrixNumeric b_as_matrix(1, x_exp.size());
 copy(b.begin(), b.end(), b_as_matrix[0].begin());
 MatrixNumeric transpose_a=a.transpose();
 MatrixNumeric alpha = transpose_a*a;
 MatrixNumeric copy_alpha=alpha;
 MatrixNumeric transpose_b_as_matrix = b_as_matrix.transpose();
 MatrixNumeric beta=transpose_a*transpose_b_as_matrix;
 MatrixNumeric transpose_beta = beta.transpose(); 
 VectorNumeric beta_as_vector = transpose_beta[0];
 VectorNumeric copy_beta_as_vector = beta_as_vector;
 MatrixUtilities mutil(alpha);
 mutil.gauss_jordan(alpha, beta_as_vector, params.size());
 params = beta_as_vector;
 }
/*F UserFitFunction(x, basis_values)  . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    x: param.
**    values: param.
** 
**    Routine PolyLeastSquares::UserFitFunction(x, basis_values) calculates power
**    products of polynomial in point x.    
**
**  REMARKS
**
*/          
void PolyLeastSquares::UserFitFunction(const double& x, VectorNumeric& basis_values)
     {
     unsigned int i;
     for(i=0; i<basis_values.size();i++)
	  basis_values[i]=pow(x,(int) i);	   
     
     }
/*F UserFitFunction(x, basis_values)  . . . . . . . . . . . . . . . . . . .  
**
**  DESCRIPTION
**    x: param.
**    values: param.
** 
**    Routine LogLeastSquares::UserFitFunction(x, basis_values) calculates 
**    vector with elements 1, ln(1+x), x.    
**
**  REMARKS
**
*/          
void LogLeastSquares::UserFitFunction(const double& x, VectorNumeric& basis_values)
     {
	        
     basis_values[0]=1.0;
     basis_values[1]=log(1+x);
     basis_values[2]=x;

     }
/*F CopyClone(coeffs) . . . . . . . . . . . . . . . . . . . . .  Coefficients
**
**  DESCRIPTION
**    coeffs: The vector of coefficients
**
**    Copy the contents into the current
**
**  REMARKS
**
*/
void Coefficients::CopyClone(Identify *vecnum)
     {
       Coefficients *coeffs = (Coefficients *) vecnum;
     *this = *coeffs;
     }
/*F Clone() . . . . . . . . . . . . . . . . . . . . . . . . . .  Coefficients
**
**  DESCRIPTION
**    Clone a copy
**
**  REMARKS
**
*/
Coefficients *Coefficients::Clone()
     {
       Coefficients *coeffs = new Coefficients();
     coeffs->CopyClone(this);
     return coeffs;
     }

/*F stream = print(out) . . . . . . . . . . . . . . . . . . . .  Coefficients
**
**  DESCRIPTION
**    out: The output stream
**    stream: The stream after print
**
**  REMARKS
**
*/
ostream& Coefficients::print(ostream& out) const
     {
     out << "Coefficients: ";

     for(unsigned int i=0;i < (*this).size();i++)
       {
	 out << (*this)[i] << " ";
       }
     return out;
     }
/*F BaseLeastSquares()  . . . . . . Class BaseLeastSquares empty constructor.
**
**  DESCRIPTION
**    Empty constructor.
**    
**  REMARKS
**
*/
BaseLeastSquares::BaseLeastSquares()
     {
     }
/*F BaseLeastSquares(N) . . . . . . . . . Class BaseLeastSquares constructor.
**
**  DESCRIPTION
**    N: param.
**
**    Class BaseLeastSquares constructor, which takes as argument integer
**    and uses it to initialize member PolyProdNumber.
**    
**  REMARKS
**
*/
BaseLeastSquares::BaseLeastSquares(int N)
: PolyProdNumber(N)
     {
     }
/*F PolyLeastSquares()  . . . . . . Class PolyLeastSquares empty constructor.
**
**  DESCRIPTION
**    Empty constructor.
**    
**  REMARKS
**
*/
PolyLeastSquares::PolyLeastSquares()
     {
     }
/*F PolyLeastSquares(N) . . . . . . . . . Class PolyLeastSquares constructor.
**
**  DESCRIPTION
**    N: param.
**
**    Class PolyLeastSquares constructor, which takes as argument integer
**    and uses it to initialize member PolyProdNumber of base class BaseLeastSquares.    
**    
**  REMARKS
**
*/
PolyLeastSquares::PolyLeastSquares(int N)
: BaseLeastSquares(N)
     {
     }
/*F LogLeastSquares() . . . . . . .  Class LogLeastSquares empty constructor.
**
**  DESCRIPTION
**    Empty constructor.
**    
**  REMARKS
**
*/
LogLeastSquares::LogLeastSquares()
     {
     }
/*F LogLeastSquares(N)  . . . . . . . . .  Class LogLeastSquares constructor.
**
**  DESCRIPTION
**    N: param.
**
**    Class PolyLeastSquares constructor, which takes as argument integer
**    and uses it to initialize member PolyProdNumber of base class BaseLeastSquares.
**    
**  REMARKS
**
*/
LogLeastSquares::LogLeastSquares(int N)
: BaseLeastSquares(N)
     {
     }



/*S Constructors
*/
/*F MatrixUtilities()  . . . . . . . . . . . . . . . . .  MatrixUtilities empty constructor.
**
**  DESCRIPTION
**    MatrixUtilities empty constuctor.
**    
**  REMARKS
**    
*/
MatrixUtilities::MatrixUtilities()
{
}

/*F MatrixUtilities(dim1, dim2)  . . . . . . . . . . . .  MatrixUtilities  constructor.
**
**  DESCRIPTION
**    dim1,dim2: The dimensions
**
**    Class MatrixUtilities constructor, which
**    takes two arguments - dimensions of 
**    constructed matrix.
**     
**  REMARKS
*/
MatrixUtilities::MatrixUtilities(int dim1, int dim2)
  : MatrixNumeric(dim1, dim2)
{
}

/*F MatrixUtilities(nummat) . . . . . . . . . . . . . . . MatrixUtilities copy constructor.
**
**  DESCRIPTION
**    Mat: to be copied
** 
**    MatrixNumeric copy constructor.
**    It is invoked when existing object 
**    of type MatrixNumeric is assigned to 
**    new ( previously  undeclared ) object 
**    of type MatrixNumeric. 
**    Declaration of new object should
**    not contain any constructor parameters.
**    The Proper dimensions of new object are set 
**    automatically. Syntax: MatrixNumeric Mat2 = Mat1.
**
**  REMARKS 
**    This kind of assignment should be used
**    when construction of object of type
**    Matrix<T> with explicitly passed dimensions
**    is not desirable.
**  
*/
MatrixUtilities::MatrixUtilities(const MatrixUtilities& matUtil) 
  : MatrixNumeric(matUtil)
{
}

/*F d = determinant(A, C, N)  . . . . . . . . . . . . . . . . The determinant
**
**  DESCRIPTION
**    A: param.
**    C: param.
**    N: param.
**    d: The determinant
**
**    Routine determinant(A,C,N) calculates matrix determinant
**    using Gauss elimination scheme. 
**  
**  REMARKS
**
*/
double MatrixUtilities::determinant(MatrixNumeric& A, 
                                    VectorNumeric& c, 
                                    int n)
{
  double x;
  Vector<int> order(n);
  VectorNumeric scale(n, Zero(x));
  int z = n - 1;
  int count1;

  double determinant_value = Unit(x);
  double factor;
        
  count1 = 1;

  order_rows(A, order, scale, z);      
  eliminate_gauss(A, c, order, scale, z, count1);
        
  factor = -Unit(x);
  for (int k=0; k<=z; k++)
    determinant_value*=A[k][k];
           
  cout << " count1 = " << count1 << " \n";
  determinant_value*=count1;
           
  return determinant_value;
}         

/*F order_rows(A, order, scale, z)  . . . . . . . . . . . . . vector ordering
**
**  DESCRIPTION
**    A: param.
**    order: param.
**    scale: param.
**    z: param.
**
**    order_rows(A, order, scale, z) is basic routine, used by the 
**    subsequent ones. Creats ordering vector,
**    which then allows to keep track of the
**    correct ordering of matrix rows.
**    Creates also scaling vector, which is used
**    to determine, whether pivoting is necessary.
**    
**  REMARKS
**
*/
void MatrixUtilities::order_rows(MatrixNumeric& A, 
                                 Vector<int>& order, 
                                 VectorNumeric& scale, 
                                 unsigned int z)
{
  unsigned int i;
  double x;

  VectorNumeric temp(z+1, Zero(x)); 

  for(i=0; i<=z; i++)
    {
      order[i] = i;
      //transform(A[i].begin(), A[i].end(), temp.begin(), fabs);
      vector<double> v = A[i];
      //vector<double> temp1 = temp1;
      //transform(v.begin(), v.end(), temp1.begin(), fabs);
      vector<double>::iterator j;
      vector<double>::iterator t = temp.begin();
      for(j=v.begin();j!=v.end();j++) {
	*t++ = fabs(*j);
      }
      scale[i]=*max_element(temp.begin(), temp.end());
    }
}


/*F MatrixUtilities::pivot(A, order, scale, z, k) . . . . . . . . . . . . . . Pivot
**
**  DESCRIPTION
**    A:                The matrix
**    order:    param
**    scale:    param.
**    z:                param.
**    k:                param.
**  
**    Routine pivot(A, order, scale, z, k) provides partial
**    pivoting of system of linear equations,
**    i.e. row interchanging.
**    Alters the content of ordering vector,
**    while the rows are not actually interchanged.
**     
**  REMARKS
**
*/
void MatrixUtilities::pivot(MatrixNumeric& A, 
                            Vector<int>& order, 
                            VectorNumeric& scale, 
                            unsigned int z, 
                            unsigned int k)
{
  unsigned int i;
  unsigned int last = z; 
  unsigned int pivot, index_dummy;
  double big, dummy;

  pivot = k;
  big = fabs(A[order[k]][k]/scale[order[k]]);
  for ( i = k+1; i<= last; i++)
    {
      dummy =  fabs(A[order[i]][k]/scale[order[i]]);
      if (dummy > big)
        {
          big = dummy;
          pivot = i;
        }
    }
        
  index_dummy = order[pivot];
  order[pivot] = order[k];
  order[k] = index_dummy;
}

/*F eliminate(A, c, order, scale, z)  . . . . . . .  Gauss-Jordan Elimination
**
**  DESCRIPTION
**    A:                param.
**    c:                param.
**    order:    param.
**    scale:    param.
**    z:                param.
**
**    Routine eliminate(A, c, order, scale, z) implements
**    Gauss-Jordan elimination with partial pivoting
**    for solving system of linear equations.
**    Changed right-hand-side vector represents solution.
**     
**  REMARKS
**
*/
void MatrixUtilities::eliminate(MatrixNumeric& A, 
                                VectorNumeric& c, 
                                Vector<int>& order, 
                                VectorNumeric& scale, 
                                unsigned int z)
{
  unsigned int i,k;
  double factor, dummy_factor;
  double x;

  VectorNumeric temp(z+1, Zero(x));
  VectorNumeric temp_Copy_C(z+1, Zero(x));

  MatrixNumeric temp_Copy_A(z+1, z+1);

  for(k=0; k<=z; k++)
    {
      pivot(A,order,scale,z,k);
      dummy_factor = 1.0/A[order[k]][k];

      transform(A[order[k]].begin(), 
		A[order[k]].end(), 
		A[order[k]].begin(), 
		bind2nd(multiplies<double>(), dummy_factor));

      c[order[k]] = c[order[k]]*dummy_factor; 

      for(i=0; i<=z; i++)
        {
          if (i!=k)
            {
              factor = A[order[i]][k];
              //                  for(j=0; j<=z; j++)
                //                        A[order[i]][j] = A[order[i]][j]-factor*A[order[k]][j];
              transform(A[order[k]].begin(), 
			A[order[k]].end(), 
			temp.begin(), 
			bind2nd(multiplies<double>(), factor));
              transform(A[order[i]].begin(), 
			A[order[i]].end(), 
			temp.begin(), 
			A[order[i]].begin(), 
			minus<double>());
              fill_n(temp.begin(), temp.size(), Zero(x)); 

              c[order[i]] = c[order[i]] - factor*c[order[k]];
            }
        }

      // Restores the correct order of solutions for output
        for(i=0; i<=z; i++) 
          temp_Copy_C[i] = c[order[i]];
      for(i=0; i<=z; i++) 
        c[i] = temp_Copy_C[i];
      for(i=0; i<=z; i++)           
        copy(A[order[i]].begin(), A[order[i]].end(), temp_Copy_A[i].begin());
      for(i=0; i<=z; i++)
        copy(temp_Copy_A[i].begin(), temp_Copy_A[i].end(), A[i].begin());
    }
}

/*F eliminate_invert(A, INVERT, c, order, scale, z) . . . . . . square matrix
**
**  DESCRIPTION
**    A: param.
**    INVERT: param.
**    c: param.
**    order: param.
**    scale: param.
**    z: param.
**    
**    Routine eliminate_invert(A, INVERT, c, order, scale, z) is a modification
**    of routine eliminate. It allows to get the inverse
**    of square matrix, using the same Gauss-Jordan
**    elimination scheme.
**  
**  REMARKS
**
*/
void MatrixUtilities::eliminate_invert(MatrixNumeric& A, 
                                       MatrixNumeric& INVERT, 
                                       VectorNumeric& c, 
                                       Vector<int>& order, 
                                       VectorNumeric& scale, 
                                       unsigned int z)
{
  unsigned int i,k;
  double factor, dummy_factor, x;

  VectorNumeric temp(z+1, Zero(x));
  VectorNumeric temp_Copy_C(z+1, Zero(x));
  MatrixNumeric temp_Copy_A(z+1, z+1);
  MatrixNumeric temp_Copy_INVERT(z+1,z+1);

  for(k=0; k<=z; k++)
    {
      pivot(A,order,scale,z,k);
      dummy_factor = 1.0/A[order[k]][k];

      transform(A[order[k]].begin(), 
		A[order[k]].end(), 
		A[order[k]].begin(), 
		bind2nd(multiplies<double>(), dummy_factor));
      transform(INVERT[order[k]].begin(), 
		INVERT[order[k]].end(), 
		INVERT[order[k]].begin(), 
		bind2nd(multiplies<double>(), dummy_factor));

      c[order[k]] = c[order[k]]*dummy_factor; 

      for(i=0; i<=z; i++)
        {
          if (i!=k)
            {
              factor = A[order[i]][k];
                                
              transform(A[order[k]].begin(), 
			A[order[k]].end(), 
			temp.begin(), 
			bind2nd(multiplies<double>(), factor));
              transform(A[order[i]].begin(), 
			A[order[i]].end(), 
			temp.begin(), 
			A[order[i]].begin(), 
			minus<double>());
              fill_n(temp.begin(), temp.size(), Zero(x)); 
              transform(INVERT[order[k]].begin(), 
			INVERT[order[k]].end(), 
			temp.begin(), 
			bind2nd(multiplies<double>(), factor));
              transform(INVERT[order[i]].begin(), 
			INVERT[order[i]].end(), 
			temp.begin(), 
			INVERT[order[i]].begin(), minus<double>());
              fill_n(temp.begin(), temp.size(), Zero(x)); 

              c[order[i]] = c[order[i]] - factor*c[order[k]];
            }
        }
    }

  for(i=0; i<=z; i++) 
    temp_Copy_C[i] = c[order[i]];
  for(i=0; i<=z; i++) 
    c[i] = temp_Copy_C[i];

  for(i=0; i<=z; i++)
    copy(A[order[i]].begin(), A[order[i]].end(), temp_Copy_A[i].begin());
  for(i=0; i<=z; i++)
    copy(temp_Copy_A[i].begin(), temp_Copy_A[i].end(), A[i].begin());

  for(i=0; i<=z; i++)
    copy(INVERT[order[i]].begin(), INVERT[order[i]].end(), temp_Copy_INVERT[i].begin());
  for(i=0; i<=z; i++)
    copy(temp_Copy_INVERT[i].begin(), temp_Copy_INVERT[i].end(), INVERT[i].begin());
}

/*F pivot_and_count(A, order, scale, z, k, count1)  . .  keep track of pivots
**
**  DESCRIPTION
**    A: param.
**    order: param.
**    scale: param.
**    z: param.
**    k: param.
**    count1: param.
**  
**    Routine pivot_and_count(A, order, scale, z, k, count1) provides partial
**    pivoting and keeps track of the number of 
**    rows interchangings. Is used for calculating 
**    matrix determinant by Gauss elimination scheme.
**
**  
**  REMARKS
**
*/
void MatrixUtilities::pivot_and_count(MatrixNumeric& A, 
                                      Vector<int>& order, 
                                      VectorNumeric& scale, 
                                      unsigned int z, 
                                      unsigned int k, 
                                      int& count1)
{
  unsigned int i;
  unsigned int last = z; 
  unsigned int pivot, index_dummy;
  double big, dummy;
        
  pivot = k;
  big = fabs(A[order[k]][k]/scale[order[k]]);
        
  for ( i = k+1; i<= last; i++)
    {
      dummy =  fabs(A[order[i]][k]/scale[order[i]]);
      if (dummy > big)
        {
          big = dummy;
          pivot = i;
        }
    }

  if (pivot!=k)
    count1=count1*(-1);
        
  index_dummy = order[pivot];
  order[pivot] = order[k];
  order[k] = index_dummy;
}

/*F eliminate_gauss(A, c, order, scale, z, count1)  . . . .  partial pivoting
**
**  DESCRIPTION
**    A: param.
**    c: param.
**    order: param.
**    scale: param.
**    z: param.
**    count1: param.
**  
**    Routine eliminate_gauss(A, c, order, scale, z, count1) implements
**    Gauss elimination with partial pivoting
**    for solving system of linear equations.
**    Algorithm provides possibility to calculate
**    the determinant of matrix.
**       
**  REMARKS
**
**    Subsequent back substitution routine is 
**    needed for retrieving the vector of solutions
**
*/
void MatrixUtilities::eliminate_gauss(MatrixNumeric& A, 
                                      VectorNumeric& c, 
                                      Vector<int>& order, 
                                      VectorNumeric& scale, 
                                      int z, 
                                      int& count1)
{
  int i,k;
  double factor, x;
  VectorNumeric temp(z+1, Zero(x));
  MatrixNumeric temp_Copy_A(z+1, z+1);
        
  for(k=0; k<=z-1; k++)
    {
      pivot_and_count(A,order,scale,z,k,count1);
      for(i=k+1; i<=z; i++)
        {
          factor = A[order[i]][k]/A[order[k]][k];

          transform(A[order[k]].begin()+k, 
		    A[order[k]].end(), 
		    temp.begin(), 
		    bind2nd(multiplies<double>(), factor));
          transform(A[order[i]].begin()+k, 
		    A[order[i]].end(), 
		    temp.begin(), 
		    A[order[i]].begin(), 
		    minus<double>());
          //             for(j=k+1; j<=z; j++)
            //                   A[order[i]][j] = A[order[i]][j]-factor*A[order[k]][j];
          c[order[i]] = c[order[i]] - factor*c[order[k]];
        };
    }

  for(i=0; i<=z; i++)           
    copy(A[order[i]].begin(), A[order[i]].end(), temp_Copy_A[i].begin());            
        
  for(i=0; i<=z; i++)           
    copy(temp_Copy_A[i].begin(), temp_Copy_A[i].end(), A[i].begin());
}

/*F gauss_jordan_invert(A, INVERT, c, n)  . . . . . . . . . . . . . . inverse
**
**  DESCRIPTION
**    A: param.
**    INVERT: param.
**    c: param.
**    n: param.
**
**    Routine gauss_jordan_invert(A, INVERT, c, n) calculates
**    inverse matrix. On input the INVERT matrix
**    have to be initiated to identity matrix.
**  
**  REMARKS
**
*/
void MatrixUtilities::gauss_jordan_invert(MatrixNumeric& A, 
                                          MatrixNumeric& INVERT, 
                                          VectorNumeric& c, 
                                          int n)
{
  double x;
  Vector<int> order(n);
  VectorNumeric scale(n, Zero(x));
  int z = n - 1;
  order_rows(A, order, scale, z);      
  eliminate_invert( A, INVERT, c, order, scale, z);
}

/*F gauss_jordan(A, c, n) . . . . . . . . . . . . . .  solve linear equations
**
**  DESCRIPTION
**    A: param.
**    c: param.
**    n: param.
**   
**    Routine gauss_jordan(A,c,n) solves system
**    of linear equations.
**  
**  REMARKS
**    The input right-hand-side vector c is changed
**    by routine, it represents the solution.
*/
void MatrixUtilities::gauss_jordan(MatrixNumeric& A, 
                                   VectorNumeric& c, 
                                   int n)
{          
  double x;
  Vector<int> order(n);
  VectorNumeric scale(n, Zero(x));
  int z = n - 1;
                        
  order_rows(A, order, scale, z);      
  eliminate( A, c, order, scale, z);
}

/*F jacobi(a, n, d, v, nrot)  . . . . . . . . . . . . eigenvalues and vectors
**
**  DESCRIPTION
**    a: The matrix of values (it is assumed that it is square and symmetric)
**    d: The resulting eigenvalues (should be dimensioned beforehand)
**    v: The resulting set of eigenvectors (should be dimensioned beforehand)
**    nrot: param.
**
**    Routine jacobi(a, n, d, v, nrot)
**    Computes all eigenvalues and eigenvectors of a real symmetric
**    matrix. On output, elements of the input matrix above the 
**    diagonal are destroyed. Matrix v contains eigenvectors as 
**    columns. nrot gives the number of Jacobi rotations that
**    were needed. The eigenvalues are not ordered on output.
**    This is a more or less direct translation of the numerical
**    recipes algorithm.
**      
**  REMARKS
**
*/
void jacobi(MatrixNumeric& a, VectorNumeric& d, MatrixNumeric& v, int& nrot)
{
  int j,iq,ip,i;
  int last;
  double tresh, theta, tau, t, sm, s, h, g, c, x;
  int n = a.size();
  VectorNumeric b(n, Zero(x));
  VectorNumeric z(n, Zero(x));
    
  last = n-1; 
  for (ip=0;ip<=last;ip++) 
    {
      for (iq=0;iq<=last;iq++) 
        v[ip][iq] = Zero(x);
      v[ip][ip] = Unit(x);
    }
  for (ip=0;ip<=last;ip++) 
    {
      b[ip]=d[ip] = a[ip][ip];
      z[ip]=Zero(x);
    }
  nrot=0;
  for (i=1;i<=110;i++) 
    {
      sm=Zero(x);
      for (ip=0;ip<=last-1;ip++) 
        {
          for (iq=ip+1;iq<=last;iq++)
            sm += fabs(a[ip][iq]);
        }

      if (sm == Zero(x))
        {
          return;
        }
          
      if (i < 4)
        tresh=0.2*sm/(n*n);
      else
        tresh=Zero(x);
          
      for (ip=0;ip<=last-1;ip++) 
        {
          for (iq=ip+1;iq<=last;iq++) 
            {
              g=100.0*fabs(a[ip][iq]);
                    
              if (i > 4 && fabs(d[ip])+g == fabs(d[ip]) && fabs(d[iq])+g == fabs(d[iq]))
                a[ip][iq]=Zero(x);
              else if (fabs(a[ip][iq]) > tresh) 
                {
                  h=d[iq]-d[ip];
                  if (fabs(h)+g == fabs(h))
                    t=(a[ip][iq])/h;
                  else 
                    {
                      theta=0.5*h/(a[ip][iq]);
                      t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                      if (theta < Zero(x)) 
                        t = -t;
                    }
                  c=1.0/sqrt(1+t*t);
                  s=t*c;
                  tau=s/(1.0+c);
                  h=t*a[ip][iq];
                  z[ip] -= h;
                  z[iq] += h;
                  d[ip] -= h;
                  d[iq] += h;
                  a[ip][iq] = Zero(x);
                         

                  for (j=0;j<=ip-1;j++)
                    { 
                      ROTATE(a,j,ip,j,iq)
                        }
                  for (j=ip+1;j<=iq-1;j++) 
                    {
                      ROTATE(a,ip,j,j,iq)
                        }
                  for (j=iq+1;j<=last;j++) 
                    {
                      ROTATE(a,ip,j,iq,j)
                        }
                  for (j=0;j<=last;j++) 
                    {
                      ROTATE(v,j,ip,j,iq)
                        }

                  ++nrot;
                }
            }
        }
          
      for (ip=0;ip<=last;ip++) 
        {
          b[ip] += z[ip];
          d[ip]=b[ip];
          z[ip]=Zero(x);
        }
    }
  cout << "Too many iterations in routine JACOBI" << " \n";
}
