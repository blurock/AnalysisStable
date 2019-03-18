/*  FILE     CommBuffer.cc
**  PACKAGE  BASIS
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    
**
**  REFERENCES
**
**  COPYRIGHT (C) 1995  Basis Library / Edward S. Blurock 
*/
 
/*I  . . . INCLUDES  . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
*/
#include "CommBuffer.hh" 

/*S Utility
 */
/*F IncreaseBuffer()  . . . . . . . . . . . . . . . . increase size of buffer
**
**  DESCRIPTION
**    Increase the size of buffer by BufferIncrement
**
**  REMARKS
**
*/
void CommBuffer::IncreaseBuffer()
{
#ifndef _noxdr
  int NewBufferSize = BufferSize + BufferIncrement;
  char *  NewBuffer = (char *) malloc(NewBufferSize);
  unsigned int BufferUsed = (unsigned int) xdr_getpos(Xdr);
  XDR * XdrNew = (XDR *) malloc(sizeof(XDR));
  xdrmem_create(XdrNew,NewBuffer,NewBufferSize,XDR_Direction);
     
  xdr_opaque(XdrNew,Buffer,BufferUsed);
  BufferSize = NewBufferSize;
  xdr_destroy(Xdr);
  free(Buffer);
  Buffer = NewBuffer;
  Xdr = XdrNew;
#else

  int NewBufferSize = BufferSize + BufferIncrement;
  char * NewBuffer = (char *) malloc(NewBufferSize);
  unsigned int BufferUsed = Xdr->BufferUsed;
     
  XDR *XdrNew = (XDR *) malloc(sizeof(XDR));
  xdrmem_create(XdrNew,NewBuffer,NewBufferSize,XDR_Direction);

  memcpy(NewBuffer, Buffer, BufferUsed);
  BufferSize = NewBufferSize;
  XdrNew->BufferLeft = NewBufferSize - BufferUsed;
  XdrNew->BufferUsed = BufferUsed;
  free(Buffer);
  Buffer = NewBuffer;
  Xdr = XdrNew;
#endif
}
 
/*f xdrmem_create(xdrs,addr_Buffer,size,op) . . . . . dummy routine if no XDR
**
**  DESCRIPTION
**    xdrs: The structure
**    addr_Buffer: The address of the buffer
**    size: The size of the buffer
**    op: The operation type
**
**  REMARKS
**
*/
void xdrmem_create(XDR *xdrs,char * addr_Buffer,unsigned int  size,unsigned int  op)
{       

#ifdef _noxdr

  xdrs->Buffer = addr_Buffer;
  xdrs->BufferUsed = 0;
  xdrs->BufferLeft = size;
  xdrs->Direction = op;
#endif

}
/*S EncodeDecode
*/ 
/*F ans = Encode(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . . int
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be encoded into buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Encode(CommBuffer& buffer, int i)
{
  return Pack(buffer,i);
}
/*F ans = Decode(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . . int
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be decoded from buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Decode(CommBuffer& buffer, int &i)
{
  return Unpack(buffer,i);
}
 
/*F ans = Encode(buffer,i)  . . . . . . . . . . . . . . . . . .  unsigned int
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be encoded into buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Encode(CommBuffer& buffer, unsigned int i)
{
  return Pack(buffer,i);
}
 
/*F ans = Decode(buffer,i)  . . . . . . . . . . . . . . . . . .  unsigned int
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be decoded from buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Decode(CommBuffer& buffer, unsigned int &i)
{
  return Unpack(buffer,i);
}
/*F ans = Encode(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . short
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be encoded into buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Encode(CommBuffer& buffer, short i)
{
  return Pack(buffer,i);
}
 
/*F ans = Decode(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . short
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be decoded from buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Decode(CommBuffer& buffer, short &i)
{
  return Unpack(buffer,i);
}
/*F ans = Encode(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . float
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be encoded into buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Encode(CommBuffer& buffer, float i)
{
  return Pack(buffer,(float) i);
}
/*F ans = Decode(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . float
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be decoded from buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Decode(CommBuffer& buffer, float &i)
{
  return Unpack(buffer,i);
}
/*F ans = Encode(buffer,i)  . . . . . . . . . . . . . . . . . . . . .  double
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be encoded into buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Encode(CommBuffer& buffer, double i)
{
  return Pack(buffer,i);
}
 
/*F ans = Decode(buffer,i)  . . . . . . . . . . . . . . . . . . . . .  double
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be decoded from buffer
**    ans: true if successful
**    
**  REMARKS
**
*/
extern bool Decode(CommBuffer& buffer, double &i)
{
  return Unpack(buffer,i);
}
/*F ans = Encode(buffer,string) . . . . . . . . .  pointer to string (char**)
**
**  DESCRIPTION
**    buffer: The buffer class
**    string: The pointer to the string (ending with null character)
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Encode(CommBuffer& buffer, char** string)
{

  return Pack(buffer,string);
}
/*F ans = Decode(buffer,string) . . . . . . . . . . . . . . . . . . .  char**
**
**  DESCRIPTION
**    buffer: The buffer class
**    string: The pointer to the string
**    ans: True if successful
**
**  REMARKS
**
*/
extern bool Decode(CommBuffer& buffer, char** string)
{
  return Unpack(buffer,string);
}
/*S PackUnpack
 */
