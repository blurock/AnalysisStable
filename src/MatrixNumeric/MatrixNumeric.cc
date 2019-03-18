/*  FILE     MatrixNumeric.cpp
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
#define TEMPLATE_INSTANTIATION
#include "BasisSystem.hh"
#include "Vector.hh"
#include "MatrixNumeric.hh"

#ifdef _unix
template class vector<VectorNumeric>;
#endif

/*S Constructors
*/
/*F MatrixNumeric()  . . . . . . . . . . . . . . . . .  MatrixNumeric empty constructor.
**
**  DESCRIPTION
**    MatrixNumeric empty constuctor.
**    
**  REMARKS
**    
*/
MatrixNumeric::MatrixNumeric()
{
}

/*F MatrixNumeric(dim1, dim2)  . . . . . . . . . . . .  MatrixNumeric  constructor.
**
**  DESCRIPTION
**    dim1,dim2: The dimensions
**
**    Class MatrixNumeric constructor, which
**    takes two arguments - dimensions of 
**    constructed matrix.
**     
**  REMARKS
**    Parameter dim1 is passed to the constructor
**    of the inherited class Vector<T>.
**    Function setSize provides constructor
**    facilities for each row ( Vector<T> )
**    of matrix.
*/
MatrixNumeric::MatrixNumeric(int dim1, int dim2)
  : VectorFull< VectorNumeric > (dim1)
{
  //     cout << " Superclass Matrix is being constructed\n";
  if (dim1>0)
    {
      for( int i=0; i<dim1; i++)
	{
	  (*this).setSize( dim2, i );
	}
    }
}

/*F MatrixNumeric::CopyClone 
**
**  DESCRIPTION
**    
**  REMARKS
**    
*/
void MatrixNumeric::CopyClone(Identify *vec) {
  MatrixNumeric *numMat = (MatrixNumeric *) vec;
  *this = *numMat;
}

/*F MatrixNumeric::Clone
**
**  DESCRIPTION
**    
**  REMARKS
**    
*/
Vector<class VectorNumeric>* MatrixNumeric::Clone()
{
  MatrixNumeric *numMat = new MatrixNumeric(0,0);
  numMat->CopyClone((Identify *) this);
  return numMat;
}

/*F MatrixNumeric::Read 
**
**  DESCRIPTION
**    
**  REMARKS
**    
*/
bool MatrixNumeric::Read(istream& in)
{
  bool result = true;
  unsigned int dim1, dim2;
  String word;
  StreamObjectInput file(in, ' ');

  word = file.ReadNext();
  dim1 = word.ToInteger();

  word = file.ReadNext();
  dim2 = word.ToInteger();
    
  for (unsigned int i=0; i<dim1; i++)
    {
      VectorNumeric line;
      for (unsigned int j=0; j<dim2; j++)
	{
	  double currentVal;
	  word = file.ReadNext();
	  currentVal = word.ToFloat();
	  line.AddObject(currentVal);
	}
      AddObject(line);
    }

  return result;
}

/*F MatrixNumeric::print 
**
**  DESCRIPTION
**    
**  REMARKS
**    
*/
ostream& MatrixNumeric::print(ostream& out) const
{
  for (unsigned int i=0; i<(*this).size(); i++)
    {
      for (unsigned int j=0; j<(*this)[0].size(); j++)
	out << (*this)[i][j] << " ";
      out << "\n";
    }
  return out;
}

/*F MatrixNumeric::EncodeThis 
**
**  DESCRIPTION
**    
**  REMARKS
**    
*/
bool MatrixNumeric::EncodeThis(CommBuffer& buffer)
{
  unsigned int d1 = (*this).size();
  unsigned int d2;
  if (d1 == 0) // empty matrix
		 d2 = 0;
  else
    d2 = (*this)[0].size();

  bool result = Encode(buffer, d1);
  result = result && Encode(buffer, d2);

  for (unsigned int i = 0; i < d1; i++)
    for (unsigned int j = 0; j < d2; j++)
      result = result && Encode(buffer, (*this)[i][j]);

  return result;
}

/*F MatrixNumeric::DecodeThis 
**
**  DESCRIPTION
**    
**  REMARKS
**    
*/
bool MatrixNumeric::DecodeThis(CommBuffer& buffer)
{
  unsigned int dim1, dim2;
  bool result = Decode(buffer, dim1);
  result = result && Decode(buffer, dim2);

  for (unsigned int i = 0; i < dim1; i++)
    {
      VectorNumeric helpVec;
      for (unsigned int j = 0; j < dim2; j++)
	{
	  double *help = new double;
	  result = result && Decode(buffer, *help);
	  helpVec.AddObject(*help);
	}
      (*this).AddObject(helpVec);
    }
  return result;
}


