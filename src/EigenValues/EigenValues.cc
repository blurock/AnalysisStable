/*  FILE     EigenValues.cpp
**  PACKAGE  EigenValues    
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    
**
**  REFERENCES
**
*/
#include "BasisSystem.hh"
#include "Vector.hh"

#include "MatrixNumeric.hh"
#include "MatrixUtilities.hh"
#include "BasicLaTeXTable.hh"
#include "EigenValuesOut.hh"
#include "EigenValues.hh"

/*F ans = Encode(buffer,mat)  . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    buffer: The buffer
**    mat: The set of Eigenvectors and Eigenvalues
**    ans: true if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, EigenVectors& mat)
{
  return mat.EncodeThis(buffer);
}
/*F ans = Decode(buffer,mat)  . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    buffer: The buffer
**    mat: The set of Eigenvectors and Eigenvalues
**    ans: true if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, EigenVectors& mat)
{
  return mat.DecodeThis(buffer);
}
/*F ans = Encode(buffer,vec)  . . . . . . . . . . . . . . . . .  SingleEigenVector
**
**  DESCRIPTION
**    buffer: The buffer
**    vec: SingleEigenVector
**    ans: true if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, SingleEigenVector& vec)
{
  return vec.EncodeThis(buffer);
}
/*F ans = Decode(buffer,vec)  . . . . . . . . . . . . . . . . .  SingleEigenVector
**
**  DESCRIPTION
**    buffer: The buffer
**    vec: SingleEigenVector
**    ans: true if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, SingleEigenVector& vec)
{
  return vec.DecodeThis(buffer);
}

/*F newout = operator<<(out,mat)  . . . . . . . . . . . . . . .  EigenvVectors
**
**  DESCRIPTION
**    out: The output buffer
**    mat: The Eigenvalues and vectors
**    newout: After printing
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const EigenVectors& mat)
{
  return mat.print(out);
}
/*F newout = operator<<(out,vec)  . . . . . . . . . . . . . . .  SingleEigenVector
**
**  DESCRIPTION
**    out: The output buffer
**    vec: SingleEigenVector
**    newout: After printing
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const SingleEigenVector& vec)
{
  return vec.print(out);
}
/*F SingleEigenVector::operator<
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool SingleEigenVector::operator<(const SingleEigenVector vec2) const
{
  return (*this).Value > vec2.Value;
}
/*F SingleEigenVector::operator==
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool SingleEigenVector::operator==(const SingleEigenVector vec2) const
{
  return (*this).Value == vec2.Value;
}

/*S Constructors
*/ 
/*F EigenVectors()  . . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
EigenVectors::EigenVectors()
{
}
 
/*F EigenVectors(mat) . . . . . . . . . . . . . . . . . . .  copy constructor
**
**  DESCRIPTION
**    mat: The set of Eigenvectors and Eigenvalues
**
**  REMARKS
**
*/
EigenVectors::EigenVectors(const EigenVectors& mat)
  : Eigenvectors(mat.Eigenvectors),
    Eigenvalues(mat.Eigenvalues),
    Cutoff(.01),
    Filter(true)
{
}
/*F EigenVector(mat,filter) . . . . . . . compute the Eigenvectors and values
**
**  DESCRIPTION
**    mat: where the columns are the set of values for a particular element
**         and the set of elements.  The number of rows is the dimension of the
**         Vector space.  The columns are the instances.  The result is sorted.
**    norm: true if the diagonal elements are to be normalized
**    filter: Whether the values should be filtered on output
**
**  REMARKS
**
*/
EigenVectors::EigenVectors(MatrixNumeric mat, const bool norm, const bool filter)
  : Cutoff(.01),
    Filter(filter)
{
  MatrixNumeric FullEigenvectors(mat.size(),mat.size());
  VectorNumeric FullEigenvalues(mat.size());
     
  if(norm)
    mat.normalizeDiagonalElements();
     
  int nrot;
  jacobi(mat,FullEigenvalues,FullEigenvectors,nrot);
    
  FullEigenvectors = FullEigenvectors.transpose();
    
  SortEigenVectors(FullEigenvalues,FullEigenvectors);
}
/*F EigenVectors::CopyClone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void EigenVectors::CopyClone(EigenVectors *mat)
{
  *this = *mat;
}
/*F EigenVectors::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
EigenVectors * EigenVectors::Clone()
{
  EigenVectors *mat = new EigenVectors;
  mat->CopyClone(this);
  return mat;
}
/*F EigenVectors::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& EigenVectors::print(ostream& out) const
{
  unsigned int eigensize = Eigenvalues.size();

  out << "Eigenvalues (originally " << eigensize << ")\n";

  unsigned int count = 0;
  double percent = 0.0, normed = 1.0;
  VectorNumeric::const_iterator val = Eigenvalues.begin();

  out << "     Vector    ";
  out << "   Eigenvalue  ";
  out << "     Total     ";
  out << "   Remainder   ";
  out << endl;
  
  while( (normed > Cutoff) && count < eigensize)
    {
      double value = *val;
      percent += value;
      normed = 1.0 - sqrt(percent);
      out << setw(15) << count;
      out << setw(15) << setprecision(3) << value;
      out << setw(15) << setprecision(3) << percent;
      out << setw(15) << setprecision(3) << normed;
      out << endl;

      count++;
      val++;
    }
  out << endl;
  out << count << " Eigenvectors for Cutoff " << Cutoff << "\n";
  out << "-----------------------------------------------\n";
  out << "Eigenvectors\n";

  unsigned int size1 = Eigenvectors.size();
  unsigned int size2 = Eigenvectors[0].size();

  out << "Eigenmatrix: " << size1 << "," << size2 << "\n";

  for(unsigned int i=0;i < size2;i++)
    {
      out << setw(15) << i;
      for(unsigned j=0;j < count;j++)
        out << setw(12) << setprecision(3) << Eigenvectors[j][i];
      out << "\n";
    }
  out << "-----------------------------------------------\n";
  return out;
}
/*F EigenVectors::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool EigenVectors::EncodeThis(CommBuffer& buffer)
{
  bool result = Eigenvectors.EncodeThis(buffer);
  result = result && Eigenvalues.EncodeThis(buffer);
  return result;
}
/*F EigenVectors::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool EigenVectors::DecodeThis(CommBuffer& buffer)
{
  bool result = Eigenvectors.DecodeThis(buffer);
  result = result && Eigenvalues.DecodeThis(buffer);
  return result;
}
/*F ChangeFilter(filter)  . . . . . . . . . change the Eigenvalue filter flag
**
**  DESCRIPTION
**    filter: true if the Cutoff is to be used to filter Eigenvalues
**
**  REMARKS
**
*/
void EigenVectors::ChangeFilter(const bool filter)
{
  Filter = filter;
}
/*F mat = getEigenVectors()  . . . . . . . . . get the set of eigenvectors
**
**  DESCRIPTION
**    mat: The matrix of eigenvectors
**
**  REMARKS
**
*/
MatrixNumeric& EigenVectors::getEigenVectors()
{
  return Eigenvectors;
}
/*F vec = getEigenValues()  . . . . . . . . . get the set of eigenvalues
**
**  DESCRIPTION
**    vec: The vector of eigenvalues
**
**  REMARKS
**
*/
VectorNumeric& EigenVectors::getEigenValues()
{
  return Eigenvalues;
}
 
