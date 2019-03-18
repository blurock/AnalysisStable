/*  FILE     VectorType.hh
**  PACKAGE  Vector
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "Vector" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_VECTORTYPE_HH
#define BASIS_VECTORTYPE_HH

 
 
/*C EncodeVector  . . . . . . . . . . . . . . . . Encode the class Vector
**
**  DESCRIPTION
**
**  REMARKS
**
*/
template <class T> 
class EncodeVector
     {
     bool result;
     
 public:
     EncodeVector()
	  : result(true)
	       {
	       }
     
	       
     CommBuffer& operator()(CommBuffer& buffer, T& vec)
	  {
	  result = result && Encode(buffer,vec);
	  return buffer;
	  }
     };
/*C DecodeVector  . . . . . . . . . . . . . . . . .  decodes class Vector
**
**  DESCRIPTION
**     This is set up with the buffer
**
**  REMARKS
**
*/
template <class T>
class DecodeVector
     {
     
     CommBuffer& Buffer;
     bool result;
     
 public:
     DecodeVector(CommBuffer& buffer)
	  : Buffer(buffer), result(true)
	       {
	       }
     bool Successful()
	  {
	  return result;
	  }
     
     T operator()()
	  {
	  T* vec = new T;
	  result = result && Decode(Buffer,*vec);
	  return *vec;
	  }
     };	
 
/*C Vector<T> . . . . . . . . . . . . . . . . . . . .  class of vector<T>
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
template <class T>
class Vector : public vector< T >
{
public:	
  String Title;
  String Delimitor;
     
// Constructors
  Vector();
  Vector(const String& title, const String& delimitor);
  Vector(const char *title, const char *delimitor);
  Vector(const int n);
  Vector(const int n, const T& elem);
  Vector(const Vector<T>& vec);
  virtual ~Vector(){};
// Conversion:
  Vector(const vector<T>& v);
	 
  virtual void CopyClone(Identify *vec);
	virtual Vector<T> * Clone();

// Utility Operations
     void ChangeTitle(const String& title);
     void ChangeDelimitor(const String& title);
// Modifying Functions
     void AddObject(const T& newobject);
     Vector<T>& Concatenate(const Vector<T>& vec2);
// Compare
     bool operator==(const Vector<T>& vec2) const;
     bool operator<(const Vector<T>& vec2) const;
}; // class Vector


/*C VectorFull<T> 
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
template <class T>
class VectorFull : public Vector< T >
{
public:     
// Constructors
  VectorFull();
  VectorFull(const String& title, const String& delimitor);
  VectorFull(const char *title, const char *delimitor);
  VectorFull(const int n);
  VectorFull(const int n, const T& elem);
  VectorFull(const VectorFull<T>& vec);
// Conversion
  VectorFull(const Vector<T>& vec);
  
  virtual ostream& print(ostream& out) const;
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
  virtual bool Read(istream& in);
}; // class VectorFull

/*C VectorSimple<T> 
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
template <class T>
class VectorSimple : public Vector< T >
{
public:     
// Constructors
  VectorSimple();
  VectorSimple(const String& title, const String& delimitor);
  VectorSimple(const char *title, const char *delimitor);
  VectorSimple(const int n);
  VectorSimple(const int n, const T& elem);
  VectorSimple(const VectorSimple<T>& vec);
// Conversion
  VectorSimple(const Vector<T>& vec);

  virtual ostream& print(ostream& out) const;
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
  virtual bool Read(istream& in);
}; // class VectorSimple


/*C VectorNumeric . . . . . . . . . . . . . . . . . . . .  class of VectorNumeric
**
**  DESCRIPTION
**     
**  REMARKS
**
*/
class VectorNumeric : public VectorSimple< double >
{
public:
// Constructors
  VectorNumeric();
  VectorNumeric(const String& title, const String& delimitor);
  VectorNumeric(const char *title, const char *delimitor);
  VectorNumeric(const int n);
  VectorNumeric(const int n, const double& elem);
	VectorNumeric(const VectorNumeric& vec);
// Conversion
//  VectorNumeric(const Vector<double>& vec);

// Prototypes Operators of VectorNumeric
  VectorNumeric operator+(const VectorNumeric& numvec2);
  VectorNumeric operator-(const VectorNumeric& numvec2);
  VectorNumeric operator*(const double& c);
  VectorNumeric operator/(const double& c);
  double operator*(const VectorNumeric& numvec2);

  bool WriteAsLatex(ostream& out);
  bool WriteAsLine(ostream& out);
  bool WriteAsASCII(ostream& out);
  virtual bool Read(istream& in);

}; // class VectorNumeric


/*F getVectorElement(vec, i) . . . . . . . . . . . . . . . . get vector element
**
**  DESCRIPTION
**    returns the element ov vector vec at position i.
**    
**    Initiates to 0 elements of x.
**    
**  REMARKS
**
*/
template<class T>
struct getVectorElement : binary_function<  Vector<T>, int , T >
{
	T operator()(const Vector<T>& vec, const int& index1) const
	{
		return vec[index1];
	}
}; // struct getVectorElement



/*F dotProduct(vec1, vec2) . . . . . . . . . . . . . . . . dot product
**
**  DESCRIPTION
**		dot product of vectors vec1 and vec2
**    
**  REMARKS
**
*/
template<class T>     
struct dotProduct : binary_function< Vector<T> , Vector<T>, T>
{
	T  operator()(const Vector<T>& vec1, const Vector<T>& vec2) const
	{
		T x;
		if (vec1.size() == vec2.size())
		{
			Vector<T> temp(vec1.size(), Zero(x));
			transform(vec1.begin(), vec1.end(), vec2.begin(), temp.begin(), multiplies<T>());
			T temp_scalar = accumulate(temp.begin(), temp.end(), Zero(x));
		    
			return temp_scalar;
		}

		return Zero(x);
		//  	       cout << " Sorry vectors have different sizes\n";
	}
}; // struct dotProduct




#endif
