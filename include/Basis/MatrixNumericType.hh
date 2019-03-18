/*  FILE     MatrixNumericType.hh
**  PACKAGE  MatrixNumeric
**
**  CONTENT
**    Definitions for the "Matrix" package.
**
**  OVERVIEW
**		Class MatrixNumeric is designed to perform
**		some typical operations with matrices.
**		(==, <, <<, >>, Encode, Decode, TopDecode,
**		+, -, *, transpose, getMatrixColumn,
**		getMatrixrow, setSize)
**    
**  REFERENCES
**
*/
#ifndef BASIS_MATRIXNUMERICTYPE_HH
#define BASIS_MATRIXNUMERICTYPE_HH

/*C MatrixNumeric
**
**  DESCRIPTION
**    This class implements some basic matrix operations
**        
**  REMARKS
**
*/
class MatrixNumeric : public VectorFull< VectorNumeric >
{

public:
// Constructors
	MatrixNumeric();
	MatrixNumeric(int dim1, int dim2);
	MatrixNumeric(const MatrixNumeric& numMat);

  virtual void CopyClone(Identify *vec);
  virtual Vector< VectorNumeric>* Clone();
  bool Read(istream& in);
	virtual ostream& print(ostream& out) const;
	virtual bool EncodeThis(CommBuffer& buffer);
	virtual bool DecodeThis(CommBuffer& buffer);

// matrix operators prototypes.
  MatrixNumeric operator+(MatrixNumeric mat2);
  MatrixNumeric operator-(MatrixNumeric mat2);
  MatrixNumeric operator*(MatrixNumeric mat2);
  MatrixNumeric operator*(double c);
  
// Modifying Functions
	MatrixNumeric transpose();
	void transpose(MatrixNumeric &mat);
	void setSize(int newDim, int i);
	VectorNumeric getMatrixColumn(int i); // starts with line 0 !!
	VectorNumeric getMatrixRow(int i);
	void normalizeDiagonalElements();
};	// class MatrixNumeric



#endif
