/*  FILE     MatrixOutType.hh
**  PACKAGE  MatrixOut
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "MatrixOut" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_MATRIXOUTTYPE_HH
#define BASIS_MATRIXOUTTYPE_HH


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
class LaTeXMatrixOutBlock : public BasicLaTeXTable
{
  const MatrixNumeric& Mat;
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
                      const MatrixNumeric& mat,
                      const ObjectList<String>& rows,
                      const ObjectList<String>& points,
                      const unsigned int colstart,
                      const unsigned int colend,
                      const unsigned int fsize,
                      const unsigned int prec);
  ostream& printTitles(ostream& out);
  ostream& printTableLine(ostream& out);
  ostream& printTable(ostream& out);
}; // LaTeXMatrixOutBlock


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
class LaTeXMatrixOutSelect : public BasicLaTeXTable
{
  const MatrixNumeric& Mat;
  const ObjectList<double>& Select;
  const ObjectList<double>& Dependencies;
  const ObjectList<String>& Names;
  unsigned int FSize;
  unsigned int Prec;
  ObjectList<String>::const_iterator Name;
  unsigned int x;
  
public:
  LaTeXMatrixOutSelect(const String& caption,  
                       const String& label,
                       const MatrixNumeric& mat,
                       const ObjectList<String>& names,
                       const ObjectList<double>& select,
                       const ObjectList<double>& dependencies,
                       const unsigned int fsize,
                       const unsigned int prec);
  ostream& printTitles(ostream& out);
  ostream& printTableLine(ostream& out);
  ostream& printTable(ostream& out);
}; // LaTeXMatrixOutSelect



#endif
