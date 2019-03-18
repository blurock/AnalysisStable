/*F obj = operator()(x,y,xclass,yclass) . . . . . . . . . . BaseData=Object=
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseData=Object=::operator()(BaseDataObject *x, BaseDataObject *y,
					     DataObjectClass *xc, DataObjectClass *yc)
{
  return operator()(x,xc);
}
/*F obj = operator()(x,xclass)  . . . . . . . . . . . . . . BaseData=Object=
**
**  DESCRIPTION
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a one-dimensional call.  An object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseData=Object=::operator()(BaseDataObject *x,
					     DataObjectClass *xc)
{
  return (BaseDataObject *) x->Clone();
}
/*F obj = operator()(cls,x,y,xclass,yclass) . . . . . . . . . . BaseData=Object=
**
**  DESCRIPTION
**    x,y: The objects to be operated on
**    xclass,yclass: The object classes
**    obj: The result
**
**    This is a two-dimensional call.  An object is created.
**    The cls is used (among other things) to check the input types
**
**  REMARKS
**
*/
BaseDataObject *BaseData=Object=::operator()(DataObjectClass *cls,
						  BaseDataObject *x, BaseDataObject *y,
						  DataObjectClass *xc, DataObjectClass *yc)
                                              
{
  /*
    DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) cls->PointerToAllowedClasses();
    bool result = true;
    result = result && set->IsOfClass(xc,_NAME);
    result = result && set->IsOfClass(yc,_NAME);
    result = result && (x->GetType() == xc->GetType());
    result = result && (y->GetType() == yc->GetType());
  */
  return operator()(x,y,xc,yc);
}
/*F obj = operator()(cls,x,xclass)  . . . . . . . . . . . . . . BaseData=Object=
**
**  DESCRIPTION
**    cls: The class of the operation
**    x: The object to be operated on
**    xclass: The class of the object
**    obj: The result
**
**    This is a dummy one-dimensional call.  An empty object is created.
**
**  REMARKS
**
*/
BaseDataObject *BaseData=Object=::operator()(DataObjectClass *cls,
						  BaseDataObject *x,
						  DataObjectClass *xclass)
{
  /*
    DataSetOfObjectsClass *set = (BaseDataSetOfObjects *) cls->PointerToAllowedClasses();
    bool result = true;
    result = result && set->IsOfClass(xc,_NAME);
    result = result && (x->GetType() == xc->GetType());
  */
  return operator()(x,xclass);
}
