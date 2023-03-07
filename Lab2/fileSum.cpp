#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


int main(int argc, char* argv[]) 
{
  int sumVar , pos;
  string fileName;
  
  fileName = argv[1];
  ifstream infile(fileName.c_str());
  
  while( !(infile.eof() ) ) // while in the file
  {
    while(infile >> pos) // while numbers are in the file
    {
      sumVar= sumVar + pos;
    }
    infile.clear(); // revives dead file
    
    if(infile.peek() == ',' || infile.peek() == -1) // checks for commas or end of file marker
    {
      infile.ignore(1);
    }
    else
    {
      sumVar = -1;
    }
  
  }
  cout << sumVar << endl;


  return 0;
}
