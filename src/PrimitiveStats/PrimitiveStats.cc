/*  FILE     PrimitiveStats.cpp
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
#include "MatrixNumeric.hh"
#include "BasicLaTeXTable.hh"
#include "MatrixOut.hh"

#include "PrimitiveStats.hh"

/*S Constructors
*/
/* PrimitiveStats() . . . . . . . . . . . . . . . . . . . . . . .  Empty constructor.
**
**  DESCRIPTION
**    Class PrimitiveStats empty constructor.
**    
**  REMARKS
**
*/
PrimitiveStats::PrimitiveStats()
  : Identify(),
    Values(),
    SortedValues(),
    Min(0), Max(0), Mean(0), Average(0), StdDev(0)
{
  NameTag = "PrimitiveStats";
}

/* PrimitiveStats(vec)    . . . . . . . . . . . . . . . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class PrimitiveStats Constructor.with a VectorNumeric
**    
**  REMARKS
**
*/
PrimitiveStats::PrimitiveStats(const VectorNumeric& vec)
  : Identify(),
    Values(vec),
    SortedValues(vec)
{
  // SortedValues
       sort(SortedValues.begin(), SortedValues.end());

  // Min:
    Min = SortedValues[0];
        
    // Max:
    VectorNumeric::iterator iternumvec;
    iternumvec = max_element(SortedValues.begin(), SortedValues.end());
    Max = *iternumvec;
    //  Max = SortedValues[SortedValues.size() - 1];
        
    // Mean:
    CalcMean();
        
    // Average:
    CalcAverage();

    // Standard Deviation:
    CalcStdDev();

}

/* PrimitiveStats(primstat) . . . . . . . . . . . . . . . . . . . .   Copy Constructor.
**
**  DESCRIPTION
**    primstat: The PrimitiveStats class to be copied
**
**  REMARKS
**
*/
PrimitiveStats::PrimitiveStats(const PrimitiveStats& primstat)
  : Identify(primstat),
    Values(primstat.Values),
    SortedValues(primstat.SortedValues),
    Min(primstat.Min), 
    Max(primstat.Max), 
    Mean(primstat.Mean), 
    Average(primstat.Average), 
    StdDev(primstat.StdDev)
{
  Identification = primstat.Identification;
  NameTag = primstat.NameTag;
}


/* DistributionStats() . . . . . . . . . . . . . . . . . . . . . . .  Empty constructor.
**
**  DESCRIPTION
**    Class PrimitiveStats empty constructor.
**    
**  REMARKS
**
*/
DistributionStats::DistributionStats()
  : PrimitiveStats(),
    Counts()
{
}

/* DistributionStats(vec) . . . . . . . . . . . . . . . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class DistributionStats Constructor.with a VectorNumeric
**    
**  REMARKS
**
*/
DistributionStats::DistributionStats(const VectorNumeric& vec)
  : PrimitiveStats(vec),
    Counts()
{
}

/* DistributionStats(diststat) . . . . . . . . . . . . . . . . . . . .   Copy Constructor.
**
**  DESCRIPTION
**    diststat: The DistributionStats class to be copied
**
**  REMARKS
**
*/
DistributionStats::DistributionStats(const DistributionStats& diststat)
  : PrimitiveStats(diststat),
    Counts(diststat.Counts)
{
}


/* GeneralDistributionStats() . . . . . . . . . . . . . . . . . . . . . . .  Empty constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStats empty constructor.
**    
**  REMARKS
**
*/
GeneralDistributionStats::GeneralDistributionStats()
  : DistributionStats(),
    LeftEdges(),
    RightEdges()
{
}

/* GeneralDistributionStats(vec) . . . . . . . . . . . . . . . . . . . . . Constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStats constructor with VectorNumeric.
**    
**  REMARKS
**
*/
GeneralDistributionStats::GeneralDistributionStats(const VectorNumeric& vec)
  : DistributionStats(vec),
    LeftEdges(),
    RightEdges()
{
  LeftEdges.AddObject(Min);
  RightEdges.AddObject(Max);
  CountFrequencies();
}

/* GeneralDistributionStats(vec, left, right)  . . . . . . . . . . . . . . . . Constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStats constructor with VectorNumeric and
**        LeftEdges left and RightEdges right.
**    
**  REMARKS
**
*/
GeneralDistributionStats::GeneralDistributionStats(const VectorNumeric& vec, 
                                                   const VectorNumeric& left, const VectorNumeric& right)
  : DistributionStats(vec),
    LeftEdges(left),
    RightEdges(right)
{
  CountFrequencies();
}

/* GeneralDistributionStats(diststat) . . . . . . . . . . . . . . . . . . .   Copy Constructor.
**
**  DESCRIPTION
**    gendiststat: The GeneralDistributionStats class to be copied
**
**  REMARKS
**
*/
GeneralDistributionStats::GeneralDistributionStats(const GeneralDistributionStats& gendiststat)
  : DistributionStats(gendiststat),
    LeftEdges(gendiststat.LeftEdges),
    RightEdges(gendiststat.RightEdges)
{
}


/* EvenDistributionStats() . . . . . . . . . . . . . . . . . . . . . . .  Empty constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStats empty constructor.
**    
**  REMARKS
**
*/
EvenDistributionStats::EvenDistributionStats()
  : DistributionStats(),
    IntervalBegin(0),
    IntervalEnd(0),
    IntervalSize(0)
{
}

/* EvenDistributionStats(vec) . . . . . . . . . . . . . . . . . . . . . Constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStats constructor with VectorNumeric.
**    
**  REMARKS
**
*/
EvenDistributionStats::EvenDistributionStats(const VectorNumeric& vec)
  : DistributionStats(vec),
    IntervalBegin(Min),
    IntervalEnd(Max),
    IntervalSize((Max - Min)/10.0)
{
  CountFrequencies();
}

/* EvenDistributionStats(vec, isize)  . . . . . . . . . . . . . . . . Constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStats constructor with VectorNumeric and
**        IntervalSize isize.
**    
**  REMARKS
**
*/
EvenDistributionStats::EvenDistributionStats(const VectorNumeric& vec, 
                                             const double isize)
  : DistributionStats(vec),
    IntervalBegin(Min),
    IntervalEnd(Max),
    IntervalSize(isize)
{
  CountFrequencies();
}

