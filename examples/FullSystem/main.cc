/*  File     main.cc
**  PACKAGE     REACTION    
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  REACTION Project / Edward S. Blurock 
*/
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#define TEMPLATE_INSTANTIATION
#include "FullSystem.hh"

/*F ans = main(argc,argv) . . . . . . . . . . . . . . . . .  the main routine
**
**  DESCRIPTION
**    
**  REMARKS
**
*/
int main(int argc, char *argv[])
{
  AnalysisSystemSave test(argc,argv);
  test.Initialization();
  test.Run();
  test.Exit();

  return 0;
  
}
