/*  FILE     NumericPropertiesType.hh
**  PACKAGE  NumericProperties
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "NumericProperties" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_NUMERICPROPERTIESTYPE_HH
#define CoreObjects_NUMERICPROPERTIESTYPE_HH

/*C BaseDataMatrixPlots  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the MatrixPlots class definitions
**
**  REMARKS
**    Inheirits BaseDataInstanceDoubleMatrix
*/
class BaseDataMatrixPlots : public BaseDataInstanceDoubleMatrix
{
  BaseDataKeyWords Xcoords;
  BaseDataKeyWords Ycoords;

public:
  BaseDataMatrixPlots();
  BaseDataMatrixPlots(const BaseDataMatrixPlots& data);
  BaseDataMatrixPlots(const BaseDataInstanceDoubleMatrix &mat,
		      const BaseDataKeyWords& Xcoords,
		      const BaseDataKeyWords& Ycoords);
  BaseDataKeyWords& getXcoords();
  BaseDataKeyWords& getYcoords();
  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataMatrixPlotsClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataInstanceDoubleMatrixClass
*/
class DataMatrixPlotsClass : public DataInstanceDoubleMatrixClass
{
public:
  DataMatrixPlotsClass();
  DataMatrixPlotsClass(const DataMatrixPlotsClass& data);
  DataMatrixPlotsClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataPolynomialPlotProperties  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the PolynomialPlotProperties class definitions
**
**  REMARKS
**    Inheirits BaseDataInstanceDoubleMatrix
*/
class BaseDataPolynomialPlotProperties : public BaseDataInstanceDoubleMatrix
{
public:
  BaseDataPolynomialPlotProperties();
  BaseDataPolynomialPlotProperties(const BaseDataPolynomialPlotProperties& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C DataPolynomialPlotPropertiesClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataInstanceDoubleMatrixClass
*/
class DataPolynomialPlotPropertiesClass : public DataInstanceDoubleMatrixClass
{
public:
  DataPolynomialPlotPropertiesClass();
  DataPolynomialPlotPropertiesClass(const DataPolynomialPlotPropertiesClass& data);
  DataPolynomialPlotPropertiesClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};
/*C BaseDataCalculateNumericProperties  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the CalculateNumericProperties class definitions
**
**  REMARKS
**    Inheirits BaseDataMatrixSetUp
*/
class BaseDataCalculateNumericProperties : public BaseDataMatrixSetUp
{
  String LowerPowerS;
  BaseDataInteger *LowerPower;
  int Lower;
  String UpperPowerS;
  BaseDataInteger *UpperPower;
  int Upper;
  String XcoordsS;
  BaseDataKeyWords *Xcoords;
  String YcoordsS;
  BaseDataKeyWords *Ycoords;

  String PlotsS;
  BaseDataMatrixPlots *Plots;
  String AttributeNamesS;
  BaseDataKeyWords *AttributeNames;

  String NumDerivativesS;
  BaseDataInteger *NumDerivatives;
  unsigned int numderiv;

  String NumericZeroValueS;
  BaseDataReal *NumericZeroValue;
  double Zero;

  MatrixNumeric *matderivatives;

public:
  BaseDataCalculateNumericProperties();
  BaseDataCalculateNumericProperties(const BaseDataCalculateNumericProperties& data);

  STANDARD_VIRTUAL_METHODS_OBJECT;
  STANDARD_VIRTUAL_ALGORITHM_OBJECT_METHODS;
  bool CalculatePlotInfoForXParameter(String& xname,BaseDataSetOfInstances *instances);
  bool CalculatePlotInfoForXandYParameters(String& xname,String& yname);
  bool ValuesForInstance(MatrixNumeric& mat, 
			 double max,
			 unsigned int numinstance, unsigned int ideriv,
			 unsigned int range, unsigned int icenter, 
			 unsigned int xpos, unsigned int ypos);
  void WriteInstanceValues(String& Xattr, String& yattr,
			   BaseDataSetOfInstances *instances);
  void WriteToInstance(unsigned int ideriv,
		       BaseDataSetOfInstances *instances, 
		       BaseDataReal *r);
  void CalculateDerivatives(double x,unsigned int icenter,double lower,
			    VectorNumeric& coefs);
  MatrixNumeric *FormMatrixOfPowers(MatrixNumeric& mat,
			  unsigned int ibegin, unsigned int iend,
			  double lpower, double upower,
			  unsigned int xpos);
};
/*C DataCalculateNumericPropertiesClass . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits DataMatrixSetUpClass
*/
class DataCalculateNumericPropertiesClass : public DataMatrixSetUpClass
{
public:
  DataCalculateNumericPropertiesClass();
  DataCalculateNumericPropertiesClass(const DataCalculateNumericPropertiesClass& data);
  DataCalculateNumericPropertiesClass(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};





/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
