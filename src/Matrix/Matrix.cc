/*  FILE     Eigenvectors.cc
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
#include "Basis/defines.hh"
#include "Basis/System.hh"
#include "iomanip.h"

#include "Basis/CommBuffer.hh"
#include "Basis/String.hh"
#include "Basis/Objects.hh"
#include "Basis/MixedClasses.hh"

#include "Basis/Matrix.hh"
 
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
 
/*F EigenVector(mat,filter) . . . . . . . compute the eigenvectors and values
**
**  DESCRIPTION
**    mat: where the columns are the set of values for a particular element
**         and the set of elements.  The number of rows is the dimension of the
**         vector space.  The columns are the instances.  The result is sorted.
**    norm: true if the diagonal elements are to be normalized
**    filter: Whether the values should be filtered on output
**
**  REMARKS
**
*/
EigenVectors::EigenVectors(Matrix<double> mat, const bool norm, const bool filter)
  : Cutoff(.01),
    Filter(filter)
     {
     Matrix<double> FullEigenvectors(mat.size(),mat.size());
     vector<double> FullEigenvalues(mat.size());
     
     if(norm)
	  mat.NormalizeDiagonalElements();
//     cout << "===============================================\n";
//     cout << mat;
     
     int nrot;
     jacobi(mat,FullEigenvalues,FullEigenvectors,nrot);
//     cout << "===============================================\n";
     FullEigenvectors = FullEigenvectors.transpose();
//     cout << FullEigenvectors;
     
     SortEigenVectors(FullEigenvalues,FullEigenvectors);
//     cout << "===============================================\n";
//     cout << Eigenvalues;
//     cout << Eigenvectors;
     }
/*S Clone
*/ 
/*F CopyClone(mat)  . . . . . . . . . . . . . . . . . . . . . .  Eigenvectors
**
**  DESCRIPTION
**    mat: The set of eigenvectors and eigenvalues
**
**  REMARKS
**
*/
void EigenVectors::CopyClone(EigenVectors *mat)
     {
     *this = *mat;
     }
 
/*F mat = Clone() . . . . . . . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    Clone a copy
**
**  REMARKS
**
*/
EigenVectors *EigenVectors::Clone()
     {
     EigenVectors *mat = new EigenVectors;
     mat->CopyClone(this);
     return mat;
     }
/*S IO
*/
/*F newout = print(out) . . . . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    out: The output buffer
**    newout: after printing
** 
**  REMARKS
**
*/
ostream& EigenVectors::print(ostream& out) const
{
  unsigned int eigensize = Eigenvalues.size();
  
  out << setw(15) << "Eigenvalues";
  cout << "Eigenvalues (originally " << eigensize << ")\n";
  
  unsigned int count = 0;
  double percent = 0.0;
  double normed = 1.0;
  vector<double>::const_iterator val = Eigenvalues.begin();
  while( (normed > Cutoff) && count < eigensize)
    {
      double value = *val;
      cout << setw(15) << count;
      cout << setw(15) << setprecision(3) << value;
      cout << setw(15) << setprecision(3) << percent;
      cout << setw(15) << setprecision(3) << normed;
      cout << "\n";
      
	   out << setw(12) << setprecision(3) << value;
	   
	   percent += value;
	   normed = 1.0 - sqrt(percent);
	   count++;
	   val++;
    }
  out << "\n";
  cout << count << " Eigenvectors for Cutoff " << Cutoff << "\n";
  cout << "-----------------------------------------------\n";
  cout << "Eigenvectors\n";
  unsigned int size1 = Eigenvectors.size();
  unsigned int size2 = Eigenvectors[0].size();
  cout << "Eigenmatrix: " << size1 << "," << size2 << "\n";
  
  for(unsigned int i=0;i < size2;i++)
    {
      out << setw(15) << i;
      for(unsigned j=0;j < count;j++)
	{
	  out << setw(12) << setprecision(3) << Eigenvectors[j][i];
	}
      out << "\n";
    }
  cout << "-----------------------------------------------\n";
  
  return out;
}
#define RIGHT_TABLE_JUSTIFICATION    1
#define LEFT_TABLE_JUSTIFICATION     2
#define CENTER_TABLE_JUSTIFICATION   3
/*S LaTeXTable
 */
