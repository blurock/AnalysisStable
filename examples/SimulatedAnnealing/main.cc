/*  FILE     main.cpp
**  PACKAGE  SimulatedAnnealing    
**  AUTHOR   
**
**  CONTENT
**    test program for SimulatedAnnealing package
**
**  REFERENCES
**
*/
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
//#include "CommBuffer.hh"
//#include "String.hh"
//#include "Objects.hh"
//#include "Vector.hh"

#include "CoreDataObjects.hh"
#include "NumericObjects.hh"
#include "LogicalObjects.hh"
#include "FunctionReal1DObjects.hh"
#include "OperationObjects.hh"
#include "DataObjects.hh"
#include "InstanceObjects.hh"
#include "MenuObjects.hh"
//#include "PredicateObjects.hh"
#include "DirectedTreeObjects.hh"
#include "SelectObjects.hh"
#include "AlgorithmObjects.hh"

#include "InstanceAlgorithms.hh"
// #include "PredicateObjects.hh"

//#include "CommBuffer.hh"
//#include "String.hh"
//#include "Vector.hh"
//
//#include "System.hh"
//#include "MatrixNumeric.hh"
//#include "BasicLaTeXTable.hh"
//#include "MatrixOut.hh"
//#include "PrimitiveStats.hh"

//#include "ReadData.hh"

#include <string>


#ifdef _unix
#include "unix.hh"
#endif

#include "SimulatedAnnealing.hh"



///*C TestFunction1
//**
//**  DESCRIPTION
//**        
//**  REMARKS
//**
//*/
//class TestFunction1 : public BaseDataFunctionToOptimize
//{
//public:
//  TestFunction1() {};
//  TestFunction1(ALLOC_INT *par_dimension,
//      double *par_lower_bound, 
//      double *par_upper_bound, 
//      double *cost_par,
//      double *cost_tan,
//      int *par_int_real)
//      :    BaseDataFunctionToOptimize(par_dimension,
//                  par_lower_bound, 
//                  par_upper_bound, 
//                  cost_par,
//                  cost_tan,
//                  par_int_real)
//	{
//	}
//  TestFunction1(ALLOC_INT *par_dimension,
//      BaseDataSimAnnUpperLower *upLow, 
//      VectorNumeric *parVec,
//      double *cost_tan,
//      int *par_int_real)
//      :    BaseDataFunctionToOptimize(par_dimension,
//                  upLow, 
//                  parVec,
//                  cost_tan,
//                  par_int_real)
//	{
//	}
//
//	virtual BaseDataReal operator()(VectorNumeric *x)
//	{
//    double q_n, d_i, s_i, t_i, z_i, c_r;
//    int k_i;
//    LONG_INT i, j;
//    static LONG_INT funevals = 0;
//
//    s_i = 0.2;
//    t_i = 0.05;
//    c_r = 0.15;
//
//    q_n = 0.0;
//
//    for (i = 0; i < 4; ++i) {
////    for (i = 0; i < *parameter_dimension; ++i) {
//      j = i % 4;
//      switch (j) {
//        case 0:
//          d_i = 1.0;
//          break;
//        case 1:
//          d_i = 1000.0;
//          break;
//        case 2:
//          d_i = 10.0;
//          break;
//        default:
//          d_i = 100.0;
//      }
//      if (x->at(i) > 0.0) {
//        k_i = (int) (x->at(i) / s_i + 0.5);
//      }
//      else if (x->at(i) < 0.0) {
//        k_i = (int) (x->at(i) / s_i - 0.5);
//      }
//      else {
//        k_i = 0;
//      }
//
//      if (fabs (k_i * s_i - x->at(i)) < t_i) {
//        if (k_i < 0) {
//          z_i = k_i * s_i + t_i;
//        }
//        else if (k_i > 0)	{
//          z_i = k_i * s_i - t_i;
//        }
//        else {
//          z_i = 0.0;
//        }
//        q_n += c_r * d_i * z_i * z_i;
//      }
//      else {
//        q_n += d_i * x->at(i) * x->at(i);
//      }
//    }
//
//    funevals = funevals + 1;
//
//#if TIME_CALC
//    if ((PRINT_FREQUENCY > 0) && ((funevals % PRINT_FREQUENCY) == 0))	{
//      fprintf (ptr_out, "funevals = %ld  ", funevals);
//      print_time ("", ptr_out);
//    }
//#endif
//    
////    cout << "returnvalue: " << q_n << endl;
//    
//    
//    BaseDataReal r;
//    r.SetValue(q_n);
//    
//    return (r);
//  };
//}; // end class TestFunction1