/* EvenDistributionStats(eventstat) . . . . . . . . . . . . . . . . . . . .   Copy Constructor.
**
**  DESCRIPTION
**    evendiststat: The EvenDistributionStats class to be copied
**
**  REMARKS
**
*/
EvenDistributionStats::EvenDistributionStats(const EvenDistributionStats& evendiststat)
  : DistributionStats(evendiststat),
    IntervalBegin(evendiststat.IntervalBegin),
    IntervalEnd(evendiststat.IntervalEnd),
    IntervalSize(evendiststat.IntervalSize)
{
}


/* GeneralDistributionStatsExcept() . . . . . . . . . . . . . . . . . . . . . . .  Empty constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStatsExcept empty constructor.
**    
**  REMARKS
**
*/
GeneralDistributionStatsExcept::GeneralDistributionStatsExcept()
  : GeneralDistributionStats(),
    ExceptionValues(),
    SortedExceptionValues()
{
}

/* GeneralDistributionStatsExcept(vec) . . . . . . . . . . . .  . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStatsExcept constructor.with Vector vec 
**    and no Exceptions
**    
**  REMARKS
**
*/
GeneralDistributionStatsExcept::GeneralDistributionStatsExcept(const VectorNumeric& vec)
  : GeneralDistributionStats(vec),
    ExceptionValues(),
    SortedExceptionValues()
{
}

/* GeneralDistributionStatsExcept(vec, exceptvec) .  . . . . . . . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStatsExcept constructor.with Vector vec 
**    and ExceptionValues exceptvec
**    
**  REMARKS
**
*/
GeneralDistributionStatsExcept::GeneralDistributionStatsExcept
(const VectorNumeric& vec, const VectorNumeric& exceptvec)
  : GeneralDistributionStats(vec),
    ExceptionValues(exceptvec),
    SortedExceptionValues(exceptvec)
{
  // SortedExceptionValues
       sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

  VectorNumeric helpvalues = Values;
  VectorNumeric helpexcvalues = ExceptionValues;
  VectorNumeric helpdeleteexc, helpdeleteval;

  VectorNumeric::iterator iterval, iterexc, location;

  for (iterexc = helpexcvalues.begin(); iterexc < helpexcvalues.end(); iterexc++)
    {
      iterval = find(helpvalues.begin(), helpvalues.end(), (*iterexc));

      if(iterval != helpvalues.end())
        helpdeleteval.AddObject((*iterexc));
      else
        helpdeleteexc.AddObject((*iterexc));
    }
  for (iterval = helpdeleteval.begin(); iterval < helpdeleteval.end(); iterval++)
    {
      RemoveValue((*iterval), false);
      /*                if (IntervalBegin < Min)
                        IntervalBegin = Min;
                        if (IntervalEnd > Max)
                        IntervalEnd = Max;
                        */
      CountFrequencies();
    }
  for (iterexc = helpdeleteexc.begin(); iterexc < helpdeleteexc.end(); iterexc++)
    {
      location = find(ExceptionValues.begin(), ExceptionValues.end(), (*iterexc));
      ExceptionValues.erase(location);
      SortedExceptionValues = ExceptionValues;
      sort(SortedExceptionValues.begin(), SortedExceptionValues.end());
    }
}

/* GeneralDistributionStatsExcept(vec, from, to, exceptvec)  .  . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class GeneralDistributionStatsExcept constructor.with Vector numvec 
**    and ExceptionValues exceptvec and IntervalBegin = from and IntervalEnd = to
**    
**  REMARKS
**    
*/
GeneralDistributionStatsExcept::GeneralDistributionStatsExcept
(const VectorNumeric& vec, const VectorNumeric& from, 
 const VectorNumeric& to, const VectorNumeric& exceptvec)
  : GeneralDistributionStats(vec, from, to),
    ExceptionValues(exceptvec),
    SortedExceptionValues(exceptvec)
{
  // SortedExceptionValues
       sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

  VectorNumeric helpvalues = Values;
  VectorNumeric helpexcvalues = ExceptionValues;
  VectorNumeric helpdeleteexc, helpdeleteval;

  VectorNumeric::iterator iterval, iterexc, location;

  for (iterexc = helpexcvalues.begin(); iterexc < helpexcvalues.end(); iterexc++)
    {
      iterval = find(helpvalues.begin(), helpvalues.end(), (*iterexc));

      if(iterval != helpvalues.end())
        helpdeleteval.AddObject((*iterexc));
      else
        helpdeleteexc.AddObject((*iterexc));
    }
  for (iterval = helpdeleteval.begin(); iterval < helpdeleteval.end(); iterval++)
    {
      RemoveValue((*iterval), false);
      CountFrequencies();
    }
  for (iterexc = helpdeleteexc.begin(); iterexc < helpdeleteexc.end(); iterexc++)
    {
      location = find(ExceptionValues.begin(), ExceptionValues.end(), (*iterexc));
      ExceptionValues.erase(location);
      SortedExceptionValues = ExceptionValues;
      sort(SortedExceptionValues.begin(), SortedExceptionValues.end());
    }
}

/* GeneralDistributionStatsExcept(gdexc) . . . . . . . . . . . . . . . . . . . . .   Copy Constructor.
**
**  DESCRIPTION
**    gdexc: The GeneralDistributionStatsExcept class to be copied
**
**  REMARKS
**
*/
GeneralDistributionStatsExcept::GeneralDistributionStatsExcept
(const GeneralDistributionStatsExcept& gdexc)
  : GeneralDistributionStats(gdexc),
    ExceptionValues(gdexc.ExceptionValues),
    SortedExceptionValues(gdexc.SortedExceptionValues)
{
}


/* EvenDistributionStatsExcept() . . . . . . . . . . . . . . . . . . .  Empty constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStatsExcept empty constructor.
**    
**  REMARKS
**
*/
EvenDistributionStatsExcept::EvenDistributionStatsExcept()
  : EvenDistributionStats(),
    ExceptionValues(),
    SortedExceptionValues()
{
}

