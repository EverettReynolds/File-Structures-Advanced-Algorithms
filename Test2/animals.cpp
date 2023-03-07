#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

int main()
{
  fstream zipFile ("animal.zip", ios::out | ios::binary);
  enum Animals {RODENT, CAT, DOG, BIRD, REPTILE, HORSE, BOVINE, SHEEP};
  Animals myAnimal; 
  char zippedAnimal;
  
  Animals a = SHEEP;
  char compressedA = (char) a;
  //Animals aC = (Animals) compressedA;
  
  zipFile.write( (char*) &compressedA, sizeof(Animals) );
  
  return 0;
}