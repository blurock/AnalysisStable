/*  FILE     EigenValuesOut.cpp
**  PACKAGE  EigenValuesOut    
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
#include "BasicLaTeXTable.hh"
#include "EigenValuesOut.hh"


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
EigenValueLaTeXTable::EigenValueLaTeXTable(const MatrixNumeric& vectors,
										   const VectorNumeric& values,
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
  unsigned int i;
  
  out << setw(15) << "Eigenvalues";
	VectorNumeric::const_iterator val = Eigenvalues.begin();
  
	for(i=0;i<eigensize;i++)
    {
		out << " & ";
		double value = *val;
		out << setw(12) << setprecision(3) << value;
		val++;
    }
  
	out << " \\\\ \\hline\n";
	val = Eigenvalues.begin();       
  
	for(i=0;i<eigensize;i++)
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