/* EvenDistributionStatsExcept(vec) . . . . . . . . . . . .  . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStatsExcept constructor.with Vector vec 
**    and no Exceptions
**    
**  REMARKS
**
*/
EvenDistributionStatsExcept::EvenDistributionStatsExcept(const VectorNumeric& vec)
  : EvenDistributionStats(vec),
    ExceptionValues(),
    SortedExceptionValues()
{
}

/* EvenDistributionStatsExcept(vec, exceptvec) .  . . . . . . . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStatsExcept constructor.with Vector vec 
**    and ExceptionValues exceptvec
**    
**  REMARKS
**
*/
EvenDistributionStatsExcept::EvenDistributionStatsExcept
(const VectorNumeric& vec, const VectorNumeric& exceptvec)
  : EvenDistributionStats(vec),
    ExceptionValues(exceptvec),
    SortedExceptionValues(exceptvec)
{
  // SortedExceptionValues
       sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

  VectorNumeric helpvalues = Values;
  VectorNumeric helpexcvalues = ExceptionValues;
  VectorNumeric helpdeleteexc, helpdeleteval;

  VectorNumeric::iterator iterval, iterexc, location;

  for (iterexc = helpexcvalues.begin(); iterexc < helpexcvalues.end(); iterexc++)
    {
      iterval = find(helpvalues.begin(), helpvalues.end(), (*iterexc));

      if(iterval != helpvalues.end())
        helpdeleteval.AddObject((*iterexc));
      else
        helpdeleteexc.AddObject((*iterexc));
    }
  for (iterval = helpdeleteval.begin(); iterval < helpdeleteval.end(); iterval++)
    {
      RemoveValue((*iterval), false);
      /*                if (IntervalBegin < Min)
                        IntervalBegin = Min;
                        if (IntervalEnd > Max)
                        IntervalEnd = Max;
                        */
      CountFrequencies();
    }
  for (iterexc = helpdeleteexc.begin(); iterexc < helpdeleteexc.end(); iterexc++)
    {
      location = find(ExceptionValues.begin(), ExceptionValues.end(), (*iterexc));
      ExceptionValues.erase(location);
      SortedExceptionValues = ExceptionValues;
      sort(SortedExceptionValues.begin(), SortedExceptionValues.end());
    }
}

/* EvenDistributionStatsExcept(vec, isize, exceptvec) . . . . .  . . . . . . . . .  Constructor.
**
**  DESCRIPTION
**    Class EvenDistributionStatsExcept constructor.with Vector vec 
**    and IntyervalSize isize and ExceptionValues exceptvec
**    
**  REMARKS
**
*/
EvenDistributionStatsExcept::EvenDistributionStatsExcept(const VectorNumeric& vec, 
                                                         const double isize, const VectorNumeric& exceptvec)
  : EvenDistributionStats(vec, isize),
    ExceptionValues(exceptvec),
    SortedExceptionValues(exceptvec)
{
  // SortedExceptionValues
       sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

  VectorNumeric helpvalues = Values;
  VectorNumeric helpexcvalues = ExceptionValues;
  VectorNumeric helpdeleteexc, helpdeleteval;

  VectorNumeric::iterator iterval, iterexc, location;

  for (iterexc = helpexcvalues.begin(); iterexc < helpexcvalues.end(); iterexc++)
    {
      iterval = find(helpvalues.begin(), helpvalues.end(), (*iterexc));

      if(iterval != helpvalues.end())
        helpdeleteval.AddObject((*iterexc));
      else
        helpdeleteexc.AddObject((*iterexc));
    }
  for (iterval = helpdeleteval.begin(); iterval < helpdeleteval.end(); iterval++)
    {
      RemoveValue((*iterval), false);
      /*                if (IntervalBegin < Min)
                        IntervalBegin = Min;
                        if (IntervalEnd > Max)
                        IntervalEnd = Max;
                        */
      CountFrequencies();
    }
  for (iterexc = helpdeleteexc.begin(); iterexc < helpdeleteexc.end(); iterexc++)
    {
      location = find(ExceptionValues.begin(), ExceptionValues.end(), (*iterexc));
      ExceptionValues.erase(location);
      SortedExceptionValues = ExceptionValues;
      sort(SortedExceptionValues.begin(), SortedExceptionValues.end());
    }
}

/* EvenDistributionStatsExcept(edexc) . . . . . . . . . . . . . . . . . . . . .   Copy Constructor.
**
**  DESCRIPTION
**    edexc: The EvenDistributionStatsExcept class to be copied
**
**  REMARKS
**
*/
EvenDistributionStatsExcept::EvenDistributionStatsExcept(const EvenDistributionStatsExcept& edexc)
  : EvenDistributionStats(edexc),
    ExceptionValues(edexc.ExceptionValues),
    SortedExceptionValues(edexc.SortedExceptionValues)
{
}


