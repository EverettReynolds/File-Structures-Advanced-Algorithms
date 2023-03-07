using namespace std;
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>

class File
{
   public :
       File (const File& otherFile); // copy instructor (deep copy)
       File (const char name[], const char pmode[], // Constructor to define arguments (explicit constructor)
             const char size[], const char stamp[]); 
       File (); // Default Constructor
       File & operator = (const File& otherFile); // overloading with deep copy
       string getSize() const; // bunches of getters and setters
       string getName() const;
       string getPmode() const;
       string getStamp() const;
       int recordSize() const;
       void flagAsDir(); // marks it as directory not a file
       bool isADir() const; // getter

   private :
       char name[81], pmode[5], size[7], stamp[16];
       bool ADir;
};
