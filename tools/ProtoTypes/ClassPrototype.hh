/*C BaseData=Object=  . . . . . . . . . . . . . . . . . . . . . . .  data
**
**  DESCRIPTION
**    This is the =Object= class definitions
**
**  REMARKS
**    Inheirits BaseData=SubClass=
*/
class BaseData=Object= : public BaseData=SubClass=
{
public:
  BaseData=Object=();
  BaseData=Object=(const BaseData=Object=& data);

  STANDARD_VIRTUAL_METHODS_OBJECT
};
/*C Data=Object=Class . . . . . . . . . . . .  the info about a data type
**
**  DESCRIPTION
**
**  REMARKS
**     Inheirits Data=SubClass=Class
*/
class Data=Object=Class : public Data=SubClass=Class
{
public:
  Data=Object=Class();
  Data=Object=Class(const Data=Object=Class& data);
  Data=Object=Class(const int id, 
		    const String& name,
		    const String& descr);
  STANDARD_VIRTUAL_METHODS_CLASS
};