/*F PrimitiveStats::CloneCopy
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void PrimitiveStats::CopyClone(Identify *iden)
{
  PrimitiveStats* primstat = (PrimitiveStats*) iden;
  *this = *primstat;
}
/*F PrimitiveStats::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
Identify* PrimitiveStats::Clone()
{
  PrimitiveStats *newprimstat = new PrimitiveStats(*this);
  return newprimstat;
}
/*F PrimitiveStats::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& PrimitiveStats::print(ostream& out) const
{
  out << "[";
  out << Identification;
  out << ',';
  out << NameTag;
  out << ']' << endl;
                
  //            out << Values << endl;
  //            out << SortedValues << endl;
  out << "Minimum: " << Min << endl;
  out << "Maximum: " << Max << endl;
  out << "Mean:    " << Mean << endl;
  out << "Average: " << Average << endl;
  if (StdDev < 1e-14)
    out << "StdDev:  " << 0 << endl;
  else
    out << "StdDev:  " << StdDev << endl;
  return out;
}
/*F ans = WriteAsLine(out)  . . . . . . . . . . . . . . . . .  PrimitiveStats
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool PrimitiveStats::WriteAsLine(ostream& out)
{
  out << "Statistics: " << NameTag << "   Ave = " << Average << "+/-" << StdDev;
  out << "  Range:[" << Min << "," << Max << "] ";
  return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . . . . . . .  PrimitiveStats
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool PrimitiveStats::WriteAsASCII(ostream& out)
{
    SortedValues.WriteAsASCII(out);
    out << endl;
    out << Min << " ";
    out << Max << " ";
    out << Mean << " ";
    out << Average << " ";
    out << StdDev << endl;;

    return true;
}
/*F ans = WriteAsLatex(out)  . . . . . . . . . . . . . . . . .  PrimitiveStats
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool PrimitiveStats::WriteAsLatex(ostream& out)
{
    out << endl<< "$ ";
    WriteAsLine(out);
    out << " $\\\\" << endl;

    return true;
}
        
/*F PrimitiveStats::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool PrimitiveStats::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer,Identification);
  result = Encode(buffer,NameTag);
  result = result && Values.EncodeThis(buffer);
  result = result && SortedValues.EncodeThis(buffer);
  result = result && Encode(buffer,Min);
  result = result && Encode(buffer,Max);
  result = result && Encode(buffer,Mean);
  result = result && Encode(buffer,Average);
  result = result && Encode(buffer,StdDev);
  return result;
}
        
/*F PrimitiveStats::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool PrimitiveStats::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Identification);
  result = Decode(buffer,NameTag);
  result = result && Values.DecodeThis(buffer);
  result = result && SortedValues.DecodeThis(buffer);
  result = result && Decode(buffer,Min);
  result = result && Decode(buffer,Max);
  result = result && Decode(buffer,Mean);
  result = result && Decode(buffer,Average);
  result = result && Decode(buffer,StdDev);
  return result;
}
/*F GeneralDistributionStats::CopyClone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void GeneralDistributionStats::CopyClone(Identify *iden)
{
  GeneralDistributionStats *gdst = (GeneralDistributionStats *) iden;
  *this = *gdst;
}
/*F GeneralDistributionStats::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
Identify* GeneralDistributionStats::Clone()
{
  GeneralDistributionStats *newgdst = new GeneralDistributionStats(*this);
  return newgdst;
}
/*F GeneralDistributionStats::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& GeneralDistributionStats::print(ostream& out) const
{
  out << "[";
  out << Identification;
  out << ',';
  out << NameTag;
  out << ']' << endl;
                
  //            out << Values << endl;
  //            out << SortedValues << endl;
  out << "Minimum:    " << Min << endl;
  out << "Maximum:    " << Max << endl;
  out << "Mean:       " << Mean << endl;
  out << "Average:    " << Average << endl;
  if (StdDev < 1e-14)
    out << "StdDev:  " << 0 << endl;
  else
    out << "StdDev:  " << StdDev << endl;
  out << "LeftEdges:  "; LeftEdges.print(out); out << endl;
  out << "RightEdges: "; RightEdges.print(out); out << endl;
  out << "Counts:     "; Counts.print(out); out << endl;
  return out;
}
/*F GeneralDistributionStats::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool GeneralDistributionStats::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer,Identification);
  result = Encode(buffer,NameTag);
  result = result && Values.EncodeThis(buffer);
  result = result && SortedValues.EncodeThis(buffer);
  result = result && Encode(buffer,Min);
  result = result && Encode(buffer,Max);
  result = result && Encode(buffer,Mean);
  result = result && Encode(buffer,Average);
  result = result && Encode(buffer,StdDev);
  result = result && LeftEdges.EncodeThis(buffer);
  result = result && RightEdges.EncodeThis(buffer);
  result = result && Counts.EncodeThis(buffer);
  return result;
}
/*F GeneralDistributionStats::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool GeneralDistributionStats::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Identification);
  result = Decode(buffer,NameTag);
  result = result && Values.DecodeThis(buffer);
  result = result && SortedValues.DecodeThis(buffer);
  result = result && Decode(buffer,Min);
  result = result && Decode(buffer,Max);
  result = result && Decode(buffer,Mean);
  result = result && Decode(buffer,Average);
  result = result && Decode(buffer,StdDev);
  result = result && LeftEdges.DecodeThis(buffer);
  result = result && RightEdges.DecodeThis(buffer);
  result = result && Counts.DecodeThis(buffer);
  return result;
}
        
/*F EvenDistributionStats::CopyClone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void EvenDistributionStats::CopyClone(Identify *iden)
{
  EvenDistributionStats *edst = (EvenDistributionStats *) iden;
  *this = *edst;
}
        
/*F EvenDistributionStats::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
Identify* EvenDistributionStats::Clone()
{
  EvenDistributionStats *newedst = new EvenDistributionStats(*this);
  return newedst;
}
/*F EvenDistributionStats::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& EvenDistributionStats::print(ostream& out) const
{
  out << "[";
  out << Identification;
  out << ',';
  out << NameTag;
  out << ']' << endl;
                
  //            out << Values << endl;
  //            out << SortedValues << endl;
  out << "Minimum: " << Min << endl;
  out << "Maximum: " << Max << endl;
  out << "Mean:    " << Mean << endl;
  out << "Average: " << Average << endl;
  if (StdDev < 1e-14)
    out << "StdDev:  " << 0 << endl;
  else
    out << "StdDev:  " << StdDev << endl;
  out << "Begin:   " << IntervalBegin << endl;
  out << "End:     " << IntervalEnd << endl;
  out << "I-size:  " << IntervalSize << endl;
  out << "Counts:  "; Counts.print(out); out << endl;

  double val = IntervalBegin;
  for(VectorNumeric::const_iterator count = Counts.begin() ; 
      count != Counts.end();
      count++)
    {
      out << setw(20) << val << "  ";
      out << setw(20) << *count << endl;
      val += IntervalSize;
    }

  return out;
}
/*F ans = WriteAsLine(out,objc) . . . . . . . . . . . . EvenDistributionStats
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object one one line
**
**  REMARKS
**
*/
bool EvenDistributionStats::WriteAsLine(ostream& out)
{
    PrimitiveStats::WriteAsLine(out);
    return true;
}
/*F ans = WriteAsASCII(out,objc)  . . . . . . . . . . . EvenDistributionStats
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object as complement to input
**
**  REMARKS
**
*/
bool EvenDistributionStats::WriteAsASCII(ostream& out)
{
    PrimitiveStats::WriteAsASCII(out);
    Counts.WriteAsASCII(out);
    out << IntervalBegin << " " << IntervalEnd << endl;
    return true;
}
/*F ans = WriteAsLatex(out,objc)  . . . . . . . . . . . . . . . . .  EvenDistributionStats
**
**  DESCRIPTION
**    out: The output stream
**    ans: true if successful
**
**    This writes out the object prepared for latex
**
**  REMARKS
**
*/
bool EvenDistributionStats::WriteAsLatex(ostream& out)
{
    PrimitiveStats::WriteAsLatex(out);
    out << "\\begin{tabular}[|l|l|l|]\\\\\\hline" << endl;
    out << " Begin & End & Count \\\\\\hline" << endl;
    double interval = IntervalBegin;
    double intervalsize = IntervalSize;
    for(unsigned int i=0; i < Counts.size(); i++)
	{
	    out << interval << " & ";
	    out << interval + intervalsize << " & ";
	    out << Counts[i] << " \\\\\\hline"  << endl;
	    interval += intervalsize;
	}
    return true;
}
/*F EvenDistributionStats::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool EvenDistributionStats::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer,Identification);
  result = Encode(buffer,NameTag);
  result = result && Values.EncodeThis(buffer);
  result = result && SortedValues.EncodeThis(buffer);
  result = result && Encode(buffer,Min);
  result = result && Encode(buffer,Max);
  result = result && Encode(buffer,Mean);
  result = result && Encode(buffer,Average);
  result = result && Encode(buffer,StdDev);
  result = result && Encode(buffer,IntervalBegin);
  result = result && Encode(buffer,IntervalEnd);
  result = result && Encode(buffer,IntervalSize);
  result = result && Counts.EncodeThis(buffer);
  return result;
}
        
/*F EvenDistributionStats::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool EvenDistributionStats::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Identification);
  result = Decode(buffer,NameTag);
  result = result && Values.DecodeThis(buffer);
  result = result && SortedValues.DecodeThis(buffer);
  result = result && Decode(buffer,Min);
  result = result && Decode(buffer,Max);
  result = result && Decode(buffer,Mean);
  result = result && Decode(buffer,Average);
  result = result && Decode(buffer,StdDev);
  result = result && Decode(buffer,IntervalBegin);
  result = result && Decode(buffer,IntervalEnd);
  result = result && Decode(buffer,IntervalSize);
  result = result && Counts.DecodeThis(buffer);
  return result;
}
        
/*F GeneralDistributionStatsExcept::CopyClone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void GeneralDistributionStatsExcept::CopyClone(Identify *iden)
{
  GeneralDistributionStatsExcept *gdste = (GeneralDistributionStatsExcept *) iden;
  *this = *gdste;
}
        
/*F GeneralDistributionStatsExcept::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
Identify* GeneralDistributionStatsExcept::Clone()       
{
  GeneralDistributionStatsExcept *newgdste = new GeneralDistributionStatsExcept(*this);
  return newgdste;
}
        
/*F GeneralDistributionStatsExcept::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& GeneralDistributionStatsExcept::print(ostream& out) const
{
  out << "[";
  out << Identification;
  out << ',';
  out << NameTag;
  out << ']' << endl;
                
  //            out << Values << endl;
  //            out << SortedValues << endl;
  //            out << ExceptionValues << endl;
  //            out << SortedExceptionValues << endl;
  out << "Minimum: " << Min << endl;
  out << "Maximum: " << Max << endl;
  out << "Mean:    " << Mean << endl;
  out << "Average: " << Average << endl;
  if (StdDev < 1e-14)
    out << "StdDev:  " << 0 << endl;
  else
    out << "StdDev:  " << StdDev << endl;
  out << "LeftEdges:  "; LeftEdges.print(out); out << endl;
  out << "RightEdges: "; RightEdges.print(out); out << endl;
  out << "Counts:  "; Counts.print(out); out << endl;
  return out;
}
        
/*F GeneralDistributionStatsExcept::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool GeneralDistributionStatsExcept::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer,Identification);
  result = result && Encode(buffer,NameTag);
  result = result && Values.EncodeThis(buffer);
  result = result && SortedValues.EncodeThis(buffer);
  result = result && ExceptionValues.EncodeThis(buffer);
  result = result && SortedExceptionValues.EncodeThis(buffer);
  result = result && Encode(buffer,Min);
  result = result && Encode(buffer,Max);
  result = result && Encode(buffer,Mean);
  result = result && Encode(buffer,Average);
  result = result && Encode(buffer,StdDev);
  result = result && LeftEdges.EncodeThis(buffer);
  result = result && RightEdges.EncodeThis(buffer);
  result = result && Counts.EncodeThis(buffer);
  return result;
}
        
/*F GeneralDistributionStatsExcept::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool GeneralDistributionStatsExcept::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Identification);
  result = result && Decode(buffer,NameTag);
  result = result && Values.DecodeThis(buffer);
  result = result && SortedValues.DecodeThis(buffer);
  result = result && ExceptionValues.DecodeThis(buffer);
  result = result && SortedExceptionValues.DecodeThis(buffer);
  result = result && Decode(buffer,Min);
  result = result && Decode(buffer,Max);
  result = result && Decode(buffer,Mean);
  result = result && Decode(buffer,Average);
  result = result && Decode(buffer,StdDev);
  result = result && LeftEdges.DecodeThis(buffer);
  result = result && RightEdges.DecodeThis(buffer);
  result = result && Counts.DecodeThis(buffer);
  return result;
}
        
/*F EvenDistributionStatsExcept::CopyClone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void EvenDistributionStatsExcept::CopyClone(Identify *iden)
{
  EvenDistributionStatsExcept *edste = (EvenDistributionStatsExcept *) iden;
  *this = *edste;
}
/*F EvenDistributionStatsExcept::Clone
**
**  DESCRIPTION
**
**  REMARKS
**
*/
Identify* EvenDistributionStatsExcept::Clone()
{
  EvenDistributionStatsExcept *newedste = new EvenDistributionStatsExcept(*this);
  return newedste;
}
/*F EvenDistributionStatsExcept::print
**
**  DESCRIPTION
**
**  REMARKS
**
*/
ostream& EvenDistributionStatsExcept::print(ostream& out) const
{
  out << "[";
  out << Identification;
  out << ',';
  out << NameTag;
  out << ']' << endl;
                
  //            out << Values << endl;
  //            out << SortedValues << endl;
  //            out << ExceptionValues << endl;
  //            out << SortedExceptionValues << endl;
  out << "Minimum: " << Min << endl;
  out << "Maximum: " << Max << endl;
  out << "Mean:    " << Mean << endl;
  out << "Average: " << Average << endl;
  if (StdDev < 1e-14)
    out << "StdDev:  " << 0 << endl;
  else
    out << "StdDev:  " << StdDev << endl;
  out << "Begin:   " << IntervalBegin << endl;
  out << "End:     " << IntervalEnd << endl;
  out << "I-size:  " << IntervalSize << endl;
  out << "Counts:  "; Counts.print(out); out << endl;
  return out;
}
/*F EvenDistributionStatsExcept::EncodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool EvenDistributionStatsExcept::EncodeThis(CommBuffer& buffer)
{
  bool result = Encode(buffer,Identification);
  //            result = result && Encode(buffer,NameTag);
  result = result && Values.EncodeThis(buffer);
  result = result && SortedValues.EncodeThis(buffer);
  result = result && ExceptionValues.EncodeThis(buffer);
  result = result && SortedExceptionValues.EncodeThis(buffer);
  result = result && Encode(buffer,Min);
  result = result && Encode(buffer,Max);
  result = result && Encode(buffer,Mean);
  result = result && Encode(buffer,Average);
  result = result && Encode(buffer,StdDev);
  result = result && Encode(buffer,IntervalBegin);
  result = result && Encode(buffer,IntervalEnd);
  result = result && Encode(buffer,IntervalSize);
  result = result && Counts.EncodeThis(buffer);
  return result;
}
/*F EvenDistributionStatsExcept::DecodeThis
**
**  DESCRIPTION
**
**  REMARKS
**
*/
bool EvenDistributionStatsExcept::DecodeThis(CommBuffer& buffer)
{
  bool result = Decode(buffer,Identification);
  //            result = result && Decode(buffer,NameTag);
  result = result && Values.DecodeThis(buffer);
  result = result && SortedValues.DecodeThis(buffer);
  result = result && ExceptionValues.DecodeThis(buffer);
  result = result && SortedExceptionValues.DecodeThis(buffer);
  result = result && Decode(buffer,Min);
  result = result && Decode(buffer,Max);
  result = result && Decode(buffer,Mean);
  result = result && Decode(buffer,Average);
  result = result && Decode(buffer,StdDev);
  result = result && Decode(buffer,IntervalBegin);
  result = result && Decode(buffer,IntervalEnd);
  result = result && Decode(buffer,IntervalSize);
  result = result && Counts.DecodeThis(buffer);
  return result;
}

 
/*F PrimitiveStats::CalcAverage() .. . . . . . . . . . . . . . . Calculates the Average
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void PrimitiveStats::CalcAverage(void)
{
  VectorNumeric::iterator location;
  double helpdouble = 0;

  for (location = Values.begin(); location < Values.end(); location++)
    helpdouble = helpdouble + (*location);
  Average = helpdouble / Values.size();
}
/*F PrimitiveStats::CalcMean() . . . . . . . . . . . . . . . . . Calculates the Mean
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void PrimitiveStats::CalcMean(void)
{
  double help;
  
  help = SortedValues.size()/2.0;
  unsigned int ihelp = (unsigned int) ceil(help) - 1;
  Mean = SortedValues[ihelp];
}

/*F PrimitiveStats::CalcStdDev() . . . . . . . . . . . . . . . . Calculates the Standard Deviation
**
**  DESCRIPTION
**
**  REMARKS
**
*/
void PrimitiveStats::CalcStdDev(void)
{
  VectorNumeric::iterator location;
  double helpdouble = 0;

  for (location = Values.begin(); location < Values.end(); location++)
    helpdouble = helpdouble + ((*location - Average) * (*location - Average))
      / (Values.size()-1);
  StdDev = sqrt(helpdouble) ;
}

