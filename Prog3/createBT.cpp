#include "btree.h"
#include "album.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  Album album;
  BTree tree;
  fstream stream(argv[1],ios::in);
  tree.reset(argv[2]);
  while(stream >> album )
  {
  
    cout << " Now Inserting " << album << endl;
    tree.insert(album);
  
  }
  cout << endl;
  tree.printTree();
  stream.close();
  
  

}