/*C EigenValueLaTeXTable  . . . . . . . . . . help class to print eigenvalues
**
**  DESCRIPTION
**    This is a help class to print out the eigenvalues of a
**    matrix in LaTeX form.
**    - Eigenvectors,Eigenvalues: The values
**    - Names: The set of names representing the columns
**    - eigensize: The size of the column to be printed
**
**  REMARKS
**
*/
class EigenValueLaTeXTable : public BasicLaTeXTable
{
  const Matrix<double>& Eigenvectors;
  const vector<double>& Eigenvalues;
  const ObjectList<String>& Names;
  
  unsigned int eigensize;
  unsigned int i;
  ObjectList<String>::const_iterator name;
       
public:
  EigenValueLaTeXTable();  
  EigenValueLaTeXTable(const Matrix<double>& eigenvectors,
		       const vector<double>& eigenvalues,
		       const ObjectList<String>& names,
		       const unsigned int numcols,
		       const String& caption,
		       const String& label);
  ostream& PrintTitles(ostream& out);
  ostream& PrintTableLine(ostream& out);
};
/*F BasicLaTeXTable(numcols,caption,label)  . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    numcols: The maximum number of columns in the table
**    caption: The text for the caption (and title)
**    label: The text for the label
**    
**  REMARKS
**
*/
BasicLaTeXTable::BasicLaTeXTable(const unsigned int numcols,
				 const String& caption,
				 const String& label)
  : Figure(true),
    Rotated(true),
    NameColumn(true),
    Justification(RIGHT_TABLE_JUSTIFICATION),
    NumberOfColumns(numcols),
    Caption(caption),
    Label(label),
    LineCount(0),
    MaxLines(30)
{
}
/*F BasicLaTeXTable(figure,rot,name,just,numcols,caption,label)
**
**  DESCRIPTION
**    figure: true if a figure
**    rot: true if table is rotated
**    name: The name of the table
**    just: parameter
**    numcols: The maximum number of columns
**    caption: Text to appear in the caption
**    label: The label
**
**  REMARKS
**
*/
BasicLaTeXTable::BasicLaTeXTable(const bool figure,
				 const bool rot,
				 const bool name,
				 const unsigned int just,
				 const unsigned int numcols,
				 const String& caption,
				 const String& label)
  : Figure(figure),
    Rotated(rot),
    NameColumn(name),
    Justification(just),
    NumberOfColumns(numcols),
    Caption(caption),
    Label(label),
    LineCount(0),
    MaxLines(30)
{
}
 
/*F out = PrintTableBodyNLines(out,count) . .  print count lines of the table
**
**  DESCRIPTION
**    out: The output stream
**    count: The number of lines in this table
**
**    Of the entire matrix of data, 'count' lines are printed 
**    a single table.  This is done to keep a long table on 
**    one side
**
**  REMARKS
**
*/
ostream& BasicLaTeXTable::PrintTableBodyNLines(ostream& out, unsigned int count)
{
  for(unsigned int i=0;i<count;i++)
    {
      PrintTableBodyLine(out);
    }
  PrintTrailer(out);
  return out;
}
      
/*F out = PrintTableBodyLine(out) . . . . . . . . . . . . .  print out a line
**
**  DESCRIPTION
**    out: the output buffer
**
**    A single line is printed.  If the maximum number of lines
**    is reached, then the trailer of the table and the
**    begining of the next table is printed.  If it is the
**    first line, the begining of the table is printed
**
**  REMARKS
**
*/
ostream& BasicLaTeXTable::PrintTableBodyLine(ostream& out)
{
  if(LineCount % MaxLines == 0)
    {
      if(LineCount != 0)
	{
	  PrintTrailer(out);
	}
      PrintHeading(out);
    }
  LineCount++;
  PrintTableLine(out);
  return out;
} 
/*F PrintHeading(out) prints the label line of the table
**
**  DESCRIPTION
**    out: The output buffer
**
**    The first line of the table is printed out.  If a rotated
**    figure, then the 'sidewaysfigure' environment is used
**
**  REMARKS
**
*/
ostream& BasicLaTeXTable::PrintHeading(ostream& out)
    {
      if(Figure || Rotated)
	out << "\\begin{sidewaysfigure}\n";
      else if(Figure)
	out << "\\end{figure}\n";
      out << "\\begin{center}\n";
      
      out << "\\begin{tabular}";
      if(NameColumn)
	out << "{|l|";
      else
	out << "{|";
      
      for(unsigned int i=0;i<NumberOfColumns;i++)
	out << "c|";
      out << "}\\hline\n";
      PrintTitles(out);
      return out;
    }
 
