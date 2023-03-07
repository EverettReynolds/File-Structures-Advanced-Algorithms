#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <ostream>
#include <ios>
#include <vector>
#include <bits/stdc++.h>


using namespace std;


void compress(string myInput);
void uncompress(string myInput);

int main()
{

  string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73"; // These four lines give me long lists of errors and I spent way too long trying to figure out why\
  string comp = compress(myInput); // I came to the conclusion my error was because of my version of c++ but I did not give myself enough time to solve that error
  cout << comp << endl;
  cout << uncompress(comp) << endl;
  return 0;

}

void compress(string myInput)
{

}


void uncompress(string myInput)
{

}