/*F GeneralDistributionStats::CountFrequencies() . . . . . . . . . Calculate
**
**  DESCRIPTION
**  Calculates the number of frequencies Values
**  in the Interval [IntervalBegin, IntervalEnd]
**    
**  REMARKS
**
*/
void GeneralDistributionStats::CountFrequencies(void)
{
  VectorNumeric::iterator iterleft, iterright, itervalues;
  int helpcount = 0;

  Counts.erase(Counts.begin(), Counts.end());
        
  iterleft=LeftEdges.begin();
  iterright=RightEdges.begin();

  while (iterleft<LeftEdges.end())
    {
      for (itervalues = Values.begin(); itervalues < Values.end(); itervalues++)
        {
          if ( (*itervalues >= *iterleft) && (*itervalues <= *iterright))
            helpcount++;
        }
      Counts.AddObject(helpcount);
      helpcount = 0;
      iterleft++;
      iterright++;
    }
}


/*F EvenDistributionStats::CountFrequencies() . . . . . . . . . Calculate
**
**  DESCRIPTION
**  Calculates the number of frequencies within an interval
**  with size IntervalSize
**    
**  REMARKS
**
*/
void EvenDistributionStats::CountFrequencies(void)
{
  VectorNumeric::iterator location;

  Counts.erase(Counts.begin(), Counts.end());

  if (Min == Max)
    {
      Counts.AddObject(Values.size());
      IntervalSize = 0;
    }
  else
    {
      VectorNumeric intervalBorders;
      double currentBorder = IntervalBegin;

      while (currentBorder < IntervalEnd + IntervalSize)
        {
          if (currentBorder < IntervalEnd)
            intervalBorders.AddObject(currentBorder);
          else
            intervalBorders.AddObject(IntervalEnd);

          currentBorder += IntervalSize;
        }

      int helpcount = 0;        
      for (location = Values.begin(); location < Values.end(); location++)
        {
          if (*location == IntervalBegin)       // Minima mitzaehlen!
                                                  helpcount++;
        }

      for (unsigned int i=0; i<intervalBorders.size()-1; i++)
        {
          for (location = Values.begin(); location < Values.end(); location++)
            {
              if ( ((*location) > intervalBorders[i]) && ((*location) <= intervalBorders[i+1]) )
                helpcount++;
            }
          Counts.AddObject(helpcount);
          helpcount = 0;
        }
    }
}


