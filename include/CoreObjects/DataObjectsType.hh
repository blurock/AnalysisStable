/*  FILE     DataObjectsType.hh
**  PACKAGE  DataObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "DataObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_DATAOBJECTSTYPE_HH
#define CoreObjects_DATAOBJECTSTYPE_HH

/*P  . . . PROTOTYPES . . . . . . . . . . . . . . . . . . . . . . . . . . .  
g*/
class DataKeyWordsClass;
class DataMatrixClass;
class DataDoubleMatrixClass;
class DataDoubleVectorClass;

/*C BaseDataString  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the String class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataString : public BaseDataObject
{
  String Name;
public:
  BaseDataString();
  BaseDataString(const BaseDataString& data);
  String& getString();
  void setString(String& s);

  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& o, DataObjectClass  *cls);
};
/*C DataStringClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataStringClass : public DataObjectClass
{
public:
  DataStringClass();
  DataStringClass(const DataStringClass& data);
  DataStringClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};


/*C BaseDataKeyWords  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This structure is to store a list of 'keywords', 'parameters'
**    or 'flags' as a list of keywords.  The access routines are simple:
**    - AddKeyWord(keyword)
**    - RemoveKeyWord(keyword)
**    - bool KeyWordInList(keyword)
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataKeyWords : public BaseDataObject
{
 public:
  ObjectListString KeyWords;

  BaseDataKeyWords();
  BaseDataKeyWords(const BaseDataKeyWords& data);
  BaseDataKeyWords(const ObjectListString& keys);
  
  bool AddKeyWord(const String& key);
  bool AddKeyWords(BaseDataKeyWords &keys);
  bool RemoveKeyWord(const String& key);
  bool KeyWordInList(const String& key);
  String& BuildCategoryName();
  ObjectListString& GetKeyWords();
  void WriteKeys(ostream& out);
  String NextKey();
  unsigned int SizeOf();
  bool ContainedIn(BaseDataKeyWords& list);
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& o, DataObjectClass  *cls);

};
/*C DataKeyWordsClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataKeyWordsClass : public DataObjectClass
{
public:
  DataKeyWordsClass();
  DataKeyWordsClass(const DataKeyWordsClass& data);
  DataKeyWordsClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  bool AddKeyWord(const String& key);
};
/*C BaseDataKeySet  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the KeySet class definitions
**
**  REMARKS
**    Inheirits BaseDataKeyWords
*/
class BaseDataKeySet : public BaseDataKeyWords
{
public:
  BaseDataKeySet();
  BaseDataKeySet(const BaseDataKeySet& data);
  BaseDataKeySet(const BaseDataKeyWords& data);
  bool AddKeyWord(const String& key);

  STANDARD_VIRTUAL_METHODS_OBJECT;
};
/*C DataKeySetClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataKeyWordsClass
*/
class DataKeySetClass : public DataKeyWordsClass
{
public:
  DataKeySetClass();
  DataKeySetClass(const DataKeySetClass& data);
  DataKeySetClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
};
/*C BaseDataPair  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the Pair class definitions
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataPair : public BaseDataObject
{
  BaseDataObject *I;
  BaseDataObject *J;
public:
  BaseDataPair();
  BaseDataPair(const BaseDataPair& data);
  BaseDataObject *getI();
  BaseDataObject *getJ();
  void setI(BaseDataObject *obj);
  void setJ(BaseDataObject *obj);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataPairClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataPairClass : public DataObjectClass
{
  DataObjectClass *IClass;
  DataObjectClass *JClass;  
public:
  DataPairClass();
  DataPairClass(const DataPairClass& data);
  DataPairClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS;
  DataObjectClass *getIClass();
  DataObjectClass *getJClass();  

};



/*C BaseDataDoubleMatrix  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DoubleMatrix class
**
**  REMARKS
**    Inheirits BaseDataNumeric
*/
class BaseDataDoubleMatrix : public BaseDataNumeric
{
  MatrixNumeric Mat;
  
public:
  BaseDataDoubleMatrix();
  BaseDataDoubleMatrix(const BaseDataDoubleMatrix& data);
  BaseDataDoubleMatrix(const MatrixNumeric& mat);

  MatrixNumeric& CurrentMatrix();
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& o, DataObjectClass  *cls);
};
/*C DataDoubleMatrixClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataNumericClass
*/
class DataDoubleMatrixClass : public DataNumericClass
{
public:
  DataDoubleMatrixClass();
  DataDoubleMatrixClass(const DataDoubleMatrixClass& data);
  DataDoubleMatrixClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
 
/*C BaseDataDoubleVector  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the DoubleVector class
**
**  REMARKS
**    Inheirits BaseDataObject
*/
class BaseDataDoubleVector : public BaseDataObject
{
  VectorNumeric Vect;
public:
  BaseDataDoubleVector();
  BaseDataDoubleVector(const BaseDataDoubleVector& data);
  BaseDataDoubleVector(const VectorNumeric& data);
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& o, DataObjectClass  *cls);
  VectorNumeric& CurrentVector();
};
/*C DataDoubleVectorClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataObjectClass
*/
class DataDoubleVectorClass : public DataObjectClass
{
public:
  DataDoubleVectorClass();
  DataDoubleVectorClass(const DataDoubleVectorClass& data);
  DataDoubleVectorClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
