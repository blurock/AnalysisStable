/*  FILE     CommBufferType.hh
**  PACKAGE  CommBuffer
**  AUTHOR   Edward S. Blurock
**
**  CONTENT
**    Class definitions for the "CommBuffer" package.
**
**  OVERVIEW
**
**  IMPLEMENTATION
**
**  REFERENCES
**
**  COPYRIGHT (C) 1996 STURM Project, RISC Linz
*/
 
#ifndef STURM_COMMBUFFERTYPE_HH
#define STURM_COMMBUFFERTYPE_HH

/*C CommBuffer
**
**  DESCRIPTION
**     This is the XDR interface for a buffer.
**
**     Through the Pack and Unpack functions the buffer is 
**     sequentially filled or decoded. In the encoding mode,
**     if the original buffer size is not enough, it is 
**     expanded.
**
**     The XDR functions are used to standardize the byte representation.
**
**  REMARKS
**
*/
class CommBuffer
{
private:
  COMM_DIRECTION_TYPE Direction;
#ifndef _noxdr
  enum xdr_op XDR_Direction;
#else
  int XDR_Direction;
#endif
  XDR *Xdr;
  unsigned int BufferSize;
  unsigned int BufferIncrement;
  char *Buffer;
  int IncreaseBufferMode;
     
  void IncreaseBuffer();
     
public:
  inline CommBuffer(const COMM_DIRECTION_TYPE direction, 
                    int buffersize,
                    int bufferinc);

  inline CommBuffer(const COMM_DIRECTION_TYPE direction);
  inline CommBuffer(char *buffer,
                    const int buffersize);
  inline char* GetBuffer();
  inline unsigned int GetBufferSize();
  inline ~CommBuffer(void);
  inline bool IsStoring();
  inline bool IsReading();


  friend bool Pack(CommBuffer& buffer, int i);
  friend bool Unpack(CommBuffer& buffer, int& i);
  friend bool Pack(CommBuffer& buffer, unsigned int i);
  friend bool Unpack(CommBuffer& buffer, unsigned int& i);
  friend bool Pack(CommBuffer& buffer, short i);
  friend bool Unpack(CommBuffer& buffer, short& i);
  friend bool Pack(CommBuffer& buffer, float i);
  friend bool Unpack(CommBuffer& buffer, float& i);
  friend bool Pack(CommBuffer& buffer, double i);
  friend bool Unpack(CommBuffer& buffer, double& i);
  friend bool Pack(CommBuffer& buffer, char** string);
  friend bool Pack(CommBuffer& buffer, char** string, unsigned int length);
  friend bool Unpack(CommBuffer& buffer, char** string);
};

#endif