/*F out1 = PrintTrailer(out) . . . . . . . . . . . . . . .  print end of table
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**    The caption and the end of the table is printed
**
**  REMARKS
**
*/
ostream& BasicLaTeXTable::PrintTrailer(ostream& out)
{
  out << "\\hline\n";
  out << "\\end{tabular}\n";
  out << "\\end{center}\n";
  
  if(Figure)
    {
      out << "\\caption[";
      out << Caption;
      out << "]{\n";
      out << Caption;
      out << "\n\\label{";
      out << Label;
      out << "}\n}\n";
    }
  if(Figure || Rotated)
      out << "\\end{sidewaysfigure}\n";
  else if(Figure)
      out << "\\end{figure}\n";
  
  return out;
}
 
/*F EigenValueLaTeXTable(vectors,values,names,numcols,caption,label) constructor
**
**  DESCRIPTION
**    vectors: The matrix of eigenvectors
**    values: The eigenvalues
**    names: The name of the parameters of the vectors
**    numcols: The maximum number of columns for a table
**    caption: Text for a caption
**    label: Text for a label of the table
**
**  REMARKS
**
*/
EigenValueLaTeXTable::EigenValueLaTeXTable(const Matrix<double>& vectors,
					     const vector<double>& values,
					     const ObjectList<String>& names,
					     const unsigned int numcols,
					     const String& caption,
					     const String& label)
  : BasicLaTeXTable(numcols,caption,label),
    Eigenvectors(vectors),
    Eigenvalues(values),
    Names(names),
    eigensize(Eigenvalues.size()),
    i(0),
    name(Names.begin())
{
}
 
/*F out1 = PrintTitles(out)  . . . . . . . . . . . . . . . .  eigenvalue title
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**    The title of the eigenvalue table
**
**  REMARKS
**
*/
ostream& EigenValueLaTeXTable::PrintTitles(ostream& out)
{
  out << setw(15) << "Eigenvalues";
  vector<double>::const_iterator val = Eigenvalues.begin();
  for(unsigned int i=0;i<eigensize;i++)
    {
      out << " & ";
      double value = *val;
      out << setw(12) << setprecision(3) << value;
      val++;
    }
  out << " \\\\ \\hline\n";
  val = Eigenvalues.begin();       
  for(unsigned int i=0;i<eigensize;i++)
    {
      out << " & ";
      double value = *val;
      out << setw(12) << setprecision(3) << value*value;
      val++;
    }
  out << " \\\\ \\hline\n";
  return out;
}
/*F out = PrintTableLine(out)
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& EigenValueLaTeXTable::PrintTableLine(ostream& out)
{
  out << setw(15) << *name;
  for(unsigned int j=0;j < eigensize;j++)
    {
      out << " & ";
      out << setw(12) << setprecision(3) << Eigenvectors[j][i];
    }
  out << "\\\\\n";
  name++;
  i++;
  
  return out;
}
/*F newout = EigenVectorsAsLaTeX(out,names) . .  latex output of eigenvectors
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
  latex.PrintTableBodyNLines(out,Eigenvectors[0].size());
  return out;
}
/*F newout = operator<<(out,mat)  . . . . . . . . . . . . . . .  EigenvVectors
**
**  DESCRIPTION
**    out: The output buffer
**    mat: The eigenvalues and vectors
**    newout: After printing
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const EigenVectors& mat)
     {
     return mat.print(out);
     }
/*S EncodeDecode
*/ 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool EigenVectors::EncodeThis(CommBuffer& buffer)
     {
     bool result = Eigenvectors.EncodeThis(buffer);
     result = result && Encode(buffer,(vector<double>&) Eigenvalues);
     return result;
     }     
 
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
bool EigenVectors::DecodeThis(CommBuffer& buffer)
     {
     bool result = Eigenvectors.DecodeThis(buffer);
     result = result && Decode(buffer,Eigenvalues);
     return result;
     }
/*F ans = Encode(buffer,mat)  . . . . . . . . . . . . . . . . .  EigenVectors
**
**  DESCRIPTION
**    buffer: The buffer
**    mat: The set of eigenvectors and eigenvalues
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
**    mat: The set of eigenvectors and eigenvalues
**    ans: true if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, EigenVectors& mat)
     {
     return mat.DecodeThis(buffer);
     }
     
/*S Utilities
*/ 
class MakeSingleEigenList;
 
/*F ChangeFilter(filter)  . . . . . . . . . change the eigenvalue filter flag
**
**  DESCRIPTION
**    filter: true if the Cutoff is to be used to filter eigenvalues
**
**  REMARKS
**
*/
void EigenVectors::ChangeFilter(const bool filter)
     {
     Filter = filter;
     }
 
