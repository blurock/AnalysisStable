/*  FILE     BasicLaTeXTable.cpp
**  PACKAGE  BasicLaTeXTable    
**
**  CONTENT
**    
**
**  REFERENCES!!
**
*/
#include "CommBuffer.hh"
#include "String.hh"
#include "Objects.hh"

#include "BasicLaTeXTable.hh"

/*S Constructors
*/ 
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

/*S IO
*/ 
/*F out = printTableBodyNLines(out,count) . .  print count lines of the table
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
ostream& BasicLaTeXTable::printTableBodyNLines(ostream& out, unsigned int count)
{
  for(unsigned int i=0;i<count;i++)
    printTableBodyLine(out);

  printTrailer(out);
  return out;
}
      
/*F out = printTableBodyLine(out) . . . . . . . . . . . . .  print out a line
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
ostream& BasicLaTeXTable::printTableBodyLine(ostream& out)
{
  if(LineCount % MaxLines == 0)
    {
      if(LineCount != 0)
	printTrailer(out);
      
      printHeading(out);
    }

  LineCount++;
  printTableLine(out);
  return out;
}
 
/*F printHeading(out) prints the label line of the table
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
ostream& BasicLaTeXTable::printHeading(ostream& out)
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
  printTitles(out);
  return out;
}
 
/*F out1 = printTrailer(out) . . . . . . . . . . . . . . .  print end of table
**
**  DESCRIPTION
**    out,out1: The output buffer
**
**    The caption and the end of the table is printed
**
**  REMARKS
**
*/
ostream& BasicLaTeXTable::printTrailer(ostream& out)
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
