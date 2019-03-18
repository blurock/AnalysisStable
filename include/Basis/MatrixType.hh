/*  FILE     MatrixType.hh
**  PACKAGE  Matrix
**  AUTHOR   Yuri Tsybukh, extensively modified by Edward S. Blurock
**
**  CONTENT
**    Definitions for the "Matrix" package.
**
**  OVERVIEW
**    Class Matrix<T> is designed to perform
**    some typical operations with matrices
**    Each matrix is represented as a set
**    (namely vector) of  vectors (rows), 
**    which in turn, contain the elements
**    of type T
**    Class uses data type vector<T>, which
**    is available by STL 
**    "Pure" vectors can, thus, be represented 
**    as objects of type vector<T>, or, 
**    alternatively as a 1xn Matrix<T>
**    For the first case, the  basic vector 
**    operations are provided
**
**  IMPLEMENTATION
**    implementation remarks
**    
**  REFERENCES
**
**  COPYRIGHT (C) 1996 Reaction, Edward S. Blurock
*/
/*C Matrix<T> . . . . . . . . . . . . . . . . . . Matrix related operations. 
**
**  DESCRIPTION
**    This class implements some basic matrix
**    operations and some linear algebra 
**    algorithms.
**        
**  REMARKS
**
*/
template<class T>
class Matrix : public vector< vector <T> >
{
     friend vector<T> operator+(vector<T> Vec1, vector<T> Vec2);
     friend vector<T> operator-(vector<T> Vec1, vector<T> Vec2);
     friend vector<T> operator/(vector<T> Vec, int C);
     friend istream& operator>>(istream& in, vector<T>& Vec);
     friend ostream& operator<<(ostream& out, const vector<T>& Vec);
public:
typedef istream_iterator<T, ptrdiff_t> istream_iterator_T;
     Matrix();
     Matrix(int dim1, int dim2);
     void SetSize(int newDim, int i);
     Matrix(const Matrix<T>& Mat);
     Matrix<T>& operator=(const Matrix<T>& Mat);

     inline vector<T>  GetMatrixColumn(int i);
     inline vector<T>  GetMatrixRow(int i);
     void NormalizeDiagonalElements();
     
     friend Matrix<T> operator+(Matrix<T> Mat1, Matrix<T> Mat2 );
     friend Matrix<T> operator-(Matrix<T> Mat1, Matrix<T> Mat2 );
     Matrix<T> transpose();
     friend Matrix<T> operator*(Matrix<T> Mat1, Matrix<T> Mat2);
     friend istream& operator>>(istream& in, Matrix<T>& Mat);
     friend ostream& operator<<(ostream& out, Matrix<T> Mat);
     void CopyClone(Matrix<T> *mat)
	  {
	  *this = *mat;
	  }
     Matrix<T> *Clone()
	  {
	  Matrix<T> *mat = new Matrix<T>(0,0);
	  mat->CopyClone(this);
	  return mat;
	  }
     bool EncodeThis(CommBuffer& buffer)
	  {
	  return Encode(buffer, (vector< vector< T > >&) *this);
	  }
     bool DecodeThis(CommBuffer& buffer)
	  {
	  return Encode(buffer, (vector< vector< T > >&) *this);
	  }
     void order_rows(Matrix<T>& A, vector<int>& Order, vector<T>& Scale, int z );
     void pivot(Matrix<T>& A, vector<int>& Order, vector<T>& Scale, int z, int k );
     void eliminate(Matrix<T>& A, vector<T>& C, vector<int>& Order, vector<T>& Scale, int z);
     void eliminate_invert(Matrix<T>& A, Matrix<T>& INVERT, vector<T>& C, vector<int>& Order,vector<T>& Scale, int z);
     void pivot_and_count(Matrix<T>& A, vector<int>& Order, vector<T>& Scale, int z, int k, int& count1 );
     void eliminate_gauss(Matrix<T>& A, vector<T>& C, vector<int>& Order, vector<T>& Scale, int z, int& count1);
     T determinant(Matrix<T>& A, vector<T>& C, int N);
     void gauss_jordan_invert(Matrix<T>& A, Matrix<T>& INVERT, vector<T>& C, int N);
     void gauss_jordan(Matrix<T>& A, vector<T>& C, int N);
     void jacobi(Matrix<T>& a, vector<T>& d, Matrix<T>& v, int& nrot);
     };