/*F ChangeCutoff(cutoff)
**
**  DESCRIPTION
**    cutoff: The minimum eigenvalue value
**
**  REMARKS
**
*/
void EigenVectors::ChangeCutoff(const double cutoff)
     {
     Cutoff = cutoff;
     }
/*C SingleEigenVector . . . . . . . . . . . . . .  eigenvector and eigenvalue
**
**  DESCRIPTION
**     This holds the eigenvector and eigenvalue together.  This is 
**     used when these values need to be held in a list (for example
**     sorting.
**  REMARKS
**
*/
class SingleEigenVector
     {
     double Value;
     vector<double> Vector;
 public:
     SingleEigenVector()
	  {
	  }
     SingleEigenVector(const double value,
		       const vector<double> vec)
	  : Value(value),
	  Vector(vec)
	       {
	       }
     void CopyClone(SingleEigenVector *vec)
	  {
	  *this = *vec;
	  }
     SingleEigenVector *Clone()
	  {
	  SingleEigenVector *vec = new SingleEigenVector;
	  vec->CopyClone(this);
	  return vec;
	  }
     
     ostream& print(ostream& out) const
	  {
	  out << "Eigenvalue: " << Value <<"\n";
	  out << "Eigenvector " << Vector << "\n";
	  return out;
	  }
     bool EncodeThis(CommBuffer& buffer)
	  {
	  bool result = Encode(buffer,Value);
	  result = result && Encode(buffer,Vector);
	  return result;
	  }
     bool DecodeThis(CommBuffer& buffer)
	  {
	  bool result = Decode(buffer,Value);
	  result = result && Decode(buffer,Vector);
	  return result;
	  }
     friend bool operator<(const SingleEigenVector vec1, const SingleEigenVector vec2);
     friend bool operator==(const SingleEigenVector vec1, const SingleEigenVector vec2);
     friend class MakeSingleEigenList;
     };
bool operator<(const SingleEigenVector vec1, const SingleEigenVector vec2)
     {
     return vec1.Value > vec2.Value;
     }
bool operator==(const SingleEigenVector vec1,const SingleEigenVector vec2)
     {
     return vec1.Value == vec2.Value;
     }

bool Encode(CommBuffer& buffer, SingleEigenVector& vec)
     {
     return vec.EncodeThis(buffer);
     }
bool Decode(CommBuffer& buffer, SingleEigenVector& vec)
     {
     return vec.DecodeThis(buffer);
     }
ostream& operator<<(ostream& out, const SingleEigenVector& vec)
     {
     return vec.print(out);
     }
/*C MakeEigenVector . . . . . . . . . . . . . . . . . .  eigenvectors to list
**
**  DESCRIPTION
**     This converts the matrix of eigenvectors and the vector of corresponding
**     values to a list of SingleEigenVector classes.  The main use is in sorting
**     the list.
**
**  REMARKS
**
*/
class MakeSingleEigenList
     {
     vector<double>& SortedEigenValues;
     Matrix<double>& SortedEigenVectors;
     double Cutoff;
     
 public:
     MakeSingleEigenList(vector<double>& values,
			 Matrix<double>& vectors,
			 const double cutoff)
       : SortedEigenValues(values),
       SortedEigenVectors(vectors),
       Cutoff(cutoff)
       {
       }
     SingleEigenVector operator()(const double val, const vector<double>& vec)
	  {
	  SingleEigenVector single(val,vec);
	  return single;
	  }
     void operator()(SingleEigenVector& vec)
	  {
	  if(vec.Value >= Cutoff)
	       {
	       SortedEigenValues.push_back(vec.Value);
	       SortedEigenVectors.push_back(vec.Vector);
	       }
	  }
     friend class EigenVectors;
     friend class SingleEigenVector;
     };
	  
/*F SortEigenVectors()  . . . . . . . . . . . .  sort according to eigenvalue
**
**  DESCRIPTION
**    This sorts the set of eigenvectors (one in each row in the matrix) 
**    according to the eigenvalue
**
**  REMARKS
**    It makes use of the MakeEigenVectorClass
**
*/
void EigenVectors::SortEigenVectors(vector<double>& evalues,
				    Matrix<double>& evectors)
     {
     double cutoff = 0.0;
     if(Filter)
	  cutoff = Cutoff;
     
     MakeSingleEigenList makeit(Eigenvalues,Eigenvectors,cutoff);
     
     ObjectList<SingleEigenVector> vectors;
     transform(evalues.begin(),
	       evalues.end(),
	       evectors.begin(),
	       back_insert_iterator< ObjectList<SingleEigenVector> >(vectors),
	       makeit);
     vectors.Sort();
     for_each(vectors.begin(),
	      vectors.end(),
	      makeit);
     }