/*F ChangeCutoff(cutoff)
**
**  DESCRIPTION
**    cutoff: The minimum Eigenvalue value
**
**  REMARKS
**
*/
void EigenVectors::ChangeCutoff(const double cutoff)
{
  Cutoff = cutoff;
}
/*F SortEigenVectors()  . . . . . . . . . . . .  sort according to Eigenvalue
**
**  DESCRIPTION
**    This sorts the set of Eigenvectors (one in each row in the matrix) 
**    according to the Eigenvalue
**
**  REMARKS
**    It makes use of the MakeEigenVectorClass
**
*/
void EigenVectors::SortEigenVectors(VectorNumeric& evalues, 
                                    MatrixNumeric& evectors)
{
  double cutoff = 0.0;
    
  if(Filter)
    cutoff = Cutoff;
     
  MakeSingleEigenList makeit(Eigenvalues,Eigenvectors,cutoff);
  ObjectList<SingleEigenVector> vectors;
     
  transform(evalues.begin(), evalues.end(), evectors.begin(), 
            back_insert_iterator< ObjectList<SingleEigenVector> >(vectors), makeit);
     
  vectors.Sort();
    
  for_each(vectors.begin(), vectors.end(), makeit);
}
/*F newout = EigenValuesAsLaTeX(out,names) . .  latex output of Eigenvectors
**
**  DESCRIPTION
**    out: The output buffer
**    newout: after printing
** 
**  REMARKS
**
*/
ostream& EigenVectors::EigenvaluesAsLaTeX(ostream& out, const ObjectList<String>& names) const
{
  EigenValueLaTeXTable latex(Eigenvectors,Eigenvalues,names,
                             Eigenvalues.size(),"Factors","Factors");
  latex.printTableBodyNLines(out,Eigenvectors[0].size());
  return out;
}

/*S Constructors
*/ 
/*F SingleEigenVector()  . . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SingleEigenVector::SingleEigenVector()
{
}

/*F SingleEigenVector()  . . . . . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SingleEigenVector::SingleEigenVector(const double value, const VectorNumeric vec)
  : Value(value),
    Vector(vec)
{
}

/*F SingleEigenVector::CopyClone
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
void SingleEigenVector::CopyClone(SingleEigenVector *vec)
{
  *this = *vec;
}

/*F SingleEigenVector::Clone
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
SingleEigenVector * SingleEigenVector::Clone()
{
  SingleEigenVector *vec = new SingleEigenVector;
  vec->CopyClone(this);
  return vec;
}

/*F SingleEigenVector::print
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& SingleEigenVector::print(ostream& out) const
{
  out << "Eigenvalue: " << Value <<"\n";
  out << "Eigenvector ";
  Vector.print(out); out << "\n";
  return out;
}

/*F SingleEigenVector::EncodeThis
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool SingleEigenVector::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer, Value);
  result = result && Vector.EncodeThis(buffer);
  return result;
}

/*F SingleEigenVector::DecodeThis
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
bool SingleEigenVector::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Value);
  result = result && Vector.DecodeThis(buffer);
  return result;
}

/*F MakeSingleEigenList  . . . . . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
MakeSingleEigenList::MakeSingleEigenList(VectorNumeric& values, MatrixNumeric& vectors, const double cutoff)
  : SortedEigenValues(values),
    SortedEigenVectors(vectors),
    Cutoff(cutoff)
{
}