class PCAAnalysis; 
/*C EigenVectors  . . . . . . . . . . . . . .  set of eigenvalues and vectors
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
class EigenVectors
     {
     Matrix<double> Eigenvectors;
     vector<double> Eigenvalues;
     double Cutoff;
     bool Filter;
     
     void SortEigenVectors(vector<double>& evalues,
			   Matrix<double>& evectors);
 public:
     EigenVectors();
     EigenVectors(const EigenVectors& mat);
     EigenVectors(Matrix<double> mat, 
		  const bool norm,
		  const bool filter);

     void CopyClone(EigenVectors *mat);
     EigenVectors *Clone();
     ostream& print(ostream& out) const;
     bool EncodeThis(CommBuffer& buffer);
     bool DecodeThis(CommBuffer& buffer);
     void ChangeCutoff(const double cutoff);
     void ChangeFilter(const bool filter);
     
     vector<double> TransformCoordinates(vector<double>& vec);
     ostream& EigenvaluesAsLaTeX(ostream& out, const ObjectList<String>& names) const;
     ostream& EigenvectorsAsLaTeX(ostream& out, const ObjectList<String>& names) const;
     
     friend bool Encode(CommBuffer& buffer, Matrix<double>& mat);
     friend bool Decode(CommBuffer& buffer, Matrix<double>& mat);
     friend class PCAAnalysis;
     };
/*C PCAAnalysis . . . . . . . . . . . . . . . .  Principle Component Analysis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class PCAAnalysis : public EigenVectors
     {
     Matrix<double> Transformed;
     Matrix<double> CorrelationMatrix;
     
 public:
     PCAAnalysis();
     PCAAnalysis(const PCAAnalysis& analysis);
     PCAAnalysis(Matrix<double>& mat);
     
     void CopyClone(PCAAnalysis *pca);
     PCAAnalysis *Clone();
     ostream& print(ostream& out) const;
     
     Matrix<double> GetTransformedCoordinates();
     
     bool EncodeThis(CommBuffer& buffer);
     bool DecodeThis(CommBuffer& buffer);
     friend class EigenVectors;
     };
/*C BasicLaTexTable
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class BasicLaTeXTable
{
  bool Figure;
  bool Rotated;
  
  bool NameColumn;
  unsigned int Justification;
  unsigned int NumberOfColumns;
  String Caption;
  String Label;
  
  unsigned int LineCount;
  unsigned int MaxLines;
  
public:
  BasicLaTeXTable(const bool figure,
		  const bool rot,
		  const bool name,
		  const unsigned int just,
		  const unsigned int numcols,
		  const String& caption,
		  const String& label);
  BasicLaTeXTable(const unsigned int numcols,
		  const String& caption,
		  const String& label);
  
  ostream& PrintHeading(ostream& out);
  ostream& PrintTrailer(ostream& out);
  ostream& PrintTableBodyLine(ostream& out);
  ostream& PrintTableBodyNLines(ostream& out, unsigned int count);
  
  virtual ostream& PrintTitles(ostream& out)
    {
      return out;
    }
  
  virtual ostream& PrintTableLine(ostream& out)
    {
      return out;
    }
  
  
};
/*C LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    mat: The matrix
**    names: The names of the rows
**    part: The number of columns in a data row
**    fsize: The size of the element
**    out: The output stream
**
**  REMARKS
**
*/
template <class T>
class LaTeXMatrixOutBlock : public BasicLaTeXTable
{
  const Matrix<T>& Mat;
  const ObjectList<String>& Rows;
  const ObjectList<String>& Points;
  unsigned int ColStart;
  unsigned int ColEnd;
  ObjectList<String>::const_iterator Name;
  unsigned int FSize;
  unsigned int Prec;
  ObjectList<String>::const_iterator Pnt;
  unsigned int x;
  
public:
  LaTeXMatrixOutBlock(const String& caption,
		      const String& label,
		      const Matrix<T>& mat,
		      const ObjectList<String>& rows,
		      const ObjectList<String>& points,
		      const unsigned int colstart,
		      const unsigned int colend,
		      const unsigned int fsize,
		      const unsigned int prec);
  ostream& PrintTitles(ostream& out);
  ostream& PrintTableLine(ostream& out);
  ostream& PrintTable(ostream& out);
  
};
/*C LaTeXMatrixOutSelect
**
**  DESCRIPTION
**    mat: The matrix
**    names: The names of the rows
**    part: The number of columns in a data row
**    fsize: The size of the element
**    out: The output stream
**
**  REMARKS
**
*/
template <class T>
class LaTeXMatrixOutSelect : public BasicLaTeXTable
{
  const Matrix<T>& Mat;
  const ObjectList<T>& Select;
  const ObjectList<T>& Dependencies;
  const ObjectList<String>& Names;
  unsigned int FSize;
  unsigned int Prec;
  ObjectList<String>::const_iterator Name;
  unsigned int x;
  
public:
  LaTeXMatrixOutSelect(const String& caption,
		       const String& label,
		       const Matrix<T>& mat,
		       const ObjectList<String>& names,
		       const ObjectList<T>& select,
		       const ObjectList<T>& dependencies,
		       const unsigned int fsize,
		       const unsigned int prec);
  ostream& PrintTitles(ostream& out);
  ostream& PrintTableLine(ostream& out);
  ostream& PrintTable(ostream& out);
  
};