/*C TestFunction2
**
**  DESCRIPTION
**        
**  REMARKS
**
*/
//class TestFunction2 : public FunctionToOptimize
//{
//public:
//    TestFunction2(ALLOC_INT *par_dimension,
//				double *par_lower_bound, 
//				double *par_upper_bound, 
//				double *cost_par,
//				double *cost_tan,
//				int *par_int_real)
//				:    FunctionToOptimize(par_dimension,
//										par_lower_bound, 
//										par_upper_bound, 
//										cost_par,
//										cost_tan,
//										par_int_real)
//	{
//	}
//
//	virtual double operator()(double *x)
//	{
//	static VASLModelOptimize voestModelToOpt;
//
//	static unsigned int flag = 0;
//	if (flag==0)	// fill in data matrix
//	{
//		cout << "read input files____________________________" << endl << endl;	
//		String nameFile1 = "c:/home/wahl/REFORM_ALT/work/data/voest_data3_1_5stiche.inp";
//		String nameFile2 = "c:/home/wahl/REFORM_ALT/work/data/voest_data3_2_5stiche.inp";
////		String nameFile1 = "c:/home/reform/work/data/voest_data1_test_calcAll_2data.inp";
////		String nameFile2 = "c:/home/reform/work/data/voest_data2_test_calcAll_2data.inp";
//		ifstream voestin1(nameFile1.chars());
//		ifstream voestin2(nameFile2.chars());
//		voestModelToOpt.fillInData(voestin1, voestin2);
//		voestin1.close();
//		voestin2.close();
//		cout << "read input files____________________________done" << endl << endl;	
//		flag++;
//	}
//
//	for (unsigned int j = 0; j < *parameter_dimension; j++)
//	{
//		voestModelToOpt.setxParameter(j, x[j]);
//	}
//
//	return voestModelToOpt.calculateAll();  // voestModelToOpt global defined!
//		return 0;
//	};
//}; // end class TestFunction2




// Prototypes
int simTest(ReactionSystemBase *g);
int operationTest(ReactionSystemBase *g);

int encodeTest(ReactionSystemBase *g); 
int encodeItTest(CommBuffer& outbuffer);
int decodeItTest(CommBuffer& outbuffer);


