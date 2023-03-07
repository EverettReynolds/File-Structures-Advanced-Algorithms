#include "btree.h"


#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  string str;
  string key;
  fstream stream(argv[2], ios::in);
  BTree tree;
  
  while( getline(stream,key) )
  {
    
  
  
  }
  
  cout << endl;
  tree.totalio();
  stream.close();
  return 0;
}