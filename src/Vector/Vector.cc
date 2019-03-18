/*  FILE     Vector.cpp
**  PACKAGE     REACTION    
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    
**
**  REFERENCES
**
*/

#define TEMPLATE_INSTANTIATION
#include "BasisSystem.hh"
#include "Vector.hh"

#ifdef _unix
template class VectorSimple<int>;
template class VectorSimple<double>;
template class vector<int>;
template class vector<double>;
#endif

/*S ZeroUnit
 */
int Zero (int& x)
{
  x = 0;
  return x;
};
float Zero (float& x)
{
  x = 0.0;
  return x;
};
double Zero (double& x)
{
  x = 0.0;
  return x;
};

int Unit (int& x)
{
  x = 1;
  return x;
};
float Unit (float& x)
{
  x = 1.0;
  return x;
};
double Unit (double& x)
{
  x = 1.0;
  return x;
};


/*S Constructors
*/ 
/*F VectorNumeric()  . . . . . . . . . . . . . . . . . . . . . Empty Constructor
**
**  DESCRIPTION
**    Simple Empty Constructor
**    Default Values: 
**       Title     - Empty String
**       Delimitor - Space
**
**  REMARKS
**
*/
VectorNumeric::VectorNumeric()
  : VectorSimple<double>()
{
}

 
/*F Vector(title,delim) . . . . . . . . . . . . . . . . . . . Constructor
**
**  DESCRIPTION
**       title:      The title of the whole vector.
**       delimitor:  The delimitor between the elements of the vector.
** 
**    Constructor with title and delimitor
**
**  REMARKS
**
*/
VectorNumeric::VectorNumeric(const String& title, const String& delim)
  : VectorSimple<double>(title, delim)
{
}
/*F VectorNumeric(title,delim) . . . . . . . . . . . . . . . . . . . Constructor
**
**  DESCRIPTION
**       title: The title of the whole vector
**       delimitor: The delimitor between the elements of the vector
** 
**    Constructor with title and delimitor
**
**  REMARKS
**
*/
inline VectorNumeric::VectorNumeric(const char *title, const char *delim)
  : VectorSimple<double>(title, delim)
{
}

 
/*F VectorNumeric(n) . . . . . . . . . . . . . . . . . . . . . . . . Constructor
**
**  DESCRIPTION
**    n: The number of elements (empty) to initialize to
**
**  REMARKS
**
*/
VectorNumeric::VectorNumeric(const int n)
  : VectorSimple<double>(n)
{
}
/*F VectorNumeric(n, elem)  . . . . . . . . . . . . . . . . . . . . . Constructor
**
**  DESCRIPTION
**              n:              The number of elements to initialize to
**              elem:   element to be filled 
** 
**  REMARKS
**
*/
VectorNumeric::VectorNumeric(const int n, const double& elem)
  : VectorSimple<double>(n, elem)
{
}
/*F VectorNumeric(vec) . . . . . . . . . . . . . . . . . . .Copy Constructor  
**
**  DESCRIPTION
**      vec: The Vector to be copied (const dereferenced)
**
**    The Copy Constructor
**      
**  REMARKS
**
*/
VectorNumeric::VectorNumeric(const VectorNumeric& vec)
  : VectorSimple<double>(vec)
{
}

///*F VectorNumeric(vec)
//**
//**  DESCRIPTION
//**    Conversion
//**      
//**  REMARKS
//**
//*/
//VectorNumeric::VectorNumeric(const Vector<double>& vec)
     //: VectorFull<double>(vec)
     //{
       //}
