/*  FILE     MatrixOut.hh
**  PACKAGE  MatrixOut
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Definitions for the "MatrixOut" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef REACTION_MATRIXOUT_HH
#define REACTION_MATRIXOUT_HH


/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#ifdef _msdos_stl
#include <vector>
using namespace std;
#pragma warning(disable:4786)
#endif

#ifdef _unix
#include "STL.h"
#endif

#include "defines.hh"
#include "MatrixOutType.hh"

/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
extern void matrixAnalysisOut(MatrixNumeric& mat,
                              const ObjectList<String>& names,
                              int part,
                              const int fsize,
                              ostream& out);
extern void matrixAnalysisOutControl(MatrixNumeric& mat,
                                     const String& filename,
                                     int part,
                                     const int fsize,
                                     ostream& out);
extern void outputAnalysisVariables(ObjectList<String>& names,
                                    String& predicates,
                                    ostream& out);
extern void matrixGnuPlotOut(MatrixNumeric& mat,
                             const ObjectList<String>& names,
                             int part,
                             const int fsize,
                             const String& root,
                             const ObjectList<double>& xcoord,
                             const int skip);
extern int outputMatrixBlock(MatrixNumeric mat, 
                             int size1, 
                             int part,
                             int fsize,
                             int varcnt,
                             ostream& out,
                             const ObjectList<double>& xcoord,
                             const int skip);
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/


#endif
