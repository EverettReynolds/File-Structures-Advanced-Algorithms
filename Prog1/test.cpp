#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <sstream>
#include <map>

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

struct BookRec;
struct TransactionRec;


int main()
{


  return 0;
}