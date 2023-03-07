#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <sstream>

using namespace std;

typedef char String[25];

struct BookRec
{
  unsigned int isbn;
  String name;
  String author;
  int onhand;
  float price;
  String type;
};

void readRecords(ifstream& inFile, fstream& binFile);
void printValidRecords(char* fileName);
void printOutput(BookRec* record);

int main(int argc, char* argv[])
{
  
  ifstream inFile("library.dat");
  fstream binFile("library.out", ios::out|ios::binary);
  readRecords(inFile,binFile);
  printValidRecords(argv[1]);
  
  return 0;

}

void readRecords(ifstream& inFile, fstream& binFile) 
// reads in records from the input text file and parses through file for bad records
{
  
  BookRec* rec = new BookRec;
  long isbn;
  long prevIsbn = INT_MIN;
  int lCount = 1;
  rec -> isbn = 0;
  while(inFile >> isbn ) // input reading with availiable isbns
  {
    bool output = true;
    rec -> isbn = isbn; // the current record's isbn is now the isbn
    inFile.ignore(1, '|'); // Making sure delimiters are not in the result
    inFile.getline(rec -> name, 25, '|'); // Getting Name
    inFile.getline(rec -> author, 25, '|'); // Getting Author
    inFile >> rec -> onhand; // Getting Onhand
    inFile.ignore(1, '|');
    inFile >> rec -> price; // Getting Price
    inFile.ignore(1, '|');
    inFile.getline(rec -> type, 25); // Getting Genre
  
  
    if(isbn < 1)
    {
      cerr << "Illegal ISBN number detected on line number " << lCount << " of the data file. the record was ignored" << endl;
      printOutput(rec);
      output = false;
    }
    if(isbn <= prevIsbn)
    {
      cerr << "ISBN is out of sequence on line " << lCount << " of the data file. " << endl;
      printOutput(rec);
    }
    if( rec -> onhand < 0 )
    {
      cerr << "Negative onhand amount found on line number " << lCount << " of the data file - the record was ignored." << endl;
      printOutput(rec);
      output = false;
    }
    if( rec -> price < 0 )
    {
      cerr << "Negative price amount found on line number " << lCount << " of the data file - the record was   ignored." << endl;
      printOutput(rec);
      output = false;
    }
    if(output = true)
    {
      prevIsbn = isbn;
      binFile.write( (char*) rec, sizeof(BookRec) );
    }
    lCount++;
  
  }  
  binFile.close();
}

void printValidRecords(char* file) 
// prints out all records read in from our binary file
{
    fstream binaryFile(file, ios::in|ios::binary); 
  
    
    BookRec* rec = new BookRec;
    
    while( binaryFile.read( (char*) rec, sizeof(BookRec) ) ) 
    {
        printOutput(rec);
    }
    
    binaryFile.close();
}

void printOutput(BookRec* rec) 
// prints error messages with records that have any of the three checked for errors 
{
  cout<<setw(10)<<setfill('0')<<rec->isbn
  <<setw(25)<<setfill(' ')<<rec->name
  <<setw(25)<<rec->author
  <<setw(3)<<rec->onhand
  <<setw(6)<<rec->price
  <<setw(10)<<rec->type<<endl;
}