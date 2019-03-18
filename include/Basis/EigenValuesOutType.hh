/*  FILE     EigenValuesOutType.hh
**  PACKAGE  EigenValuesOut
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "EigenValuesOut" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_EIGENVALUESOUTTYPE_HH
#define BASIS_EIGENVALUESOUTTYPE_HH


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
	const MatrixNumeric& Eigenvectors;
	const VectorNumeric& Eigenvalues;
	const ObjectList<String>& Names;
	unsigned int eigensize;
	unsigned int i;
	ObjectList<String>::const_iterator name;
       
public:
	EigenValueLaTeXTable();  
	EigenValueLaTeXTable(const MatrixNumeric& eigenvectors,
						const VectorNumeric& eigenvalues,
						const ObjectList<String>& names,
						const unsigned int numcols,
						const String& caption,
						const String& label);
  
	ostream& PrintTitles(ostream& out);
	ostream& PrintTableLine(ostream& out);
}; // class EigenValueLaTeXTable

 


#endif