/*F Vector::Read
**
**  DESCRIPTION
**      
**  REMARKS
**
*/
bool VectorNumeric::Read(istream& in)
{
  bool result = true;
  String word;
  StreamObjectInput file(in, ' ');
  word = file.ReadNext();
  
  unsigned int dim;
  dim = word.ToInteger();
  
  for (unsigned int i=0; i<dim; i++)
    {
      double currentVal;
      word = file.ReadNext();
      currentVal = word.ToFloat();
      AddObject(currentVal);
    }

  return result;
}

 
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . . . . . VectorNumeric
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool VectorNumeric::WriteAsLine(ostream& out)
{
  out << "Vector with " << size() << " double elements ";
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . VectorNumeric
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool VectorNumeric::WriteAsASCII(ostream& out)
{
  out << endl << size();
  for(unsigned int i=0;i < size(); i++)
    {
      if(!(i % 10))
	out << endl;
      out << (*this)[i] << "  ";
    }
  out << endl;
  return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . VectorNumeric
**
**  DESCRIPTION
**    out: The output stream
**    objc: The class of the object
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool VectorNumeric::WriteAsLatex(ostream& out)
{
  out << endl;
  WriteAsLine(out);
  out << endl << "$ ";
  for(unsigned int i=0;i < size(); i++)
    {
      if(i != 0 && !(i % 10))
	out << "$\\\\ " << endl << "     $ ";
      out << (*this)[i] << "  ";
    }
  out << "$\\\\" << endl;
  return true;
}

/*S Modifying
*/ 
/*F result = operator+(numvec2)  . . . . . . . . . . . . . . . .  VectorNumeric
**
**  DESCRIPTION
**     numvec2: The vectors to be added
**     result: the sum of the two vectors.
**
**
**    *this) + + numvec2
**
**    The vectors are added element-wise.
**
**  REMARKS
**
*/
VectorNumeric VectorNumeric::operator+(const VectorNumeric& numvec2)
{
  if ( (*this).size() == numvec2.size() )
    {
      VectorNumeric newnumvec;

      for(unsigned int iter = 0; 
          iter != numvec2.size(); 
          iter++)
        {
          newnumvec.AddObject(numvec2[iter] + (*this)[iter]);
        }

      return newnumvec;
    }

  cerr << "Vector has different size\n";
  return (*this);
};

/*F result = operator-(numvec2)  . . . . . . . . . . . . . . . .  VectorNumeric
**
**  DESCRIPTION
**     numvec1, numvec2: The vectors to be subtracted
**     result: the difference of the two vectors.
**
**
**    numvec1 - numvec2
**
**    The vectors are aded element-wise.
**
**  REMARKS
**
*/
VectorNumeric VectorNumeric::operator-(const VectorNumeric& numvec2)
{
  if ( (*this).size() == numvec2.size())
    {
      VectorNumeric newnumvec;

      for(unsigned int iter = 0; iter != numvec2.size(); iter++)
        newnumvec.AddObject( (*this)[iter] - numvec2[iter]);

      return newnumvec;
    }
  cerr << "Vector has different size\n";
  return (*this);
};


/*F result = operator*(c, numvec)  . . . . . . . . . . . . . . . .  VectorNumeric
**
**  DESCRIPTION
**
**
**      c * numvec
**
**  REMARKS
**
*/
VectorNumeric VectorNumeric::operator*(const double& c)
{
  VectorNumeric newnumvec;

  for(unsigned int iter = 0; 
      iter != (*this).size(); 
      iter++)
    {
      newnumvec.AddObject(c * (*this)[iter]);
    }
        
  return newnumvec;
}

/*F result = operator*(numvec2)  . . . . . . . . . . . .  VectorNumeric
**
**  DESCRIPTION
**  dotproduct with numvec2
**
**      (*this) * numvec2
**
**  REMARKS
**
*/
double VectorNumeric::operator*(const VectorNumeric& numvec2)
{
  double result = 0;

  if ( (*this).size() == numvec2.size())
    {
      for(unsigned int iter = 0; iter != numvec2.size(); iter++)
        {
          result = result + (*this)[iter] * numvec2[iter];
        }
      return result;
    }

  cerr << "Vector has different size\n";
  return Unit(result);
}


/*F result = operator/(numvec, c)  . . . . . . . . . . . . . . . .  VectorNumeric
**
**  DESCRIPTION
**
**      (*this) / c
**
**  REMARKS
**
*/
VectorNumeric VectorNumeric::operator/(const double& c)
{
  VectorNumeric newnumvec;

  for(unsigned int iter = 0; 
      iter != (*this).size(); 
      iter++)
    {
      newnumvec.AddObject( (*this)[iter] / c);
    }
        
  return newnumvec;
}


         