/*S Constructors
*/ 
/*F PCAAnalysis() . . . . . . . . . . . . . . . . . . . . . empty constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
PCAAnalysis::PCAAnalysis()
     {
     }
 
/*F PCAAnalysis(analysis) . . . . . . . . . . . . . . . . . . copy costructor
**
**  DESCRIPTION
**    analysis: to be copied
**
**  REMARKS
**
*/
PCAAnalysis::PCAAnalysis(const PCAAnalysis& analysis)
: EigenVectors(analysis),
Transformed(analysis.Transformed)
     {
     }
 
/*F PCAAnalysis(mat)  . . . . . . . . . . . . . form PCA analysis from matrix
**
**  DESCRIPTION
**    mat: where the columns are the set of values for a particular element
**         and the set of elements.  The number of rows is the dimension of the
**         vector space.  The columns are the instances.
**
**  REMARKS
**
*/
PCAAnalysis::PCAAnalysis(Matrix<double>& mat)
: EigenVectors(mat * mat.transpose() ,true,true),
Transformed(Eigenvectors * mat)
     {
     }
     
/*S Clone
*/
 
/*F CopyClone(pca)  . . . . . . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    pca: The PCA info
**
**  REMARKS
**
*/
void PCAAnalysis::CopyClone(PCAAnalysis *pca)
     {
     *this = *pca;
     }
 
/*F Clone() . . . . . . . . . . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
PCAAnalysis *PCAAnalysis::Clone()
     {
     PCAAnalysis *pca = new PCAAnalysis;
     pca->CopyClone(this);
     return pca;
     }
/*S IO
*/
 
/*F newout = print(out) . . . . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    out: the output buffer
**    newout: after printing
**
**  REMARKS
**
*/
ostream& PCAAnalysis::print(ostream& out)  const
     {
     out << (EigenVectors) *this;
     return out;
     }
 
/*F newout = operator<<(out,pca)  . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    out: The output buffer
**    pca: The PCA analysis
**    newout: after printing
**
**  REMARKS
**
*/
ostream& operator<<(ostream& out, const PCAAnalysis& pca)
     {
     return pca.print(out);
     }
/*S EncodeDecode
*/
 
/*F ans = EncodeThis(buffer)  . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool PCAAnalysis::EncodeThis(CommBuffer& buffer)
     {
     bool result = Encode(buffer,(EigenVectors&) *this);
     result = result && Encode(buffer,Transformed);
     return result;
     }
/*F ans = DecodeThis(buffer)  . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    buffer: The buffer
**    ans: true if successful
**
**  REMARKS
**
*/
bool PCAAnalysis::DecodeThis(CommBuffer& buffer)
     {
     bool result = Decode(buffer,(EigenVectors&) *this);
     result = result && Decode(buffer,Transformed);
     return result;
     }
 
/*F ans = Encode(buffer,pca)  . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    buffer: The buffer
**    pca: The analysis
**    ans: true if successful
**
**  REMARKS
**
*/
bool Encode(CommBuffer& buffer, PCAAnalysis& pca)
     {
     return pca.EncodeThis(buffer);
     }
/*F ans = Decode(buffer,pca)  . . . . . . . . . . . . . . . . . . PCAAnalysis
**
**  DESCRIPTION
**    buffer: The buffer
**    pca: The analysis
**    ans: true if successful
**
**  REMARKS
**
*/
bool Decode(CommBuffer& buffer, PCAAnalysis& pca)
     {
     return pca.DecodeThis(buffer);
     }

/*S Utility
*/ 
/*F GetTransformedCoordinates() . . . . .  return filtered transformed matrix
**
**  DESCRIPTION
**    The transformed coordinated filtered by the cutoff value (if specified by
**    the Filter flag) are output in matrix form.  
**
**  REMARKS
**
*/
Matrix<double> PCAAnalysis::GetTransformedCoordinates()
     {
     return Transformed.transpose();
     }
/*S ANALYSIS
 */ 
