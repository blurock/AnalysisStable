/*  FILE     PCAAnalysis.cpp
**  PACKAGE  PCAAnalysisN    
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    
**
**  REFERENCES
**
*/

#define TEMPLATE_INSTANTIATION
#include "defines.h"
#include "BasisSystem.hh"
#include "Vector.hh"

#include "MatrixNumeric.hh"
#include "MatrixUtilities.hh"
#include "BasicLaTeXTable.hh"
#include "EigenValuesOut.hh"
#include "EigenValues.hh"
#include "PCAAnalysis.hh"


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
PCAAnalysis::PCAAnalysis(MatrixUtilities& mat)
  : EigenVectors(mat * mat.transpose() ,true,true),
    Transformed(Eigenvectors * mat)
{
}
/*F PCAAnalysis(mat,norm,filter)  . . . . . . . form PCA analysis from matrix
**
**  DESCRIPTION
**    mat: where the columns are the set of values for a particular element
**         and the set of elements.  The number of rows is the dimension of the
**         vector space.  The columns are the instances.
**
**  REMARKS
**
*/
PCAAnalysis::PCAAnalysis(MatrixUtilities& mat, const bool norm, const bool filter)
  : EigenVectors(mat * mat.transpose() ,norm,filter),
    Transformed(Eigenvectors * mat)
{
}
/*F PCAAnalysis::CopyClone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void PCAAnalysis::CopyClone(PCAAnalysis *pca)
{
     *this = *pca;
}
/*F PCAAnalysis::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
PCAAnalysis * PCAAnalysis::Clone()
{
  PCAAnalysis *pca = new PCAAnalysis;
  pca->CopyClone(this);
  return pca;
}
/*F PCAAnalysis::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& PCAAnalysis::print(ostream& out) const
{
  out << (EigenVectors) *this;
  return out;
}
/*F PCAAnalysis::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool PCAAnalysis::EncodeThis(CommBuffer& buffer)
{
  bool result = ((EigenVectors&) (*this)).EncodeThis(buffer);
  result = result && Transformed.EncodeThis(buffer);
  return result;
}
/*F PCAAnalysis::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool PCAAnalysis::DecodeThis(CommBuffer& buffer)
{
  bool result = ((EigenVectors&) (*this)).DecodeThis(buffer);
  result = result && Transformed.DecodeThis(buffer);
  return result;
}
/*F GetTransformedCoordinates() . . . . .  return filtered transformed matrix
**
**  DESCRIPTION
**    The transformed coordinated filtered by the cutoff value (if specified by
**    the Filter flag) are output in matrix form.  
**
**  REMARKS
**
*/
MatrixNumeric PCAAnalysis::GetTransformedCoordinates()
{
	return Transformed.transpose();
}
