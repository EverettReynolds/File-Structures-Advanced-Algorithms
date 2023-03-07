#include <iostream>

using namespace std;

int H1(char*s);
int H2(char*s);

int main()
{
  char* word1 = "BEAR";
  char* word2 = "BARE";
  int one,two;
   one = H1(word);
   two = H2(word);
   cout << one << endl;
   cout << two << endl;
  return 0;
}

int H1(char*s)
{
  int r = 1;
  int i;
  for (i = 0; i < 4; ++i)
  {
    r = r * (int) s[i];
  }
  return r%2001;
}

int H2(char*s)
{
  int r = 0;
  int i;
  for (i = 0; i < 4; ++i)
  {
    r = 3*r + (int) s[i];
  }
  return r%2001;
}