/*S Modifying
*/ 
/*F PrimitiveStats::AddValue(newvalue) . . . . . . . . . Add single value
**
**  DESCRIPTION
**     newvalue: The element to be put on the Vector
**
**
**  REMARKS
**
*/
void PrimitiveStats::AddValue(const double& newvalue)
{
  Values.AddObject(newvalue);

  // SortedValues:
    SortedValues.AddObject(newvalue);
    sort(SortedValues.begin(), SortedValues.end());
        
    // Min:
    if (newvalue < Min)
      Min = newvalue;
        
    // Max:
    if (newvalue > Max)
      Max = newvalue;
        
    // Mean:
    CalcMean();

    // Average:
    CalcAverage();
        
    // Standard Deviation:
    CalcStdDev();
}

/*F PrimitiveStats::RemoveValue(newvalue) . . . . . . . . . Remove single value
**
**  DESCRIPTION
**     newvalue:  The element to be removed from the Vector
**     deleteall: delete all value or only one  
**
**
**  REMARKS
**
*/
void PrimitiveStats::RemoveValue(const double& value, const bool deleteall)
{
  VectorNumeric::iterator location;
    
  if(find(Values.begin(), Values.end(), value) != Values.end())
    {
      if (deleteall)
        {
          location = remove(Values.begin(),Values.end(),value);
          Values.erase(location, Values.end());
        }
      else
        {
          location = find(Values.begin(), Values.end(), value);
          Values.erase(location);
        }
                
      // SortedValues:
        SortedValues = Values;
        sort(SortedValues.begin(), SortedValues.end());

        // Min:
        Min = SortedValues[0];
        
        // Max:
        VectorNumeric::iterator iternumvec;
        iternumvec = max_element(SortedValues.begin(), SortedValues.end());
        Max = *iternumvec;
        //      Max = SortedValues[SortedValues.size() - 1];

        // Mean:
        CalcMean();
                
        // Average:
        CalcAverage();

        // Standard Deviation:
        CalcStdDev();
    }
}