/*F MatrixAnalysisOut(mat,names,part,fsize,out) . . . . . . for ANALYSIS data
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
void MatrixAnalysisOut(Matrix<T>& mat,
		       const ObjectList<String>& names,
		       int part,
//		       const int part,
		       const int fsize,
		       ostream& out)
     {
     int size1 = mat.size();
     int size2 = mat[0].size();
     
     vector<T>::iterator begvar;
     vector<T>::iterator endvar;
     int varcnt = 0;
     
     ObjectList<String>::const_iterator name = names.begin();
     
     while(size2 > 0)
	  {
	  if(part > size2)
	       part = size2;
	       
	  for(int i=0; i < part; i++)
	       {
	       out << *name;
	       out << "\n";
	       name++;
	       }
	  
	  for(int pnt=0; pnt < size1; pnt++)
	       {
	       vector<T> vec = mat[pnt];
	       
	       begvar = vec.begin()+varcnt;
	       endvar = vec.begin()+varcnt+part;
	       
	       for(vector<T>::iterator var=begvar;
		   var != endvar;
		   var++)
		    {
		    out.width(fsize);
		    out.setf(ios::scientific, ios::floatfield);
		    out.precision(5);
		    out << setw(fsize) << *var;
		    }
	       out << "\n";
	       }
	  varcnt += part;
	  size2 -= part;
	  }
     }
 
/*F MatrixAnalysisOutControl(mat,part,fsize,out)  . . . ANALYSIS control file
**
**  DESCRIPTION
**    mat: The matrix
**    filename: The name of the data file
**    part: How many variables in one block
**    fsize: The width of each parameter
**    out: The output stream
**
**    The size of the matrix is used to determine the blocks of data and
**    output to the stream. The form of the output is
**
**    - 0 filename
**    - num ; The number of blocks
**    - filename
**    And for each block:
**    - filename (or SAME if not the first block)
**    - nvar npoints ; The number of variables and number of points
**
**
**  REMARKS
**
*/
template <class T>
void MatrixAnalysisOutControl(Matrix<T>& mat,
			      const String& filename,
			      int part,
//			      const int part,
			      const int fsize,
			      ostream& out)
     {
       int size1 = mat.size();
       int size2 = mat[0].size();
     
       int num = size2/part;
       if(num*part < size2)
	 num += 1;
     
     bool first = true;
     
     while(size2 > 0)
	  {
	    if(first)
	      out << filename;
	    else
	      out << "SAME";
	    first = false;
	    
	  if(part > size2)
	       part = size2;
	  out << "\n";
	  out << part;
	  out << "  ";
	  out << size1;
	  out << " NAME SAME\n";
	  
	  int position = 0;
	  
	  for(int i=0;i < part;i++)
	       {
	       out << position;
	       out << "  ";
	       out << fsize;
	       out << "  F\n";
	       position += fsize;
	       
	       }
	  size2 -= part;
	  }
     }
 
/*F OutputAnalysisDS(names, predicates,out) . . . . . . . .  ANALYSIS ds file
**
**  DESCRIPTION
**    names: The set of variable names
**    predicates: The string containing the predicate types
**    out: The output stream
**
**    This outputs the set of variable names in the form for the analysis routines
**
**  REMARKS
**
*/
void OutputAnalysisVariables(ObjectList<String>& names,
			     String& predicates,
			     ostream& out)
     {
     if(predicates.size() == 1)
	  predicates = "Predicates(>=)";
     
     for(ObjectList<String>::iterator name = names.begin();
	 name != names.end();
	 name++)
	  {
	  out << *name;
	  out << " ";
	  out << predicates;
	  out << "\n";
	  }
     }
/*S GnuPlot
 */ 
