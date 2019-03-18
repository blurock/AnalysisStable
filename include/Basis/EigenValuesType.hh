/*  FILE     EigenValuesType.hh
**  PACKAGE  EigenValues
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "EigenValues" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_EIGENVALUES_HH
#define BASIS_EIGENVALUES_HH


/*C EigenVectors  . . . . . . . . . . . . . .  set of Eigenvalues and vectors
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
class EigenVectors
{
  MatrixNumeric Eigenvectors;
  VectorNumeric Eigenvalues;
  double Cutoff;
  bool Filter;

public:
  // Constructors:
    EigenVectors();
    EigenVectors(const EigenVectors& mat);
    EigenVectors(MatrixNumeric mat, const bool norm, const bool filter);

    void CopyClone(EigenVectors *mat);
    EigenVectors *Clone();
    ostream& print(ostream& out) const;
    bool EncodeThis(CommBuffer& buffer);
    bool DecodeThis(CommBuffer& buffer);

    MatrixNumeric& getEigenVectors();
    VectorNumeric& getEigenValues();
    
    void SortEigenVectors(VectorNumeric& evalues, MatrixNumeric& evectors);
    // Modifying
         void ChangeCutoff(const double cutoff);
    void ChangeFilter(const bool filter);
     
    // not implemented! VectorNumeric TransformCoordinates(VectorNumeric& vec);
    ostream& EigenvaluesAsLaTeX(ostream& out, const ObjectList<String>& names) const;
    // not implemented! ostream& EigenvectorsAsLaTeX(ostream& out, const ObjectList<String>& names) const;

    friend class PCAAnalysis;
}; // class EigenVectors

/*C SingleEigenVector . . . . . . . . . . . . . .  Eigenvector and Eigenvalue
**
**  DESCRIPTION
**     This holds the Eigenvector and Eigenvalue together.  This is 
**     used when these values need to be held in a list (for example
**     sorting.
**  REMARKS
**
*/
class SingleEigenVector
{
  double Value;
  VectorNumeric Vector;
 
public:
  SingleEigenVector();
  SingleEigenVector(const double value, const VectorNumeric vec);

  bool operator<(const SingleEigenVector vec2) const;
  bool operator==(const SingleEigenVector vec2) const;

  void CopyClone(SingleEigenVector *vec);
  SingleEigenVector *Clone();
  ostream& print(ostream& out) const;
  bool EncodeThis(CommBuffer& buffer);
  bool DecodeThis(CommBuffer& buffer);
  
  friend class MakeSingleEigenList;
}; // class SingleEigenVector

/*C MakeSingleEigenList . . . . . . . . . . . . . . . . . .  Eigenvectors to list
**
**  DESCRIPTION
**     This converts the matrix of Eigenvectors and the vector of corresponding
**     values to a list of SingleEigenVector classes.  The main use is in sorting
**     the list.
**
**  REMARKS
**
*/
class MakeSingleEigenList
{
  VectorNumeric& SortedEigenValues;
  MatrixNumeric& SortedEigenVectors;
  double Cutoff;
 
public:
  // Constructor
       MakeSingleEigenList(VectorNumeric& values, MatrixNumeric& vectors,       const double cutoff);
    
  SingleEigenVector operator()(const double val, const VectorNumeric& vec)
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
}; // class MakeSingleEigenList



#endif