/*F GeneralDistributionStats::AddInterval(from, to) . . . . . . . . . . . Add interval
**
**  DESCRIPTION
**     from, to: The edges of the new interval
**
**  REMARKS
*/
void GeneralDistributionStats::AddInterval(const double& from, const double& to)
{
  LeftEdges.AddObject(from);
  RightEdges.AddObject(to);
  CountFrequencies();
}

/*F GeneralDistributionStatsExcept::AddException(value) . . . . . . . . . . . Add exception
**
**  DESCRIPTION
**     value: The element to be put on the ExceptionValues Vector
**
**
**  REMARKS
**     The value is added to ExceptionValues only if it belongs to Values!!
*/
void GeneralDistributionStatsExcept::AddException(const double& newvalue)
{
  while(find(Values.begin(), Values.end(), newvalue) != Values.end())
    //    if(find(Values.begin(), Values.end(), newvalue) != Values.end())
      {
        ExceptionValues.AddObject(newvalue);
        
        // SortedExceptionValues
             SortedExceptionValues.AddObject(newvalue);
        sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

        RemoveValue(newvalue, false);   // delete only one occurence
                                             CountFrequencies();
      }
}

/*F GeneralDistributionStatsExcept::AddExceptionsFrom(value)  . . . . . . Add exception
**
**  DESCRIPTION
**     All elements greater or equal than value are removed from 
**     Values and Added to ExceptionValues
**
**  REMARKS***********
*/
void GeneralDistributionStatsExcept::AddExceptionsFrom(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=Values.begin(); iternumvec<Values.end(); iternumvec++)
    if (*iternumvec >= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    AddException(*iternumvec);
}

/*F GeneralDistributionStatsExcept::AddExceptionsTo(value)  . . . . . . Add exception
**
**  DESCRIPTION
**     All elements less or equal than value are removed from 
**     Values and Added to ExceptionValues
**
**  REMARKS
*/
void GeneralDistributionStatsExcept::AddExceptionsTo(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=Values.begin(); iternumvec<Values.end(); iternumvec++)
    if (*iternumvec <= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    AddException(*iternumvec);
}

/*F GeneralDistributionStatsExcept::RemoveException(value) . . . . . . . . . remove exception
**
**  DESCRIPTION
**     value: The element to be removed from the ExceptionValues Vector
**         and added to Values
**
**  REMARKS
**         
*/
void GeneralDistributionStatsExcept::RemoveException(const double& value)
{
  VectorNumeric::iterator location;

  location = find(ExceptionValues.begin(), ExceptionValues.end(), value);
    
  if(location != ExceptionValues.end())
    {
      ExceptionValues.erase(location);
                
      // SortedExceptionValues:
        SortedExceptionValues = ExceptionValues;
        sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

        AddValue(value);
        CountFrequencies();
    }
}

/*F GeneralDistributionStatsExcept::RemoveExceptionsFrom(value)  . . . . . . remove exception
**
**  DESCRIPTION
**     All elements greater or equal than value are removed from 
**     ExceptionValues and Added to Values
**
**  REMARKS
*/
void GeneralDistributionStatsExcept::RemoveExceptionsFrom(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=ExceptionValues.begin(); iternumvec<ExceptionValues.end(); iternumvec++)
    if (*iternumvec >= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    RemoveException(*iternumvec);
}

/*F GeneralDistributionStatsExcept::RemoveExceptionsTo(value)  . . . . . . remove exception
**
**  DESCRIPTION
**     All elements less or equal than value are removed from 
**     ExceptionValues and Added to Values
**
**  REMARKS
*/
void GeneralDistributionStatsExcept::RemoveExceptionsTo(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=ExceptionValues.begin(); iternumvec<ExceptionValues.end(); iternumvec++)
    if (*iternumvec <= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    RemoveException(*iternumvec);
}

