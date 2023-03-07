#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <memory>

using namespace std;

void mystery(shared_ptr<int> ptr);
void mystery2(unique_ptr<int> ptr);

int main()
{
  shared_ptr<int> ptr(new int(15));
  shared_ptr<int> ptrNow(move(ptr));
  unique_ptr<int> ptrUnique = make_unique<int>(25);
  mystery(ptrNow);
  //mystery2(ptrUnique);
  return 0;
}
void mystery(shared_ptr<int> ptr) {
  cout << *ptr << endl;
  }
void mystery2(unique_ptr<int> ptr) {
  cout << *ptr << endl;
  }

 