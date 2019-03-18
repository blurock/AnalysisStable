/*  FILE     FunctionReal1DObjectsType.hh
**  PACKAGE  FunctionReal1DObjects
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "FunctionReal1DObjects" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_FUNCTIONREAL1DOBJECTSTYPE_HH
#define CoreObjects_FUNCTIONREAL1DOBJECTSTYPE_HH
 
/*P  . . . PROTOTYPES  . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
class DataFuncReal1DClass;
class DataConstantReal1DClass;
class DataLinearReal1DClass;
class DataGaussianReal1DClass;
class DataPyramidFunctionClass;

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the FuncReal1D class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataFuncReal1D : public BaseDataObject
{
  double LowerBound;
  double UpperBound;
  bool IncludeLower;
  bool IncludeUpper;
  
public:
  BaseDataFuncReal1D();
  BaseDataFuncReal1D(const BaseDataFuncReal1D& data);

  virtual double operator()(const double x)
    {
      return x;
    }
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass)
    {
      return x;
    }
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsASCII(ostream& o, DataObjectClass *cls);
  virtual bool WriteAsLatex(ostream& o, DataObjectClass  *cls);
  void WriteBounds(ostream&) const;
  VectorNumeric *NumericVectorFromParameters(BaseDataParameterSet *parameters,
					     DataParameterSetClass *parclass);
};
/*C DataFuncReal1DClass . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataFuncReal1DClass : public DataObjectClass
{
public:
  DataFuncReal1DClass();
  DataFuncReal1DClass(const DataFuncReal1DClass& data);
  DataFuncReal1DClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);
};

/*C BaseDataConstantReal1D  . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ConstantReal1D class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataConstantReal1D : public BaseDataFuncReal1D
{
  double ConstantValue;
public:
  BaseDataConstantReal1D();
  BaseDataConstantReal1D(const BaseDataConstantReal1D& data);

  virtual double operator()(const double x);
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass);

  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataConstantReal1DClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataConstantReal1DClass : public DataFuncReal1DClass
{
public:
  DataConstantReal1DClass();
  DataConstantReal1DClass(const DataConstantReal1DClass& data);
  DataConstantReal1DClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the LinearReal1D class definitions with the following 
**    virtual functions:
**    - Read(stream,objc): Read from ASCII stream (using objc for additional format info)
**    - Read(stream,objc,name): Read from ASCII stream (if the name of the object already known)
**    - Write(stream,objc): Write with formatting details
**    - Clone(),CopyClone(obj): Clone a copy
**    - EncodeThis(buffer),DecodeThis(buffer): Encode and Decode routines
**    - print(out): Standard default output routine
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataLinearReal1D : public BaseDataFuncReal1D
{
  double Pointx;
  double Pointy;
  double Directionx;
  double Directiony;
  
public:
  BaseDataLinearReal1D();
  BaseDataLinearReal1D(const BaseDataLinearReal1D& data);

  virtual double operator()(const double x);
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass);
  STANDARD_VIRTUAL_METHODS_OBJECT  
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataLinearReal1DClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataLinearReal1DClass : public DataFuncReal1DClass
{
public:
  DataLinearReal1DClass();
  DataLinearReal1DClass(const DataLinearReal1DClass& data);
  DataLinearReal1DClass(const int id, 
                    const String& name,
                    const String& descr);
STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the GaussianReal1D class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataGaussianReal1D : public BaseDataFuncReal1D
{
  double Constant;
  double ExponentMult;
  double ExponentOffset;
  
public:
  BaseDataGaussianReal1D();
  BaseDataGaussianReal1D(const BaseDataGaussianReal1D& data);

  virtual double operator()(const double x);
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataGaussianReal1DClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataGaussianReal1DClass : public DataFuncReal1DClass
{
public:
  DataGaussianReal1DClass();
  DataGaussianReal1DClass(const DataGaussianReal1DClass& data);
  DataGaussianReal1DClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

/*C BaseDataObject  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PyramidFunction class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataPyramidFunction : public BaseDataFuncReal1D
{
  double InitialHeight;
  double PointHeight;
  double FinalHeight;
  double Xbegin;
  double Xpoint;
  double Xend;
  
public:
  BaseDataPyramidFunction();
  BaseDataPyramidFunction(const BaseDataPyramidFunction& data);
  BaseDataPyramidFunction(const String& name,
                          const double initial,const double point,const double final,
                          const double xbeg, const double xpnt, const double xend);

  double FindPointValue(const double x1,const double y1,
                        const double x2, const double y2,
                        const double x);
  double operator()(const double x);
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass);
  void PrintLine(ostream& out) const;
  STANDARD_VIRTUAL_METHODS_OBJECT
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataPyramidFunctionClass . . . . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataPyramidFunctionClass : public DataFuncReal1DClass
{
public:
  DataPyramidFunctionClass();
  DataPyramidFunctionClass(const DataPyramidFunctionClass& data);
  DataPyramidFunctionClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataPowerReal1D  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PowerReal1D class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataPowerReal1D : public BaseDataFuncReal1D
{
  double Exponent;
public:
  BaseDataPowerReal1D();
  BaseDataPowerReal1D(const BaseDataPowerReal1D& data);

  virtual double operator()(const double x);
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataPowerReal1DClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataPowerReal1DClass : public DataFuncReal1DClass
{
public:
  DataPowerReal1DClass();
  DataPowerReal1DClass(const DataPowerReal1DClass& data);
  DataPowerReal1DClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataExponentialReal1D  . . . . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the ExponentialReal1D class
**
**  REMARKS
**    Inheirits Identify
*/
class BaseDataExponentialReal1D : public BaseDataFuncReal1D
{
  double Constant;
  double ExponentMult;
public:
  BaseDataExponentialReal1D();
  BaseDataExponentialReal1D(const BaseDataExponentialReal1D& data);

  virtual double operator()(const double x);
  virtual double operator()(const double x, 
			    BaseDataParameterSet *parameters,
			    DataParameterSetClass *parclass);
  STANDARD_VIRTUAL_METHODS_OBJECT;
  virtual bool WriteAsLine(ostream&, DataObjectClass *);
  virtual bool WriteAsASCII(ostream&, DataObjectClass *);
  virtual bool WriteAsLatex(ostream&, DataObjectClass  *);
};
/*C DataExponentialReal1DClass . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**
*/
class DataExponentialReal1DClass : public DataFuncReal1DClass
{
public:
  DataExponentialReal1DClass();
  DataExponentialReal1DClass(const DataExponentialReal1DClass& data);
  DataExponentialReal1DClass(const int id, 
                    const String& name,
                    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

#endif