class SimulatedAnnealingTest : public AlgorithmSystemSave
{
public:

// Constructor
	SimulatedAnnealingTest(int argc, char *argv[]) 
	: AlgorithmSystemSave(argc, argv)
	{
		SingleSystemCommand simtest("simTest",
									"Test of Simulated Annealing",
									 &simTest);
		SingleSystemCommand operationtest("operationTest",
									   "Test of Operations",
									   &operationTest);
		SingleSystemCommand encodetest("encodeTest",
									   "Test of Encode/Decode",
									   &encodeTest);
		Commands.AddObject("simTest", simtest);
		Commands.AddObject("operationTest", operationtest);
		Commands.AddObject("encodeTest", encodetest);
		cout << endl;
		PrintCommandList(this);
		cout << endl << endl;
	}
  void CommandSetUp()
    {
      AlgorithmSystemSave::CommandSetUp();
    }
  void EncodeDecodeObjectsSetUp()
    {
      AlgorithmSystemSave::EncodeDecodeObjectsSetUp();
      InitialSetOfDataObjectsEncodeDecodeRoutines();
      InitialSetOfDirectedTreesEncodeDecodeRoutines();
      InitialSetOfSelectionTreeEncodeDecodeRoutines();
      InitialSetOfAlgorithmObjectsEncodeDecodeRoutines();
      InitialInstanceAlgorithmsEncodeDecodeRoutines();
      InitialSetOfInstanceEncodeDecodeRoutines();
//      InitialSetOfPredicateEncodeDecodeRoutines();
      
      InitialSimAnnAlgorithmsEncodeDecodeRoutines();
    }
  void StandardObjectsSetUp()
    {
      AlgorithmSystemSave::StandardObjectsSetUp();
      AddBaseAlgorithmClasses(getStandard());
      AddSelectionTreeClasses(getStandard());
      AddDirectedTreeObjects(getStandard());
      AddInstanceAlgorithmsClasses(getStandard());
//      AddPredicateClasses(getStandard());
      AddInstanceClasses(getStandard());
      
      AddSimAnnAlgorithmsClasses(getStandard());
    }
}; // SimulatedAnnealingTest



int main(int argc, char *argv[])
{
	cout << "\n================= SimulatedAnnealingTest ===============\n";
	SimulatedAnnealingTest test(argc, argv);
  test.Initialization();
  test.Run();
  test.Exit();
  
	return 0;
}


int encodeTest(ReactionSystemBase *g)
{
	cout << "encodeTest:_____________________________________\n";
	ReactionSystemLevel1 *global = (ReactionSystemLevel1 *) g;

	CommBuffer outbuffer(COMM_BUFF_ENCODE,50,200);
	encodeItTest(outbuffer);
	decodeItTest(outbuffer);

	return 0;
}
int encodeItTest(CommBuffer& outbuffer)
{
	cout << "EncodeIt Test\n";
	cout << "============================================\n\n";

  VectorNumeric up;
	up.AddObject(10000);
	up.AddObject(9000);
	up.AddObject(8000);
	up.AddObject(7000);

  VectorNumeric low;
	low.AddObject(-10000);
	low.AddObject(-9000);
	low.AddObject(-8000);
	low.AddObject(-7000);

  BaseDataSimAnnUpperLower uplow(up, low);

	cout << "before encode:\n";
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++\n";
	uplow.print(cout); cout << "\n\n";

	uplow.EncodeThis(outbuffer);
	cout << "\n\n\n";
	return 0;
}



int decodeItTest(CommBuffer& outbuffer)
{
	cout << "DecodeIt Test\n";
	cout << "============================================\n\n";
	CommBuffer inbuffer(outbuffer.GetBuffer(),
			 outbuffer.GetBufferSize());

  BaseDataSimAnnUpperLower ul;

	ul.DecodeThis(inbuffer);

	cout << "after decode:\n";
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++\n";
	ul.print(cout); cout << "\n\n";
	cout << "\n\n\n";
	return 0;
}


