#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <map>
#include <cstring>

using namespace std;


typedef char String[25];

enum TransactionType {Add, Delete, ChangeOnhand, ChangePrice};

struct BookRec
{
  unsigned int isbn;
  String name;
  String author;
  int onhand;
  float price;
  String type;
};

struct TransactionRec
{
  TransactionType ToDo;
  BookRec B;
};

void errorCheck(int argc, char* argv[]);
long mapOffsets(char* masterCopy, map<unsigned int, long> &map);
void databaseOps(map<unsigned int, long> &map, long &offsetVal, char* argv[]);
void printValidRecords(char* file);
void printOutput(BookRec* rec);
string keyFormatting(unsigned int& key);


int main(int argc, char* argv[])
{
  char* masterCopy;
  map<unsigned int, long> map;
  long offsetVal;
  
  errorCheck(argc,argv);
  masterCopy = argv[1];
  offsetVal = mapOffsets(masterCopy, map);
  
  databaseOps(map,offsetVal,argv);
  
  
  return 0;
  
}

void errorCheck(int argc, char* argv[])
{
  string master, transaction, newFile;
  
  if (argc != 4)
  {
    cerr << " Input Formatting Error. " << endl;
    cout << " Correct Format is ' ./'database name' masterFile transactionFile newFile" << endl;
    throw exception();
  }
  
  master = argv[1];
  transaction = argv[2];
  newFile = argv[3];
  
  
  fstream testM(master.c_str());
  fstream testT(transaction.c_str());
  fstream testN(newFile.c_str());
  
  if( !testM  )
  {
    cerr << " Master file is invalid. Master File " << argv[1] << "cannot be found. ";
    throw exception();
  }
  if( !testT  )
  {
    cerr << " Transaction file is invalid. Transaction File " << argv[2] << "cannot be found. ";
    throw exception();
  }
  if( newFile == master )
  {
    cerr << " The new file cannot have the same name as the transaction file. Reinput file names.";
    throw exception();
  }
  if( newFile == transaction )
  {
    cerr << " The new file cannot have the same name as the transaction file. Reinput file names.";
    throw exception();
  }
  
  testM.close();
  testT.close();
  testN.close();
  
  
  
   
}

long mapOffsets(char* masterCopy, map<unsigned int, long> &map)
{
  long curr;
  BookRec* book = new BookRec;
  
  fstream infile(masterCopy, ios::in | ios::binary);
  while(infile.read( (char*) book, sizeof(BookRec) ) )
  {
    map[book -> isbn] = sizeof(BookRec) * curr++;
  }
  
  infile.close();
  return curr;
}

void databaseOps(map<unsigned int, long> &map, long &offsetVal, char* argv[]) 
// carries out database operations of add, delete, changeonhand, and price
{
  string copyMaster; // gen vars
  int transNum = 1;
  TransactionRec* transRec = new TransactionRec;
  
  long bytePosition; //onhand operation vars
  BookRec record;
  
  copyMaster = argv[1];
  system( ("cp "+ copyMaster + " copy.out").c_str()); 
  
  fstream inFile(argv[2], ios::in|ios::binary); // our transaction file
  fstream outFile("copy.out", ios::in|ios::out|ios::binary|ios::app); // Strange but copies the binary file
  fstream ERRORS("ERRORS", ios::out); // required errors file
  
  while( inFile.read( (char*) transRec, sizeof(TransactionRec) ) ) 
  // logic in while based around enum - lets hope it goes well
  {
    if(transRec -> ToDo == 0)
    {
      if( map.find(transRec -> B.isbn) != map.end() )
      {
        ERRORS<< "Invalid Transaction Number. " << transNum << " cannot be added - duped key. " << keyFormatting(transRec -> B.isbn) << endl;
      }
      else
      {
        map[transRec -> B.isbn] = sizeof(BookRec) * offsetVal;
        outFile.write( (char*) &(transRec -> B), sizeof(BookRec) );
      }
    }
    
    if(transRec -> ToDo == 1)
    {
      if( map.find(transRec -> B.isbn) == map.end() )
      {
      ERRORS<< "Invalid Transaction Number. " << transNum << " cannot be deleted - record isbn not found. " << keyFormatting(transRec -> B.isbn) << endl;
      }
      else
      {
        map.erase( map.find(transRec -> B.isbn) );
      }
    }
    
    if(transRec -> ToDo == 2)
    {
      if( map.find(transRec -> B.isbn) == map.end() )
      {
        ERRORS<< "Invalid Transaction Number. " << transNum << " cannot change onhand count - key not found. " << keyFormatting(transRec -> B.isbn) << endl;
      }
      else
      {
        bytePosition = map[transRec -> B.isbn]; //requested record byte position
        outFile.seekg(bytePosition, ios::beg);// find requested record on harddrive
        outFile.read( (char*) &record, sizeof(BookRec) ); // read new record found from outfile
        transRec -> B.onhand = transRec -> B.onhand + record.onhand;
        
        if( transRec -> B.onhand < 0)
        {
          ERRORS << "Invalid Transaction Number. " << transNum << " 's count = "<< transRec -> B.onhand << " for key number " << keyFormatting(transRec->B.isbn) << endl;
          transRec -> B.onhand = 0;
        }
        map[transRec -> B.isbn] = sizeof(BookRec) * offsetVal++; // save new offset and add to our outfile
        outFile.write( (char*) &(transRec -> B), sizeof(BookRec) );
      }
    }
    
    if(transRec -> ToDo == 3)
    {
      if( map.find(transRec -> B.isbn) == map.end() )
      {
        ERRORS<< "Invalid Transaction Number. " << transNum << " cannot change price - key not found. " << keyFormatting(transRec -> B.isbn) << endl;
      }
      else
      {
        map[transRec -> B.isbn] = sizeof(BookRec) * offsetVal++;
        outFile.write( (char*) &(transRec -> B), sizeof(BookRec) );
        
      }
    }
    transNum++;
  }
  
  fstream newFile(argv[3], ios::out|ios::binary);
  
  
  printValidRecords(argv[3]);
  system( ("rm copy.out") );
  inFile.close();
  outFile.close();
  ERRORS.close();
}

void printValidRecords(char* file) 
// prints out all records read in from our binary file
{
    fstream binFile(file, ios::in|ios::binary); 
  
    
    BookRec* rec = new BookRec;
    
    
    while( binFile.read( (char*) rec, sizeof(BookRec) ) ) 
    {
        printOutput(rec);
    }
    binFile.close(); 
}

void printOutput(BookRec* rec) 
// prints records in a specific format
{
  cout<<setw(10)<<setfill('0')<<rec->isbn
  <<setw(25)<<setfill(' ')<<rec->name
  <<setw(25)<<rec->author
  <<setw(3)<<rec->onhand
  <<setw(6)<<rec->price
  <<setw(10)<<rec->type<<endl; 
}

string keyFormatting(unsigned int& key)
{
  string keyWord;
  stringstream ss;
  ss << key;
  keyWord = ss.str();
  
  while(keyWord.length() < 10 )
  {
    keyWord = "0" + keyWord;
  }
  return keyWord;
  
  
  
}