/*F ans = Pack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . . . int
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be packed into buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, int i)
{
#ifndef _noxdr
  if(buffer.IsStoring())
    {
      unsigned int BufferUsed = (unsigned int) xdr_getpos(buffer.Xdr);
      if(xdr_int(buffer.Xdr,&i))
        return true;
      else
        {
          xdr_setpos(buffer.Xdr,BufferUsed);
          if(buffer.IncreaseBufferMode)
            {
              buffer.IncreaseBuffer();
              return xdr_int(buffer.Xdr,&i);
            }
          else
            return false;
        }
    }
  else
    return false;
#else
  //wh change
      unsigned int s = sizeof(int); 

  

  //    if(buffer.Xdr->BufferLeft < s)

    while(buffer.Xdr->BufferLeft < s)

      buffer.IncreaseBuffer();
  memcpy(buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, &i,s);
                
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
 
/*F ans = Unpack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . . int
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be unpacked from buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Unpack(CommBuffer& buffer, int& i)
{
#ifndef _noxdr
  if(buffer.IsReading())
    return xdr_int(buffer.Xdr,&i);
  else 
    return false;
#else
  //wh change   
      unsigned int s = sizeof(int);
  memcpy(&i,buffer.Xdr->Buffer + buffer.Xdr->BufferUsed,s);
        
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
/*F ans = Pack(buffer,i)  . . . . . . . . . . . . . . . . . . .  unsigned int
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be packed into buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, unsigned int i)
{
#ifndef _noxdr
  if(buffer.IsStoring())
    {
      unsigned int BufferUsed = (unsigned int) xdr_getpos(buffer.Xdr);
      if(xdr_u_int(buffer.Xdr,&i))
        return true;
      else
        {
          xdr_setpos(buffer.Xdr,BufferUsed);
          if(buffer.IncreaseBufferMode)
            {
              buffer.IncreaseBuffer();
              return xdr_u_int(buffer.Xdr,&i);
            }
          else
            return false;
        }
    }
  else
    return false;
#else
  //wh change
      unsigned int s = sizeof(unsigned int);
  while(buffer.Xdr->BufferLeft < s)

    //  if(buffer.Xdr->BufferLeft < s)

      buffer.IncreaseBuffer();
  memcpy(buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, &i,s);
                
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
 
/*F ans = Unpack(buffer,i)  . . . . . . . . . . . . . . . . . .  unsigned int
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be unpacked from buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Unpack(CommBuffer& buffer, unsigned int& i)
{
#ifndef _noxdr
  if(buffer.IsReading())
    return xdr_u_int(buffer.Xdr,&i);
  else 
    return false;
#else
  //wh change   
      unsigned int s = sizeof(unsigned int);
  memcpy(&i,buffer.Xdr->Buffer + buffer.Xdr->BufferUsed,s);
        
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
/*F ans = Pack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . . short
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be packed into buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, short i)
{
#ifndef _noxdr
  if(buffer.IsStoring())
    {
      unsigned int BufferUsed = (unsigned int) xdr_getpos(buffer.Xdr);
      if(xdr_short(buffer.Xdr,&i))
        return true;
      else
        {
          xdr_setpos(buffer.Xdr,BufferUsed);
          if(buffer.IncreaseBufferMode)
            {
              buffer.IncreaseBuffer();
              return xdr_short(buffer.Xdr,&i);
            }
          else
            return false;
        }
    }
  else
    return false;
#else
  //wh change
      unsigned int s = sizeof(short);
  while(buffer.Xdr->BufferLeft < s)

    //  if(buffer.Xdr->BufferLeft < s)

      buffer.IncreaseBuffer();
  memcpy(buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, &i,s);
                
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
 
/*F ans = Unpack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . short
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be unpacked from buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Unpack(CommBuffer& buffer, short& i)
{
#ifndef _noxdr
  if(buffer.IsReading())
    return xdr_short(buffer.Xdr,&i);
  else 
    return false;
#else
  //wh change   
      unsigned int s = sizeof(short);
  memcpy(&i,buffer.Xdr->Buffer + buffer.Xdr->BufferUsed,s);
        
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}

/*F ans = Pack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . . float
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be packed into buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, float i)
{
#ifndef _noxdr
  if(buffer.IsStoring())
    {
      unsigned int BufferUsed = (unsigned int) xdr_getpos(buffer.Xdr);
      if(xdr_float(buffer.Xdr,&i))
        return true;
      else
        {
          xdr_setpos(buffer.Xdr,BufferUsed);
          if(buffer.IncreaseBufferMode)
            {
              buffer.IncreaseBuffer();
              return xdr_float(buffer.Xdr,&i);
            }
          else
            return false;
        }
    }
  else
    return false;
#else
  //wh change
      unsigned int s = sizeof(float);
  while(buffer.Xdr->BufferLeft < s)

    //  if(buffer.Xdr->BufferLeft < s)

      buffer.IncreaseBuffer();
  memcpy(buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, &i,s);
        
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
 
/*F ans = Unpack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . . float
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be unpacked from buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Unpack(CommBuffer& buffer, float& i)
{
#ifndef _noxdr
  if(buffer.IsReading())
    return xdr_float(buffer.Xdr,&i);
  else 
    return false;
#else
  //wh change   
      unsigned int s = sizeof(float);
  memcpy(&i,buffer.Xdr->Buffer + buffer.Xdr->BufferUsed,s);
        
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
/*F ans = Pack(buffer,i)  . . . . . . . . . . . . . . . . . . . . . .  double
**
**  DESCRIPTION
**    buffer: The buffer class (as output)
**    i: to be packed into buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, double i)
{
#ifndef _noxdr
  if(buffer.IsStoring())
    {
      unsigned int BufferUsed = (unsigned int) xdr_getpos(buffer.Xdr);
      if(xdr_double(buffer.Xdr,&i))
        return true;
      else
        {
          xdr_setpos(buffer.Xdr,BufferUsed);
          if(buffer.IncreaseBufferMode)
            {
              buffer.IncreaseBuffer();
              return xdr_double(buffer.Xdr,&i);
            }
          else
            return false;
        }
    }
  else
    return false;
#else
  //wh change
      unsigned int s = sizeof(double);
  while(buffer.Xdr->BufferLeft < s)

    //  if(buffer.Xdr->BufferLeft < s)

      buffer.IncreaseBuffer();
  memcpy(buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, &i,s);
                
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
 
/*F ans = Unpack(buffer,i)  . . . . . . . . . . . . . . . . . . . . .  double
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    i: To be unpacked from buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Unpack(CommBuffer& buffer, double& i)
{
#ifndef _noxdr
  if(buffer.IsReading())
    return xdr_double(buffer.Xdr,&i);
  else 
    return false;
#else
  //wh change   
      unsigned int s = sizeof(double);
  memcpy(&i,buffer.Xdr->Buffer + buffer.Xdr->BufferUsed,s);
        
  buffer.Xdr->BufferUsed += s;
  buffer.Xdr->BufferLeft -= s;
  return true;
#endif
}
/*F ans = Pack(buffer,string,length)  . . . . . . . . . .  char** with length
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    string: bytes to be packed
**    length: The length of bytes to be packed
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, char** string, unsigned int length)
{
#ifndef _noxdr
  if(buffer.IsStoring())
    {
      Pack(buffer,length);
      unsigned int BufferUsed = (unsigned int) xdr_getpos(buffer.Xdr);
      if(xdr_opaque(buffer.Xdr,*string,length))
        return true;
      else
        {
          xdr_setpos(buffer.Xdr,BufferUsed);
          if(buffer.IncreaseBufferMode)
            {
              buffer.IncreaseBuffer();
              return xdr_opaque(buffer.Xdr,*string,length);
            }
          else
            return false;
        }
    }
  else
    return false;
#else
  //wh change

      //        if(buffer.Xdr->BufferLeft < length)

        //              buffer.IncreaseBuffer();

  int count = 0;

  while (buffer.Xdr->BufferLeft < length + sizeof(int))

    buffer.IncreaseBuffer();



  // whchange 2.7.97

       Pack(buffer,length);


  memcpy(buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, *string, length);
  buffer.Xdr->BufferUsed += length;
  buffer.Xdr->BufferLeft -= length;
        
  return true;
#endif
}
 
/*F ans = Pack(buffer,string) . . . . . . . . . . . . string ending with null
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    string: The string which ends with a null character
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Pack(CommBuffer& buffer, char** string)
{
  unsigned int length = strlen(*string)+1;
  bool ans = Pack(buffer,string,length);
  return ans;
}
 
/*F ans = Unpack(buffer,string) . . . . . . . . . . . . . . . . . . .  char**
**
**  DESCRIPTION
**    buffer: The buffer class (as input)
**    string: To be unpacked from buffer
**    ans: true if successful
**
**  REMARKS
**
*/
extern bool Unpack(CommBuffer& buffer, char** string)
{
#ifndef _noxdr
  if(buffer.IsReading())
    {
      unsigned int size;
      bool ans = Unpack(buffer,size);
      if(ans)
        {
          *string = (char *) malloc(size);
          return xdr_opaque(buffer.Xdr,*string,size);
        }
    }
  else 
    return false;
#else
  //wh change
      int length;
  bool ans = Unpack(buffer, length);
  *string = (char *) malloc(length);
  memcpy(*string, buffer.Xdr->Buffer + buffer.Xdr->BufferUsed, length);
     
  buffer.Xdr->BufferUsed += length;
  buffer.Xdr->BufferLeft -= length;
#endif
  return true;
} 
/*S XML
 */
