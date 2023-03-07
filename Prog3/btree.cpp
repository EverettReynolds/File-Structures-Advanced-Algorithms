#include "btree.h"

// I know this is unfinished but I hope you have mercy on me. This semester has put me in binds I cannot even fathom, but I have learned a lot from you. Thank you for putting all the effort you could into making our classes seem like it was just another year. ~ Everett


using namespace std;

BTree::BTree()
{

  rootAddr = 0;
  height = 0;
  read = 0;
  write = 0;
  

}

int BTree::countLeaves(int recAddr) //start of public funcs
{
  BTNode node = getNode(recAddr);
  bool isLeaf = true;
  int sum = 0;
  for(int i = 0; i <= node.currSize; i++)
  {
    if(node.child[i] != -1)
    {
    isLeaf = false;
    sum += countLeaves(node.child[i]);
    }
  }
  return isLeaf ? 1 : sum;
}

int BTree::getHeight()
{

  return height;

}

void BTree::printTree()
{

  cout << "-------- B-Tree of Height " << height << " -------- " << endl;
  printTree(rootAddr);

}

void BTree::insert(keyType key)
{

  insert(key,rootAddr);

}

BTNode BTree:: getNode(int recAddr) // start of private funcs
{
  BTNode bt;
  treeFile.seekg(recAddr, ios::beg);
  treeFile.read( (char*) &bt, sizeof(BTNode) );
  treeFile.clear();
  return bt;

}

void BTree::printNode(int recAddr)
{        
  treeFile.seekg(recAddr, ios::beg);        
  BTNode dummy;        
  treeFile.read((char *) &dummy, sizeof(BTNode));        
  read++;        
  cout << "    *** node of size " <<dummy.currSize<< " ***     "<<endl;        for (int i = 0;  i < dummy.currSize;  i++)
   {                
     cout << dummy.contents[i] << endl;
   }
}

void BTree::totalio() const
{
  cout << endl;
  cout << "Total Reads: " << fread << endl;
  cout << "Total Writes: " << fwrite << endl;

}

void BTree:: writeHeader (char* fileName)
{
  BTNode bt;
  treeFile.open(fileName, ios::in|ios::out|ios::binary);
  treeFile.seekg(0, ios::beg);
  treeFile.read( (char*) &bt, sizeof(BTNode) );
  cout << bt.child[0] << endl;
  rootAddr = bt.child[0];
  root = getNode(rootAddr);
  read++;
  

}

void BTree:: reset(char* filename)
{
  BTNode bt;
  treeFile.open(filename, ios::trunc | ios::in | ios::out | ios::binary); // ios::trunc = a file clear out when the file is opened
  treeFile.seekg(0, ios::beg);
  bt.child[0] = sizeof(BTNode);
  rootAddr = bt.child[0];
  root.currSize = 0;
  for(int i = 0; i < ORDER; i++)
  {
    root.child[i] = -1;
  }
  treeFile.write( (char*) &root, sizeof(BTNode) );
  write++;
  treeFile.write( (char*) &bt, sizeof(BTNode) );
  write++;

}
bool BTree:: isLeaf(int recAddr) //private 
{

  BTNode temp = getNode(recAddr);
  if(temp.child[0] == -1)
  {
  
    return true;
  
  }
  return false;

}

bool BTree:: isLeaf(BTNode t)
{

  if(t.child[0] == -1 )
  {
  
    return true;
  
  }
  return false;

}


void BTree::printTree(int rootAddr)
{

  if(rootAddr != -1 )
  {
    BTNode temp = getNode(rootAddr);
    printNode(rootAddr);
    for(int i = 0; i <= temp.currSize; i++)
    {
    
      printTree( temp.child[i] );
    
    }
  
  }

}

void BTree:: insert(keyType key, int recAddr)
{

  BTNode temp = getNode(recAddr);
  
  if( !isLeaf(recAddr) )
  {
  
    for( int i = 0; i < temp.currSize; i++ )
    {
    
      if( key < temp.contents[i] )
      {
        insert( key,temp.child[i] );
        return;
      }
    
    }
    insert( key,temp.child[temp.currSize] );
    return;
  
  }
  if( isLeaf(recAddr) && temp.currSize < 4 ) // a not full node
  {
    int x;
    for( x = temp.currSize-1; x>=0 && key < temp.contents[x]; x--) 
    // finding the correct location to match key to node
    {
      temp.contents[x+1] = temp.contents[x];
    }
    temp.contents[x+1] = key;
    temp.currSize++;
    
    treeFile.seekg(recAddr,ios::beg); //updates to the index file for leaf
    treeFile.write( (char*) &temp, sizeof(BTNode) );
    write++;
    if(recAddr = rootAddr)
    {
      root = temp;
    }
    
    
  
  }
  
  else //indicates there is a split
  {
  
    cout << "Split Here" << endl;
    splitNode(key,recAddr,-1,1);
  
  }
  

}

int BTree:: findpAddr(keyType key, BTNode t, int tAddr, int pAddr) // we are looking for the parent address, I added an extra pAddr variable to indicate the parent variable so we can use this function recursively
{

  if(tAddr != -1)
  {
  
    if( tAddr == pAddr ) // this means there is no parent
    {
      
      return -1;
    
    }
    for(int i = 0; i < t.currSize; i++)
    {
      if( pAddr == t.child[i])
      {
        return tAddr;
      }
      if( key < t.contents[i] )
      {
        if(t.child[i] != -1)
        {
          return findpAddr(key, getNode( t.child[i] ), t.child[i], pAddr);
        }
        else
        {
          return -1;
        }
      }
      
    
    }
  
  }
  if( isLeaf(t) ) // if current node is a leaf
  {
  
    return -1;
  
  }
  else
  {
  
    return findpAddr( key, getNode( t.child[t.currSize] ), t.child[t.currSize], pAddr );
  
  }
  return -1;
}

void BTree::splitNode(keyType& key,int recAddr,int oneAddr,int twoAddr)
{
  BTNode LChild = getNode(recAddr);
  BTNode pNode = getNode(findpAddr(key,root,rootAddr,recAddr) );
  if( key < LChild.contents[3] )
  {
    int x;
    keyType temp = LChild.contents[3];
    LChild.contents[3] = key;
    key = temp;
    int tempAdd = LChild.child[4];
    LChild.child[4] = twoAddr;
    twoAddr = tempAdd;
    
    /*for( x = LChild.currSize - 1; x > 0 && LChild.contents[x] < LChild.contents[x-1] ; x-- ) // looking for correct location for node's key // this is where my issue is, the = operator does not want to be nice and cooperate
    {
      temp = LChild.contents[x];
      LChild.contents[x] = LChild.contents[x-1]; // switching positions
      LChild.contents[x-1] = temp;
      tempAdd = LChild.contents[x+1];
      LChild.contents[x+1] = LChild.contents[x];
      LChild.contents[x] = tempAdd;
    
    }*/
    
    
  
  }
  
  
  

}



