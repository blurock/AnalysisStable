/*  FILE     FullSystemType.hh
**  PACKAGE  FullSystem
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "FullSystem" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 CoreObjects Project, RISC Linz
*/
 
#ifndef CoreObjects_FULLSYSTEMTYPE_HH
#define CoreObjects_FULLSYSTEMTYPE_HH

class AnalysisSystemSave : public GoalSystemSave
{
public:
  AnalysisSystemSave(int argc, char *argv[])
    : GoalSystemSave(argc,argv)
    {
    }
  virtual void EncodeDecodeObjectsSetUp();
  virtual void StandardObjectsSetUp();
  virtual void CommandSetUp();
  virtual int Run();
  void loadInput(String line);
  
};
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/

#endif
