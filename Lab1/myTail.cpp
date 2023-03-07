#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std; // I probably should have gotten help sooner :/

int main(int argc, char *argv[])
{

  string numLine;
  string file;
  string updateLine;
  string output;
  int lineCount;
  int itCount;
  char ch;
  double overSize;
  double currSize;
  
  numLine = argv[1]; // taking in the command line arguments here
  file = argv[2];
  
  lineCount = -(atoi(updateLine.c_str()));
  
  fstream in(file.c_str(),ios::in);
  in.seekg(0,ios::end);
  while(lineCount > itCount)
  {
    currSize++;
    in.seekg(-1,ios::cur);
    ch = in.peek();
    if(ch == '\n') // if it is the end of the line, go to the next line
    {
      itCount++;
    } 
    if(currSize == overSize) // if the current size is equal to the overall size
    {
      in.seekg(0,ios::beg);
      break; 
    }
  }
  ch = in.peek();
  if(ch == '\n')
  {
    in.seekg(1,ios::cur);
    while(in.get(ch))
    {
      cout << ch;
     output = ch + output;
     in.seekg(-1,ios::cur); 
    }
    in.close();
    
  }
  cout << output << endl;
  return 0;
}