/*  FILE     PCAAnalysisType.hh
**  PACKAGE  PCAAnalysis
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "PCAAnalysis" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_PCAANALYSISTYPE_HH
#define BASIS_PCAANALYSISTYPE_HH

 
/*C PCAAnalysis . . . . . . . . . . . . . . . .  Principle Component Analysis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class PCAAnalysis : public EigenVectors
{
	MatrixNumeric Transformed;
	MatrixNumeric CorrelationMatrix;
 
public:
// Constructors:
	PCAAnalysis();
	PCAAnalysis(const PCAAnalysis& analysis);
	PCAAnalysis(MatrixUtilities& mat);
	PCAAnalysis(MatrixUtilities& mat, 
		    const bool norm, 
		    const bool filter);     
    
	void CopyClone(PCAAnalysis *pca);
	PCAAnalysis *Clone();
	ostream& print(ostream& out) const;
	bool EncodeThis(CommBuffer& buffer);
	bool DecodeThis(CommBuffer& buffer);
    
	MatrixNumeric GetTransformedCoordinates();

	friend class EigenVectors;
}; // class PCAAnalysis

 


#endif
