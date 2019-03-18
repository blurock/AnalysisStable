/*  FILE     MatrixOut.cpp
**  PACKAGE  MatrixOut    
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
#include "MatrixOut.hh"



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
LaTeXMatrixOutSelect::LaTeXMatrixOutSelect(const String& caption,
                                           const String& label,
                                           const MatrixNumeric& mat,
                                           const ObjectList<String>& names,
                                           const ObjectList<double>& select,
                                           const ObjectList<double>& dependencies,
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

/*F out = printTable(out) . . . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& LaTeXMatrixOutSelect::printTable(ostream& out)
{
  return printTableBodyNLines(out,Mat.size());
}
   
/*F out = printTitles(out)  . . . . . . . . . . . . . .  LaTeXMatrixOutSelect
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& LaTeXMatrixOutSelect::printTitles(ostream& out)
{
  cout << Mat.size() << ", " << Mat[0].size() << "\n";
  cout << Names.size() << "\n";
  cout << Select.size() << "\n";
  cout << Dependencies.size() << "\n";
  ObjectList<double>::const_iterator dtitle = Select.begin();
  
  for(unsigned int i=0;i < Select.size();i++)
    {
      out << " &";
      out << *dtitle;
      dtitle++;
    }
  out << "\\\\\\hline\n";
  return out;
}
 
/*F out = printTableLine(out) . . . . . . . . . . . . .  LaTeXMatrixOutSelect
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& LaTeXMatrixOutSelect::printTableLine(ostream& out)
{
  ObjectList<double>::const_iterator dep = Dependencies.begin();
  ObjectList<double>::const_iterator pnt = Select.begin();
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
LaTeXMatrixOutBlock::LaTeXMatrixOutBlock(const String& caption,
                                         const String& label,
                                         const MatrixNumeric& mat,
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

/*F out = printTable(out) . . . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& LaTeXMatrixOutBlock::printTable(ostream& out)
{
  return printTableBodyNLines(out,Mat.size());
}

/*F out = printTableLine(out) . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& LaTeXMatrixOutBlock::printTableLine(ostream& out)
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

/*F out = printTitles(out)  . . . . . . . . . . . . . . . LaTeXMatrixOutBlock
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
ostream& LaTeXMatrixOutBlock::printTitles(ostream& out)
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


/*S ANALYSIS
 */ 
