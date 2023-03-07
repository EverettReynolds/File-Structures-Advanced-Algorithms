#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>

using namespace std; // Have had immense trouble with toString

int canonDate(string date);
string to_string(int i);

int main() 
{
  string date;
  int canon;
  date = "February 14, 2021";
  canon = canonDate(date);
  cout << canon << endl;
   
  
  
  return 0;
}


int canonDate(string date)
{
  string months[12] = {"January" , "February" , "March" , "April" , "May" , "June" , "July" , "August" , "September" , "October" , "November" , "December" };
  map<string, int> map;
  string month, actualDate;
  char var;
  int day, year;
  stringstream ss;
  
  int x = 1;
  
  for(int i = 0; i < 12; i++) // populate map with numbers associated with dates on our calendar
  {
    map[ months[i] ] = x;
    x++;
  }
  
  ss.str(date);
  ss >> month;
  ss >> day;
  ss >> var;
  ss >> year;
  
  actualDate = to_string(map[month]) + to_string(day) + to_string(year);
}

string to_string(int i) // had to declare my own tostring even though I know it later versions this exists in an imported library
{
  stringstream tt;
  tt << i;
  return tt.str();
} 