int simTest(ReactionSystemBase *g)
{
	cout << "\n================= simTest start =========\n";
	ReactionSystemLevel1 *global = (ReactionSystemLevel1 *) g;

			ALLOC_INT *par_dimension;
			double *par_lower_bound, *par_upper_bound, *cost_par, *cost_tan;
			int *par_int_real;
			

		  if ((par_dimension =
			   (ALLOC_INT *) calloc (1, sizeof (ALLOC_INT))) == NULL)
			exit (9);
			
				
//		  *par_dimension = 19;
		  *par_dimension = 4;


		  if ((par_lower_bound = (double *) calloc (*par_dimension, sizeof (double)) ) == NULL)
			  exit (9);
		  if ((par_upper_bound = (double *) calloc (*par_dimension, sizeof (double)) ) == NULL)
			  exit (9);
		  if ((cost_par = (double *) calloc (*par_dimension, sizeof (double)) ) == NULL)
			  exit (9);
		  if ((cost_tan = (double *) calloc (*par_dimension, sizeof (double)) ) == NULL)
			  exit (9);
		  if ((par_int_real = (int *) calloc (*par_dimension, sizeof (int)) ) == NULL)
			  exit (9);
//      par_lower_bound[0]=	6.800;
//      par_lower_bound[1]=	0.004;
//      par_lower_bound[2]=	0.570;
//      par_lower_bound[3]=	0.690;
//      par_lower_bound[4]=	1.100;
//      par_lower_bound[5]=	0.760;
//      par_lower_bound[6]=	0.100;
//      par_lower_bound[7]=	0.980;
//      par_lower_bound[8]=	1.500;
//      par_lower_bound[9]=	1.100;
//      par_lower_bound[10]=	0.500;
//      par_lower_bound[11]=	0.000;
//      par_lower_bound[12]=	0.030;
//      par_lower_bound[13]=	0.100;
//      par_lower_bound[14]=	99.0;
//      par_lower_bound[15]=	0.300;
//      par_lower_bound[16]=	0.0781;
//      par_lower_bound[17]=	0.118;
//      par_lower_bound[18]=	1.0;
//
//      par_upper_bound[0]=	7.000;
//      par_upper_bound[1]=	0.006;
//      par_upper_bound[2]=	0.590;
//      par_upper_bound[3]=	0.710;
//      par_upper_bound[4]=	1.300;
//      par_upper_bound[5]=	0.780;
//      par_upper_bound[6]=	0.300;
//      par_upper_bound[7]=	1.000;
//      par_upper_bound[8]=	1.600;
//      par_upper_bound[9]=	1.300;
//      par_upper_bound[10]=1.200;
//      par_upper_bound[11]=0.001;
//      par_upper_bound[12]=0.050;
//      par_upper_bound[13]=0.150;
//      par_upper_bound[14]=101.0;
//      par_upper_bound[15]=0.400;
//      par_upper_bound[16]=0.0781;
//      par_upper_bound[17]=0.118;
//      par_upper_bound[18]=1.0;
//
//      cost_par[0]=6.900;
//      cost_par[1]=0.005;
//      cost_par[2]=0.580;
//      cost_par[3]=0.700;
//      cost_par[4]=1.200;
//      cost_par[5]=0.770;
//      cost_par[6]=0.200;
//      cost_par[7]=0.990;
//      cost_par[8]=1.5724;
//      cost_par[9]=1.2012;
//      cost_par[10]=0.819;
//      cost_par[11]=0.00083;
//      cost_par[12]=0.04;
//      cost_par[13]=0.125;
//      cost_par[14]=100.0;
//      cost_par[15]=0.32;
//      cost_par[16]=0.0781;
//      cost_par[17]=0.118;
//      cost_par[18]=1.0;


  	VectorNumeric *parVec = new VectorNumeric(*par_dimension);
  	VectorNumeric *costTanVec = new VectorNumeric(*par_dimension);
  	VectorNumeric *parIntRealVec = new VectorNumeric(*par_dimension);
    
	  ALLOC_INT index;
	  for (index = 0; index < *par_dimension; ++index)
	  {
      par_int_real[index] = REAL_TYPE;
      par_lower_bound[index] = -10000.0;
      par_upper_bound[index] = 10000.0;      
      cost_tan[index] = 0.0;
      
      costTanVec->at(index) = 0.0;
      parIntRealVec->at(index) = REAL_TYPE;
	  }

	 for (index = 0; index < *par_dimension / 4.0; ++index)
		{
		  cost_par[4 * (index + 1) - 4] = 999.0;
		  cost_par[4 * (index + 1) - 3] = -1007.0;
		  cost_par[4 * (index + 1) - 2] = 1001.0;
		  cost_par[4 * (index + 1) - 1] = -903.0;

		  parVec->at(4 * (index + 1) - 4) = 999.0;
		  parVec->at(4 * (index + 1) - 3) = -1007.0;
		  parVec->at(4 * (index + 1) - 2) = 1001.0;
		  parVec->at(4 * (index + 1) - 1) = -903.0;
		}


//	cout << "BEFORE CONSTRUCTOR: " << endl;
//	cout << "par_dimension " << *par_dimension << endl;
//	for (index=0; index<*par_dimension; index++)
//	{
//		cout << "cost_par " << cost_par[index] << endl;
//		cout << "par_lower_bound " << par_lower_bound[index] << endl;
//		cout << "par_upper_bound " << par_upper_bound[index] << endl;
//		cout << "par_int_real " << par_int_real[index] << endl << endl;
//	}


  
//	TestFunction1 testFkt(par_dimension, par_lower_bound, par_upper_bound,
//						cost_par, cost_tan, par_int_real);

  VectorNumeric upper(*par_dimension);
  VectorNumeric lower(*par_dimension);
  ObjectList<String> names(*par_dimension);

  for(int j=0; j<*par_dimension; j++) {
    upper.at(j) = par_upper_bound[j];
    lower.at(j) = par_lower_bound[j];
    String str("Parametername");
    names.AddObject(str);
  }

  BaseDataSimAnnUpperLower *upLow = new BaseDataSimAnnUpperLower(upper, 
                                                                 lower);
  
	TestFunction1 testFkt(par_dimension, 
                        upLow,
                        parVec, 
                        costTanVec, 
                        parIntRealVec);


//	TestFunction2 testFkt(par_dimension, par_lower_bound, par_upper_bound,
//						cost_par, cost_tan, par_int_real);

	cout << "parameter_dimension " << testFkt.TheParToFct->parameter_dimension[0] << endl;
	parVec->print(cout);
	cout << endl;
	for (int ii=0; ii<testFkt.TheParToFct->parameter_dimension[0]; ii++)
	{
		cout << "cost_parameters " << testFkt.TheParToFct->cost_parameters[ii] << endl;
		cout << "parameter_lower_bound " << testFkt.TheParToFct->parameter_lower_bound[ii] << endl;
		cout << "parameter_upper_bound " << testFkt.TheParToFct->parameter_upper_bound[ii] << endl;
		cout << "cost_tangents " << testFkt.TheParToFct->cost_tangents[ii] << endl;
		cout << "parameter_int_real " << testFkt.TheParToFct->parameter_int_real[ii] << endl << endl;
	}

	SimulatedAnnealing 	sa(&testFkt);
	sa.parAsaRun->USER_OPTIONS->Limit_Generated = 99999;
//  sa.USER_OPTIONS->ASA_TEST = 1;
  sa.calculate();
  
	cout << "\nAFTER RUN: "  << endl;
	cout << "parameter_dimension ";
	cout << sa.fToUse->TheParToFct->parameter_dimension[0] << endl;
	for (int i=0; i<sa.fToUse->TheParToFct->parameter_dimension[0]; i++)
	{
		cout << "cost_parameters " << sa.fToUse->TheParToFct->cost_parameters[i] << endl;
		cout << "parameter_lower_bound " << sa.fToUse->TheParToFct->parameter_lower_bound[i] << endl;
		cout << "parameter_upper_bound " << sa.fToUse->TheParToFct->parameter_upper_bound[i] << endl;
		cout << "cost_tangents " << sa.fToUse->TheParToFct->cost_tangents[i] << endl;
		cout << "cost_curvature " << sa.cost_curvature[i] << endl;
		cout << "parameter_int_real " << sa.fToUse->TheParToFct->parameter_int_real[i] << endl;
	}
	#if OPTIONS_FILE_DATA
		cout << "ptr_options " << saptr_options << endl;
	#endif

	cout << "\n================= simTest end ===========\n";
	return 0;
}


int operationTest(ReactionSystemBase *g)
{
	ReactionSystemLevel1 *global = (ReactionSystemLevel1 *) g;

	return 0;
}