/*F MatrixGnuPlotOut(mat,names,part,fsize,root) . . . . . . for GnuPlot data
**
**  DESCRIPTION
**    mat: The matrix
**    names: The names of the rows
**    part: The number of columns in a data row
**    fsize: The size of the element
**    root: Root of the GnuPlot files
**
**  REMARKS
**
*/
template <class T>
void MatrixGnuPlotOut(Matrix<T>& mat,
		      const ObjectList<String>& names,
		      int part,
//		      const int part,
		      const int fsize,
		      const String& root,
		      const ObjectList<T>& xcoord,
		      const int skip)
     {
     int size1 = mat.size();
     int size2 = mat[0].size();
     
     int varcnt = 0;
     int filecnt = 0;
     String suffix("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789");
     OpenOutputFile gnu(root,"plt");
     OpenOutputFile tex(root,"tex");
     
     ObjectList<String>::const_iterator name = names.begin();
     gnu.Stream << "set terminal postscript portrait\n";
     gnu.Stream << "set data style lines\n";
     unsigned int count = 0;
     while(size2 > 0)
	  {
	    String datname = root;
	    String iso = suffix.Isolate(filecnt,filecnt+1);
	    datname.AppendToEnd(iso);
	    
	    OpenOutputFile dat(datname,"dat");
	    if(part > size2)
	      part = size2;
	       
	    for(int i=0; i < part; i++)
	      {
		gnu.Stream << "set output \"";
		gnu.Stream << *name;
		gnu.Stream << ".ps\"\n";
		
		gnu.Stream << "plot '";
		gnu.Stream << dat.FullName;
		gnu.Stream << "' using ";
		gnu.Stream << "1:";
		gnu.Stream << i+2;
		gnu.Stream << " title \'";
		gnu.Stream << *name;
		gnu.Stream << "'\n";
		if(count % 3 == 0)
		  tex.Stream << "\\clearpage\n";
		count++;
		
		tex.Stream << "\\begin{figure}\n";
		tex.Stream << "\\begin{center}\n";
		tex.Stream << "\\epsfxsize=7cm\n";
		tex.Stream << "\\epsfysize=4.9cm\n";
		tex.Stream << "\\epsffile{";
		tex.Stream << *name;
		tex.Stream << ".ps}\n";
		tex.Stream << "\\end{center}\n";
		tex.Stream << "\\caption[";
		tex.Stream << *name;
		tex.Stream << "]\n{";
		tex.Stream << *name;
		tex.Stream << "\\label{";
		tex.Stream << *name;
		tex.Stream << "}\n}\n";
		tex.Stream << "\\end{figure}\n\n";
		
		
		name++;
	      }
	    varcnt = OutputMatrixBlock(mat,size1,part,fsize,varcnt,dat.Stream,xcoord,skip);
	    filecnt++;
	    
	    size2 -= part;
	  }
     }
/*F newcnt = OutputMatrixBlock(mat,size1,part,varcnt) . . . . . block of data
**
**  DESCRIPTION
**    mat: The matrix
**    size1: The number of data points (rows)
**    part: The number of columns in partition
**    varcnt: The current variable count
**    out: The output stream
**    newcnt: The variable count after this partition
**
**  REMARKS
**
*/
template <class T>
int OutputMatrixBlock(Matrix<double> mat, 
		      int size1, 
		      int part,
		      int fsize,
		      int varcnt,
		      ostream& out,
		      const ObjectList<T>& xcoord,
		      const int skip)
{
  ObjectList<double>::const_iterator xpoint = xcoord.begin();
  for(int pnt=0; pnt < size1; pnt++)
    {
      vector<T> vec = mat[pnt];
      
      vector<T>::iterator begvar = vec.begin()+varcnt;
      vector<T>::iterator endvar = vec.begin()+varcnt+part;
      vector<T>::iterator var;
      
      
      if(xcoord.size() > 0)
	{
	  out.setf(ios::scientific, ios::floatfield);
	  out.precision(5);
	  out << setw(fsize) << *xpoint;
	  for(int i=1;i<skip;i++)
	    xpoint++;
	}
      
      for(var=begvar;
	  var != endvar;
	  var++)
	{
	  out.setf(ios::scientific, ios::floatfield);
	  out.precision(5);
	  out << setw(fsize) << *var;
	}
      out << "\n";
    }
  varcnt += part;
  return varcnt;
}
/*S Data
 */