/*F matrixAnalysisOut(mat,names,part,fsize,out) . . . . . . for ANALYSIS data
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
void matrixAnalysisOut(MatrixNumeric& mat,
                       const ObjectList<String>& names,
                       int part,
                       const int fsize,
                       ostream& out)
{
  int size1 = mat.size();
  int size2 = mat[0].size();
  VectorNumeric::iterator begvar;
  VectorNumeric::iterator endvar;
  int varcnt = 0;
  ObjectList<String>::const_iterator name = names.begin();

  while(size2 > 0)
    {
      // cout << "1  " << "part: " << part << "    size1: " << size1 << "    size2: " << size2 << "   varcnt: " << varcnt << endl;    
      if(part > size2)
        part = size2;
          
      for(int i=0; i < part; i++)
        {
          out << (*name);
          out << "\n";
          name++;
        }

      // cout << "2  " << "part: " << part << "    size1: " << size1 << "    size2: " << size2 << "   varcnt: " << varcnt << endl;    
      for(int pnt=0; pnt < size1; pnt++)
        {
          VectorNumeric vec = mat[pnt];
          begvar = vec.begin()+varcnt;
          endvar = vec.begin()+varcnt+part;

          for(VectorNumeric::iterator var=begvar;
              var != endvar;
              var++)
            {
              out.width(fsize);
              out.setf(ios::scientific, ios::floatfield);
              out.precision(5);
              out << setw(fsize);
              out << (*var);
            }
          out << "\n";
        }
      // cout << "3 -  " << "part: " << part << "    size1: " << size1 << "    size2: " << size2 << "   varcnt: " << varcnt << endl;    
      varcnt += part;
      size2 -= part;
      // cout << "3 +  " << "part: " << part << "    size1: " << size1 << "    size2: " << size2 << "   varcnt: " << varcnt << endl;    
    }
}
         
/*F matrixAnalysisOutControl(mat,part,fsize,out)  . . . ANALYSIS control file
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
void matrixAnalysisOutControl(MatrixNumeric& mat,
                              const String& filename,
                              int part,
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
 
/*F outputAnalysisVariables(names, predicates,out) . . . . . . . .  ANALYSIS ds file
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
void outputAnalysisVariables(ObjectList<String>& names,
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
/*F matrixGnuPlotOut(mat,names,part,fsize,root) . . . . . . for GnuPlot data
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
void matrixGnuPlotOut(MatrixNumeric& mat,
                      const ObjectList<String>& names,
                      int part,
                      const int fsize,
                      const String& root,
                      const ObjectList<double>& xcoord,
                      const int skip)
{
  int size1 = mat.size();
  int size2 = mat[0].size();
  int varcnt = 0;
  int filecnt = 0;
  String suffix("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789");
  String plotroot("plots/");
  String root1(root);
  plotroot.AppendToEnd(root1);

  OpenOutputFile gnu(plotroot,"plt");
  OpenOutputFile tex(plotroot,"tex");
  ObjectList<String>::const_iterator name = names.begin();

  unsigned int count = 0;
    
  while(size2 > 0)
    {
      String datname("plots/");
      datname.AppendToEnd(root1);
      String iso = suffix.Isolate(filecnt,filecnt+1);
      datname.AppendToEnd(iso);
      OpenOutputFile dat(datname,"dat");
      cout << "Output File: " << dat.FullName << endl;
      if(part > size2)
        part = size2;
      cout << part << " " << size1 << " " << size2 << endl;

      for(int i=0; i < part; i++)
        {
	  gnu.Stream << "set terminal postscript portrait\n";
          gnu.Stream << "set output \"";
          gnu.Stream << *name;
          gnu.Stream << ".eps\"\n";
          gnu.Stream << "plot '";
          gnu.Stream << root1 << iso << ".dat";
          gnu.Stream << "' using ";
          gnu.Stream << "1:";
          gnu.Stream << i+2;
          gnu.Stream << " title \'";
          gnu.Stream << *name;
          gnu.Stream << "'\n";
                
	  gnu.Stream << "set terminal png\n";
          gnu.Stream << "set output \"";
          gnu.Stream << *name;
          gnu.Stream << ".png\"\n";
          gnu.Stream << "plot '";
          gnu.Stream << root1 << iso << ".dat";
          gnu.Stream << "' using ";
          gnu.Stream << "1:";
          gnu.Stream << i+2;
          gnu.Stream << " title \'";
          gnu.Stream << *name;
          gnu.Stream << "'\n";

          if(count % 3 == 0)
            tex.Stream << "\\T\\clearpage\n";
                
          count++;

          tex.Stream << "\\begin{figure}\n";
          tex.Stream << "\\reporteps{";
          tex.Stream << *name;
          tex.Stream << "}\n";
          tex.Stream << "\\caption{";
          tex.Stream << *name;
          tex.Stream << "\\label{";
          tex.Stream << *name;
          tex.Stream << "}\n}\n";
          tex.Stream << "\\end{figure}\n\n";
                
          name++;
        }
      varcnt = outputMatrixBlock(mat,size1,part,fsize,varcnt,dat.Stream,xcoord,skip);
      filecnt++;
      size2 -= part;
    }
}


/*F newcnt = outputMatrixBlock(mat,size1,part,varcnt) . . . . . block of data
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
int outputMatrixBlock(MatrixNumeric mat, 
                      int size1, 
                      int part,
                      int fsize,
                      int varcnt,
                      ostream& out,
                      const ObjectList<double>& xcoord,
                      const int skip)
{
  ObjectList<double>::const_iterator xpoint = xcoord.begin();

  for(int pnt=0; pnt < size1; pnt++)
    {
      VectorNumeric vec = mat[pnt];
      VectorNumeric::iterator begvar = vec.begin()+varcnt;
      VectorNumeric::iterator endvar = vec.begin()+varcnt+part;
      VectorNumeric::iterator var;
      
      if(xcoord.size() > 0)
        {
          out.setf(ios::scientific, ios::floatfield);
          out.precision(5);
          out << setw(fsize) << *xpoint;
          
          for(int i=1;i<skip;i++)
            xpoint++;
        }
      
      for(var=begvar; var != endvar; var++)
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