/*F GeneralDistributionStatsExcept::RemoveAllExceptions() . . . . . . . . . remove exception
**
**  DESCRIPTION
**
**  REMARKS
**         
*/
void GeneralDistributionStatsExcept::RemoveAllExceptions(void)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=ExceptionValues.begin(); iternumvec<ExceptionValues.end(); iternumvec++)
    helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    RemoveException(*iternumvec);
}

/*F EvenDistributionStatsExcept::AddException(value) . . . . . . . . . . . Add exception
**
**  DESCRIPTION
**     value: The element to be put on the ExceptionValues Vector
**
**
**  REMARKS
**     The value is added to ExceptionValues only if it belongs to Values!!
*/
void EvenDistributionStatsExcept::AddException(const double& value)
{
  while(find(Values.begin(), Values.end(), value) != Values.end())
    //    if(find(Values.begin(), Values.end(), value) != Values.end())
      {
        ExceptionValues.AddObject(value);
        
        // SortedExceptionValues
             SortedExceptionValues.AddObject(value);
        sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

        RemoveValue(value, false);      // delete only one occurence
                                             if (IntervalEnd > Max)
                                               IntervalEnd = Max;
        CountFrequencies();
      }
}

/*F EvenDistributionStatsExcept::AddExceptionsFrom(value)  . . . . . . Add exception
**
**  DESCRIPTION
**     All elements greater or equal than value are removed from 
**     Values and Added to ExceptionValues
**
**  REMARKS
*/
void EvenDistributionStatsExcept::AddExceptionsFrom(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=Values.begin(); iternumvec<Values.end(); iternumvec++)
    if (*iternumvec >= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    AddException(*iternumvec);
}

/*F EvenDistributionStatsExcept::AddExceptionsTo(value)  . . . . . . Add exception
**
**  DESCRIPTION
**     All elements less or equal than value are removed from 
**     Values and Added to ExceptionValues
**
**  REMARKS
*/
void EvenDistributionStatsExcept::AddExceptionsTo(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=Values.begin(); iternumvec<Values.end(); iternumvec++)
    if (*iternumvec <= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    AddException(*iternumvec);
}

/*F EvenDistributionStatsExcept::RemoveException(value) . . . . . . . . . remove exception
**
**  DESCRIPTION
**     value: The element to be removed from the ExceptionValues Vector
**         and added to Values
**
**  REMARKS
**         
*/
void EvenDistributionStatsExcept::RemoveException(const double& value)
{
  VectorNumeric::iterator location;

  location = find(ExceptionValues.begin(), ExceptionValues.end(), value);
    
  if(location != ExceptionValues.end())
    {
      ExceptionValues.erase(location);
                
      // SortedExceptionValues:
        SortedExceptionValues = ExceptionValues;
        sort(SortedExceptionValues.begin(), SortedExceptionValues.end());

        AddValue(value);
        if (IntervalSize == 0)  // if there has been only one element before!
                                              IntervalSize = Max - Min;
        CountFrequencies();
    }
}

/*F EvenDistributionStatsExcept::RemoveExceptionsFrom(value)  . . . . . . remove exception
**
**  DESCRIPTION
**     All elements greater or equal than value are removed from 
**     ExceptionValues and Added to Values
**
**  REMARKS
*/
void EvenDistributionStatsExcept::RemoveExceptionsFrom(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=ExceptionValues.begin(); iternumvec<ExceptionValues.end(); iternumvec++)
    if (*iternumvec >= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    RemoveException(*iternumvec);
}

/*F EvenDistributionStatsExcept::RemoveExceptionsTo(value)  . . . . . . remove exception
**
**  DESCRIPTION
**     All elements less or equal than value are removed from 
**     ExceptionValues and Added to Values
**
**  REMARKS
*/
void EvenDistributionStatsExcept::RemoveExceptionsTo(const double& value)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=ExceptionValues.begin(); iternumvec<ExceptionValues.end(); iternumvec++)
    if (*iternumvec <= value)
      helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    RemoveException(*iternumvec);
}

/*F EvenDistributionStatsExcept::RemoveAllExceptions() . . . . . . . . . remove exception
**
**  DESCRIPTION
**
**  REMARKS
**         
*/
void EvenDistributionStatsExcept::RemoveAllExceptions(void)
{
  VectorNumeric::iterator iternumvec;
  VectorNumeric helpnumvec;

  for (iternumvec=ExceptionValues.begin(); iternumvec<ExceptionValues.end(); iternumvec++)
    helpnumvec.AddObject(*iternumvec);

  for (iternumvec=helpnumvec.begin(); iternumvec<helpnumvec.end(); iternumvec++)
    {
      RemoveException((*iternumvec));
    }
}


/*IO EvenDistributionStats::WriteCounts2File . . . . . . . . . . . . . . . . . . . . . Write to File
**
**  DESCRIPTION
**    Writes two rows (left Intervalborders and belonging Counts) to a file
**
**  REMARKS
*/
SYS_RETURN EvenDistributionStats::WriteCounts2File(ostream& out)
{
  unsigned int i;
  
  for (i=0; i<Counts.size(); i++)
    {
      out << IntervalBegin + IntervalSize * i << " ";
      out << Counts[i] << endl;
    }

  return 0;
}

/*IO EvenDistributionStats::WriteCountsNormalized2File . . . . . . . . . . . . . . . . . . . . . Write to File
**
**  DESCRIPTION
**    Writes two rows (left Intervalborders and belonging Counts) to a file
**    Normalized Values are writen out.
**
**  REMARKS
**    Normalized in the sense that the sum under the distribution is equal to 1
*/
SYS_RETURN EvenDistributionStats::WriteCountsNormalized2File(ostream& out)
{
  unsigned int i;
  double sum=0;
  for (i=0; i<Counts.size(); i++)
    sum+=Counts[i];

  cout << "SUMME: " << sum << endl;
  for (i=0; i<Counts.size(); i++)
    {
      out << IntervalBegin + IntervalSize * i << " ";
      out << Counts[i]/sum << endl;
    }

  return 0;
}