/*F LaTeXMatrixOutSelect(mat,names,part,fsize,out)  . . . . . . . constructor
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
LaTeXMatrixOutSelect<T>::LaTeXMatrixOutSelect(const String& caption,
						const String& label,
						const Matrix<T>& mat,
						const ObjectList<String>& names,
						const ObjectList<T>& select,
						const ObjectList<T>& dependencies,
						const unsigned int fsize,
						const unsigned int prec)
  : BasicLaTeXTable(select.size(),caption,label),
    Mat(mat),
    Select(select),
    Dependencies(dependencies),
    Names(names),
    FSize(fsize),
    Prec(prec),
    Name(Names.begin()),
    x(0)
{
}
/*F out = PrintTable(out) . . . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
ostream& LaTeXMatrixOutSelect<T>::PrintTable(ostream& out)
{
  return PrintTableBodyNLines(out,Mat.size());
}
   
/*F out = PrintTitles(out)  . . . . . . . . . . . . . .  LaTeXMatrixOutSelect
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
ostream& LaTeXMatrixOutSelect<T>::PrintTitles(ostream& out)
{
  cout << Mat.size() << ", " << Mat[0].size() << "\n";
  cout << Names.size() << "\n";
  cout << Select.size() << "\n";
  cout << Dependencies.size() << "\n";
  
  ObjectList<T>::const_iterator dtitle = Select.begin();
  for(unsigned int i=0;i < Select.size();i++)
    {
      out << " &";
      out << *dtitle;
      dtitle++;
    }
  out << "\\\\\\hline\n";
  return out;
}
 
/*F out = PrintTableLine(out) . . . . . . . . . . . . .  LaTeXMatrixOutSelect
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
ostream& LaTeXMatrixOutSelect<T>::PrintTableLine(ostream& out)
{
  ObjectList<T>::const_iterator dep = Dependencies.begin();
  ObjectList<T>::const_iterator pnt = Select.begin();
  out << *Name;
  
  for(unsigned int y=0; y < Mat[0].size(); y++)
    {
      if(*dep >= *pnt || Select.size() == 0)
	{
	  out << " & ";
	  out << setprecision(Prec) 
	      << setw(FSize) 
	      << Mat[x][y];
	  pnt++;
	}
      dep++;
    }
  out << "\\\\\n";
  Name++;
  x++;
  return out;
}
/*F LaTeXMatrixOutBlock() . . . . . . . . . . . . . . . . . . . . constructor
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
LaTeXMatrixOutBlock<T>::LaTeXMatrixOutBlock(const String& caption,
					    const String& label,
					    const Matrix<T>& mat,
					    const ObjectList<String>& rows,
					    const ObjectList<String>& points,
					    const unsigned int colstart,
					    const unsigned int colend,
					    const unsigned int fsize,
					    const unsigned int prec)
  : BasicLaTeXTable(points.size(),caption,label),
    Mat(mat),
    Rows(rows),
    Points(points),
    ColStart(colstart),
    ColEnd(colend),
    Name(Rows.begin()),
    FSize(fsize),
    Prec(prec),
    Pnt(points.begin()),
    x(0)
    {
    }
/*F out = PrintTable(out) . . . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
ostream& LaTeXMatrixOutBlock<T>::PrintTable(ostream& out)
{
  return PrintTableBodyNLines(out,Mat.size());
}
/*F out = PrintTableLine(out) . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
ostream& LaTeXMatrixOutBlock<T>::PrintTableLine(ostream& out)
{
  out << *Name;
  
  for(unsigned int y=ColStart; y < ColEnd; y++)
    {
      out << " & ";
      out.setf(ios::scientific, ios::floatfield);
      out.precision(Prec);
      out << setw(FSize) << Mat[x][y];
    }
  out << "\\\n";
  Name++;
  x++;
  
  return out;
}
/*F out = PrintTitles(out)  . . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
template <class T>
ostream& LaTeXMatrixOutBlock<T>::PrintTitles(ostream& out)
{
  unsigned int size1 = Mat.size();
  ObjectList<String>::const_iterator ptitle = Points.begin();
  for(unsigned int i=0;i < size1;i++)
    {
      out << " &";
      out << *ptitle;
    }
  out << "\\\\ \\hline\n";
  return out;
}
/*S ZeroUnit
 */
int Zero (int& x)
     {
     x = 0;
     return x;
     };
float Zero (float& x)
     {
     x = 0.0;
     return x;
     };
double Zero (double& x)
     {
     x = 0.0;
     return x;
     };

int Unit (int& x)
     {
     x = 1;
     return x;
     };
float Unit (float& x)
     {
     x = 1.0;
     return x;
     };
double Unit (double& x)
     {
     x = 1.0;
     return x;
     };

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
template void MatrixAnalysisOut(Matrix<double>& mat,
				const ObjectList<String>& names,
				const int part,
				const int fsize,
				ostream& out);
template void MatrixAnalysisOutControl(Matrix<double>& mat,
				       const String& filename,
				       const int part,
				       const int fsize,
				       ostream& out);
template void MatrixGnuPlotOut(Matrix<double>& mat,
		 	       const ObjectList<String>& names,
			       const int part,
			       const int fsize,
			       const String& root,
			       const ObjectList<double>& xcoord,
			       const int skip);
template class LaTeXMatrixOutBlock<double>;
template class LaTeXMatrixOutSelect<double>;
template bool Encode(CommBuffer &, Matrix<double> &);
template bool Decode(CommBuffer &, Matrix<double> &);

template ostream& operator<<(ostream &, Matrix<double>);



#ifdef _unix

template class Matrix<double>;
template class vector< vector <double> >;
template Matrix<double>& operator+(Matrix<double>&, Matrix<double>&);
template Matrix<double>& operator-(Matrix<double>&, Matrix<double>&);
template Matrix<double>& operator*(Matrix<double>&, Matrix<double>&);
#endif
