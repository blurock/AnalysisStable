/*  FILE     BasicLaTeXTableType.hh
**  PACKAGE  BasicLaTeXTable
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "BasicLaTeXTable" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_BASICLATEXTABLETYPE_HH
#define BASIS_BASICLATEXTABLETYPE_HH


/*C BasicLaTexTable
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class BasicLaTeXTable : public Identify
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
  // Consructors
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

  // IO	
       ostream& printHeading(ostream& out);
  ostream& printTrailer(ostream& out);
  ostream& printTableBodyLine(ostream& out);
  ostream& printTableBodyNLines(ostream& out, unsigned int count);
  void setJustification(unsigned int j) { Justification = j; }
  ostream& printTitles(ostream& out) {  return out; }
  ostream& printTableLine(ostream& out)
    {
      return out;
    }
}; // BasicLaTeXTable

 
#endif
