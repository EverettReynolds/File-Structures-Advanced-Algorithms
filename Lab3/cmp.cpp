#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;


void errorCheck(char* fname1, char* fname2, fstream &file1, fstream &file2);
bool flagCheck(int argc, char *argv[], bool &charCheck, bool &igCheck, int &pos);
bool directoryCheck(char* fname1, char* fname2, fstream &file1, fstream &file2, char &f1, char &f2);
void compareFiles(char* fname1, char* fname2,bool &charCheck, bool &igCheck, int &pos);

int main(int argc, char* argv[])
{
  int pos = 0;
  bool charCheck, igCheck;
  if( argc < 3 || argc > 6)
  {
    cerr << " You Have Entered an Invalid Number of Arguments." << endl;
    cout << " Please Try Again with This Format for Your Command. cmp [-c or -i] num filename1 filename2 " << endl;
    throw exception();
  
  }
  if( flagCheck(argc, argv, charCheck, igCheck, pos) )
  {
    compareFiles(argv[argc-2],argv[argc-1],charCheck,igCheck,pos);
  }
  return 0;

}

void errorCheck(char* fname1, char* fname2, fstream &file1, fstream &file2)
{
   if(!file1)
   {
     cerr << fname1 << " does not exist. Reenter the file names and make sure they exist. " << endl;
     throw exception();
   }
    if(!file2)
   {
     cerr << fname2 << " does not exist. Reenter the file names and make sure they exist. " << endl;
     throw exception();
   }
}

bool flagCheck(int argc, char *argv[], bool &charCheck, bool &igCheck, int &pos)
{
  string arg;
  for(int i = 0; i < argc; i++)
  {
    arg = argv[i];
    if(arg == "-c")
    {
      charCheck = true;
    }
    if(arg == "-i")
    {
      igCheck = true;
      pos = atoi( argv[i+1] );
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool directoryCheck(char* fname1, char* fname2, fstream &file1, fstream &file2, char &f1, char &f2)
{
  file1.get(f1);
  file2.get(f2);
  
  if(!file1)
  {
    return true; //directory
  }
  if(!file2)
  {
    return true; //directory
  }
  else
  {
    return false;
  }
}

void compareFiles(char* fname1, char* fname2,bool &charCheck, bool &igCheck, int &pos)
{
  char ch1,ch2;
  int lnCount, byteCount;
  lnCount = 1;
  byteCount = pos;
  fstream file1( fname1, ios::in);
  fstream file2( fname2, ios::in);
  errorCheck(fname1,fname2,file1,file2);
  if(igCheck)
  {
    file1.seekg(pos);
    file2.seekg(pos);
  }
  if(directoryCheck) // not EOF
  {
    while(file1 && file2) //valid files
    {
      file1.get(ch1);
      file2.get(ch2);
      byteCount++;
      if(ch1 != ch2)
      {
        cout << fname1 << " " << fname2 << " differ: byte " << byteCount << ", line " << lnCount;
        
        if(charCheck)
        {
          printf( " is %o %c %o %c" , ch1, ch1, ch2, ch2); // love this function, saved me from converting manually to octal
        }
      }
      if(ch1 == '\n' || ch2 == '\n')
      {
        lnCount++;
      }
  
   }
  }
   if(!file1 && file2)
   {
     cout << " cmp: EOF on " << fname1 << endl;
   }
   if(!file2 && file1)
   {
     cout << " cmp: EOF on " << fname2 << endl;
   }
  
}