/*F ans = XMLWriteBegin(out,key)  . . . . .. . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
      out: The output stream
      key: The key of the XML
**    ans: True if the string is empty
**
**  REMARKS
**
*/
bool XMLWriteBegin(std::ostream& out,const char *key)
{
  out << "<";
  while(*key != '\0')
      out.put(*key++);
  out << "> ";
  return true;      
}
/*F ans = XMLWriteEnd(out,key)  . . . . .. . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
      out: The output stream
      key: The key of the XML
**    ans: True if the string is empty
**
**  REMARKS
**
*/
bool XMLWriteEnd(std::ostream& out,const char *key)
{
  out.flush();
  out << "<\\";
  while(*key != '\0')
      out.put(*key++);
  out << "> ";
  return true;
}
/*F ans = XMLReadBegin(in,key)  . . . . .. . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
      in: The input stream
      key: The key of the XML
**    ans: True if the string is empty
**
**  REMARKS
**
*/
bool XMLReadBegin(std::istream& in,char *key)
{
  bool ans = true;
  char c = in.get();
  if(c == '<')
    {
      c = in.get();
      while(*key == c && *key != '\0')
	{
	  c = in.get();
	}
      if(c != '>')
	ans = false;
    }
  else
    ans = false;
  return ans;
}
/*F ans = XMLReadEnd(in,key)  . . . . .. . . . . . . . . . . . . . . . . . . .  String
**
**  DESCRIPTION
      in: The input stream
      key: The key of the XML
**    ans: True if the string is empty
**
**  REMARKS
**
*/
bool XMLReadEnd(std::istream& in,char *key)
{
  bool ans = true;
  char c = in.get();
  if(c == '<')
    {
      if(c == '\\')
	{
	  c = in.get();
	  while(*key == c && *key != '\0')
	    {
	      c = in.get();
	    }
	  if(c != '>')
	    ans = false;
	}
      else
	ans = false;
    }
  else
    ans = false;
  return ans;
}