/*F setSize(newDim,i) . . . . . . . . . . . . . . . . . .  Setting row size. 
**
**  DESCRIPTION
**    newDim, i: param.
**
**    Provides constructor facilities 
**    for matrix row, denoted by index;
**    allows to resize (DimNew>DimOld)
**    object of type vector<T>.
**
**  REMARKS
**
*/
void MatrixNumeric::setSize(int newDim, int i)
{
  double x;
  VectorNumeric temp(newDim, Zero(x)) ;

  int thisSize = (*this)[i].size();
  if ( thisSize < newDim)
    {
      if ((*this)[i].size() != 0) 
	{
	  copy ((*this)[i].begin(),(*this)[i].end(), temp.begin());                 
	}
      (*this)[i]=temp;
    }
  else
    cout << " new dimension is less than old one " <<  " \n ";  
}

/*F MatrixNumeric(nummat) . . . . . . . . . . . . . . . . . MatrixNumeric copy constructor.
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
MatrixNumeric::MatrixNumeric(const MatrixNumeric& numMat) 
  : VectorFull< VectorNumeric >(numMat.size()) 
{
  unsigned int i;
     
  unsigned int matSize = numMat.size();
  for( i=0; i<(*this).size(); i++)
    {
      (*this)[i].erase((*this)[i].begin(),(*this)[i].end());
    }
  (*this).erase((*this).begin(),(*this).end());

  for( i=0; i<matSize; i++)
    {
      push_back(numMat[i]);
    }
}


/*S  Some basic matrix operations
*/ 
/*F getMatrixColumn(i)  . . . . . . . . . . . . . . .  Returns matrix column.
**
**  DESCRIPTION
**    i: the column index
**   
**    Matrix column is returned in the form of vector<T>.
**    
**  REMARKS
**
*/
VectorNumeric MatrixNumeric::getMatrixColumn(int i)
{
  double x;
  VectorNumeric temp(size(), Zero(x));
  transform(begin(),end(), temp.begin(), bind2nd(getVectorElement<double>(), i));
  return temp;
}


/*F getMatrixRow(i) . . . . . . . . . . . . . . . . . . . Returns matrix row.
**
**  DESCRIPTION
**    i:  the row index
**
**    Matrix row is returned in the form of vector<T>.
**    
**  REMARKS
**
*/
VectorNumeric MatrixNumeric::getMatrixRow(int i)
{
  double x;
  VectorNumeric temp((*this)[0].size(), Zero(x));
  copy((*this)[i].begin(), (*this)[i].end(), temp.begin());
  return temp;
}


/*F mat = transpose() . . . . . . . . . . . . . . . . . Matrix transposition.
**
**  DESCRIPTION
**    mat: The transpose of the matrix
**
**    Matrix is transposed; transposed matrix is returned.
**    
**  REMARKS
**
*/
MatrixNumeric MatrixNumeric::transpose()
{
  MatrixNumeric temp((*this)[0].size(),size());
  unsigned int vecSize = (*this)[0].size();
  for(unsigned int i = 0; i < vecSize; i++)
    temp[i] = getMatrixColumn(i);
  return temp;
}
/*F mat = transpose() . . . . . . . . . . . . . . . . . Matrix transposition.
**
**  DESCRIPTION
**    mat: The transpose of the matrix
**
**    Matrix is transposed; transposed matrix is returned.
**    
**  REMARKS
**
*/
void MatrixNumeric::transpose(MatrixNumeric &temp)
{
  unsigned int vecSize = (*this)[0].size();
  for(unsigned int i = 0; i < vecSize; i++)
    temp[i] = getMatrixColumn(i);
}


