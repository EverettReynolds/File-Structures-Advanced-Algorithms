#include <iostream>
using namespace std;


class Base
{
    public :
        virtual void iam();
};
void Base::iam()
{
    cout << "base" << endl;
}

class DerivedOne : public Base
{

  public :
            void iam()
            {
              cout << "iam one" << endl;
            }
            
            void iam2()
            {
              Base::iam();
            }
            
};

class DerivedTwo : public Base
{
  public :
            void iam()
            {
              cout << "iam two" << endl;
            }
            
            void iam2()
            {
              Base::iam();
            }
};

int main()
{
  Base baseClass;
  baseClass.iam();
  
  DerivedOne childOne;
  childOne.iam();
  childOne.iam2();
  
  DerivedTwo childTwo;
  childTwo.iam();
  childTwo.iam2();
  
  Base *childOnePoint = &childOne;
  Base *childTwoPoint = &childTwo;
  
  childOnePoint -> iam();
  childTwoPoint -> iam();
  
  return 0;
  
}