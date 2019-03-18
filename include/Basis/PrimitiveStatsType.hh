/*  FILE     PrimitiveStatsType.hh
**  PACKAGE  PrimitiveStats
**  AUTHOR   Harald Wahl
**
**  CONTENT
**    Class definitions for the "PrimitiveStats" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
*/
 
#ifndef BASIS_PRIMITIVESTATSTYPE_HH
#define BASIS_PRIMITIVESTATSTYPE_HH

class PrimitiveStats  : public Identify
{
public:
  VectorNumeric Values, SortedValues;
  double Min, Max, Mean, Average, StdDev;
  // Constructors;
  PrimitiveStats();
  PrimitiveStats(const VectorNumeric& vec);
  PrimitiveStats(const PrimitiveStats& primstat);
        
  virtual void CopyClone(Identify* primstat);
  virtual Identify* Clone();
  virtual ostream& print(ostream& out) const;
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
  virtual bool WriteAsLine(ostream&);
  virtual bool WriteAsASCII(ostream&);
  virtual bool WriteAsLatex(ostream&);

  // Calculating Functions
       void CalcAverage(void);
  void CalcMean(void);
  void CalcStdDev(void);
  // Modifying Functions
       void AddValue(const double& value);
  void RemoveValue(const double& value, const bool deleteall);

}; // end class PrimitiveStats



class DistributionStats : public PrimitiveStats
{
public:
  VectorNumeric Counts;
  //    double IntervalBegin, IntervalEnd;

  // Constructors
       DistributionStats();
  DistributionStats(const VectorNumeric& numvec);
  DistributionStats(const DistributionStats& distrstat);
  /*    UNRESOLVED EXTERNAL!!!!!!
        virtual void CopyClone(Identify *dst);
        virtual PrimitiveStats * Clone();
        virtual ostream& print(ostream& out) const;
        virtual bool EncodeThis(CommBuffer& buffer);
        virtual bool DecodeThis(CommBuffer& buffer);
  */
    
};      // end class DistributionStats
     


class GeneralDistributionStats : public DistributionStats
{       
  //
//      ATTENTION! if you change IntervalBegin and IntervalEnd BY HAND
                            //  then execute CountFrequencies afterwards!!!
                            //
                            public:
VectorNumeric LeftEdges, RightEdges;
     
// Constructors
     GeneralDistributionStats();
GeneralDistributionStats(const VectorNumeric& vec);
GeneralDistributionStats(const VectorNumeric& vec, 
                         const VectorNumeric& left, const VectorNumeric& right);
GeneralDistributionStats(const GeneralDistributionStats& gdst);

virtual void CopyClone(Identify *gdst);
virtual Identify* Clone();
virtual ostream& print(ostream& out) const;
virtual bool EncodeThis(CommBuffer& buffer);
virtual bool DecodeThis(CommBuffer& buffer);

// Utility Functions
     void CountFrequencies(void);
void AddInterval(const double& from, const double& to);
};      // end class GeneralDistributionStats

     

class EvenDistributionStats : public DistributionStats
{        
  //   
//      ATTENTION! if you change IntervalSize BY HAND
			    //  then execute CountFrequencies afterwards!!!
			    //
			    
                            protected:
double IntervalBegin, IntervalEnd;

public: 
double IntervalSize;
     
// Constructors
     EvenDistributionStats();
EvenDistributionStats(const VectorNumeric& vec);
EvenDistributionStats(const VectorNumeric& vec, const double isize);
EvenDistributionStats(const EvenDistributionStats& edst);

virtual void CopyClone(Identify *edst);
virtual Identify* Clone();
virtual ostream& print(ostream& out) const;
virtual bool EncodeThis(CommBuffer& buffer);
virtual bool DecodeThis(CommBuffer& buffer);
    virtual bool WriteAsLine(ostream&);
    virtual bool WriteAsASCII(ostream&);
    virtual bool WriteAsLatex(ostream&);

// Utility Functions
     void CountFrequencies(void);
SYS_RETURN WriteCounts2File(ostream& out);
SYS_RETURN WriteCountsNormalized2File(ostream& out);
};      // end class EvenDistributionStats


class GeneralDistributionStatsExcept : public GeneralDistributionStats
{
public:
  VectorNumeric ExceptionValues;
  VectorNumeric SortedExceptionValues;
        
  // Constructors
       GeneralDistributionStatsExcept();
  GeneralDistributionStatsExcept(const VectorNumeric& vec);
  GeneralDistributionStatsExcept(const VectorNumeric& vec, const VectorNumeric& exceptvec);
  GeneralDistributionStatsExcept(const VectorNumeric& vec, const VectorNumeric& from, 
                                 const VectorNumeric& to, const VectorNumeric& exceptvec);
  GeneralDistributionStatsExcept(const GeneralDistributionStatsExcept& gdstex);

  virtual void CopyClone(Identify *gdste);
  virtual Identify* Clone();
  virtual ostream& print(ostream& out) const;
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
        
  // Modifying Functions
       void AddException(const double& value);
  void AddExceptionsFrom(const double& value);
  void AddExceptionsTo(const double& value);
  void RemoveException(const double& value);
  void RemoveExceptionsFrom(const double& value);
  void RemoveExceptionsTo(const double& value);
  void RemoveAllExceptions(void);
};      // end class GeneralDistributionStatsExcept


class EvenDistributionStatsExcept : public EvenDistributionStats
{
public:
  VectorNumeric ExceptionValues;
  VectorNumeric SortedExceptionValues;


  // Constructors
       EvenDistributionStatsExcept();
  EvenDistributionStatsExcept(const VectorNumeric& vec);
  EvenDistributionStatsExcept(const VectorNumeric& vec, const VectorNumeric& exceptvec);
  EvenDistributionStatsExcept(const VectorNumeric& vec, const double isize,
                              const VectorNumeric& exceptvec);
  EvenDistributionStatsExcept(const EvenDistributionStatsExcept& edstex);

  virtual void CopyClone(Identify *edste);
  virtual Identify* Clone();
  virtual ostream& print(ostream& out) const;
  virtual bool EncodeThis(CommBuffer& buffer);
  virtual bool DecodeThis(CommBuffer& buffer);
        
  // Modifying Functions
       void AddException(const double& value);
  void AddExceptionsFrom(const double& value);
  void AddExceptionsTo(const double& value);
  void RemoveException(const double& value);
  void RemoveExceptionsFrom(const double& value);
  void RemoveExceptionsTo(const double& value);
  void RemoveAllExceptions(void);
};      // end class EvenDistributionStatsExept



#endif
