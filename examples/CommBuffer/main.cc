/*  FILE     
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


#define TEMPLATE_INSTANTIATION
#include "Basis/CommBuffer.hh"

static void Test1();

int main( void )
{

  int i;
  Test1();
     
  CommBuffer outbuffer(COMM_BUFF_ENCODE,200,200);
  char test1[] = "abcdefghijklmnop";
  char test2[] = "won't come back";
  char *test11,*test21;
  test11 = (char *) malloc(19);
  for(i=0;i<19;i++)
    *(test11 + i) = test1[i];
  test21 = (char *) malloc(16);
  for(i=0;i<16;i++)
    *(test21+i) = test2[i];
     
  cout << "The two strings written out are:\n";
  cout << test11;
  cout << "\n";
  cout << test21;
  cout << "\n";
  cout << "and now encoding\n";
     
  Encode(outbuffer,&test11);
  Encode(outbuffer,&test21);

  cout << " and decoding\n";
  cout << "The size of the buffer is:  ";
  cout << outbuffer.GetBufferSize();
  cout << "\n";
     
  cout << "The first ten objects in the buffer are:\n";
  char *c = outbuffer.GetBuffer();
     
  for(unsigned int cnt = 0; cnt < 30; cnt++)
    {
      if(!(cnt % 10))
        cout << "\n";
      int num = (int) *c;
      cout << cnt << "  " << num << "  ";
         
      c++;
    }
     
       
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());
  char *intest1,*intest2;
  Decode(inbuffer,&intest1);
  cout << "The first string is\n";
  cout << intest1;
  cout << "\n";
  Decode(inbuffer,&intest2);
  cout << "The second string is\n";
  cout << intest2;
  cout << "\n";

  return(0);
}

static void Test1()
{
  CommBuffer outbuffer(COMM_BUFF_ENCODE,
                       1000,1000);

  int a = 1232456;
  int aorig = a;
     
  for(int i=0;i<10;i++)
    {
      Encode(outbuffer,a);
      a++;
    }
  unsigned int cnt = outbuffer.GetBufferSize();
  cout << cnt << "\n";
     
  CommBuffer inbuffer(outbuffer.GetBuffer(),
                      outbuffer.GetBufferSize());

  int aread;
  Unpack(inbuffer,aread);     
  cout << "Wrote: " << aorig << " -- ";
  cout << "Read: " << aread << "\n";

  for(unsigned int i=0;i<9;i++)
    {
      Decode(inbuffer,aread);
      cout << aread << "\n";
    }
}     