/*F normalizeDiagonalElements() . . . . . . . . . . . . . . . . . . .  MatrixNumeric
**
**  DESCRIPTION
**    The elements of the square matrix (an error is given if not) are 
**    divided by the diagonal elements m[ij] = m[ij]/ (m[ii]m[jj]).
**
**  REMARKS
**
*/
void MatrixNumeric::normalizeDiagonalElements()
{
  unsigned int dim1 = size();
  unsigned int dim2 = (*this)[0].size();
  
  if(dim1 == dim2)
    {
      VectorNumeric/*whchange*/ norm(dim1);
      double fdim = (double) dim1;
      
      for(unsigned int i=0;i!=dim1;i++)
	norm[i] = sqrt((double) (*this)[i][i]*fdim);
      
      for(unsigned ii=0;ii != dim1;ii++)
	for(unsigned int j=0;j!= dim1;j++)
	  (*this)[ii][j] = (*this)[ii][j]/(norm[ii]*norm[j]);
    }
  else
    cout << "Cannot normalize Non-square matrix\n";
}


/*S Some basic matrix operations 
*/

/*F mat = operator+(mat1, mat2) . . . . . . . . . . . . . .  Matrix addition.
**
**  DESCRIPTION
**    this plus mat2
**
**    Adds two matrices. Returns result as matrix.   
**
**  REMARKS
**
*/
MatrixNumeric MatrixNumeric::operator+(MatrixNumeric mat2)
{
  if ( (*this).size() == mat2.size() && (*this)[0].size() == mat2[0].size())
    {
      MatrixNumeric tempMat((*this).size(), (*this)[0].size());
      for (unsigned int i=0; i<(*this).size(); i++)
	for (unsigned int j=0; j<(*this)[0].size(); j++)
	  tempMat[i][j] = (*this)[i][j] + mat2[i][j];
      return tempMat;
    }
  cerr << " Dimensions are improper (operater+)\n";
  cerr << "(" << (*this).size() << ", " << (*this)[0].size() << ")  ";
  cerr << "(" << mat2.size() << ", " << mat2[0].size() << ")  " <<endl;

  return (*this); 
}

 
/*F mat = operator-(mat1, mat2) . . . . . . . . . . . . . Matrix subtraction.
**
**  DESCRIPTION
**    mat1: param.
**    mat: (*this) minus mat2
**
**    Subtracts two matrices. Returns result as matrix.   
**
**  REMARKS
**
*/
MatrixNumeric MatrixNumeric::operator-(MatrixNumeric mat2)
{
  if ( (*this).size()==mat2.size() && (*this)[0].size()==mat2[0].size())
    {
      MatrixNumeric tempMat((*this).size(), (*this)[0].size());
      for (unsigned int i=0; i<(*this).size(); i++)
	for (unsigned int j=0; j<(*this)[0].size(); j++)
	  tempMat[i][j] = (*this)[i][j] - mat2[i][j];
      return tempMat;
    }
  cerr << " Dimensions are improper (operator-) \n";
  cerr << "(" << (*this).size() << ", " << (*this)[0].size() << ")  ";
  cerr << "(" << mat2.size() << ", " << mat2[0].size() << ")  " <<endl;

  return (*this);
}

 
/*F mat = operator*(mat1, mat2) . . . . . . . . . . .  matrix multiplication.
**
**  DESCRIPTION
**    mat2: param.
**    mat: this times mat2
**
**    Multiplies two matrices. Returns result as matrix.   
**
**  REMARKS
**
*/
MatrixNumeric MatrixNumeric::operator*(MatrixNumeric mat2)
{
  if ((*this)[0].size() == mat2.size())
    {
      MatrixNumeric temp((*this).size(), mat2[0].size());
      MatrixNumeric mat2Transpose = mat2.transpose();

      for(unsigned int i=0; i<(*this).size(); i++)
	transform(mat2Transpose.begin(), mat2Transpose.end(), temp[i].begin(), bind2nd(dotProduct<double>(), (*this)[i]));
      return temp;
    }
  cerr << " Dimensions are improper (operator*) \n";
  cerr << "(" << (*this).size() << ", " << (*this)[0].size() << ")  ";
  cerr << "(" << mat2.size() << ", " << mat2[0].size() << ")  " <<endl;

  return (*this);
}


/*F mat = operator*(mat, c) . . . . . . . . . . .  matrix multiplied with constant.
**
**  DESCRIPTION
**    c:	constant.
**
**    Multiplies a matrix with a constant. Returns result as matrix.   
**
**  REMARKS
**
*/
MatrixNumeric MatrixNumeric::operator*(double c)
{
  MatrixNumeric tempMat((*this).size(), (*this)[0].size());

  for (unsigned int i=0; i<(*this).size(); i++)
    for (unsigned int j=0; j<(*this)[0].size(); j++)
      tempMat[i][j] = c * (*this)[i][j];

  return tempMat;
}
