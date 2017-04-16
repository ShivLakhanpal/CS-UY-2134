//Shiv Lakhanpal
//Data Structures Fall 2016
//Net ID: svl238
//Homework 2 - Programming Part 2 and 3
#include<math.h>
#include <vector>
#include<iostream>
#include <string>

using namespace std;

//Programming Part Question 2
class OddorEven{
public:
  bool isEven(int x){
    if(x % 2 == 0)
      return true;
    else
      return false;
  }
};

bool EvenorOdd(int Integer, OddorEven intEvenorOdd){
  return intEvenorOdd.isEven(Integer);
}

//Programming Part Question 3
class stringCompare{
public:
  bool stringSize(const string& str1, const string& str2){
    if(str1.size() > str2.size())
      return true;
    else
      return false;
  }
};

bool stringTrueorFalse(const string& firstString, const string& secondString, stringCompare trueOrFalse){
  return trueOrFalse.stringSize(firstString, secondString);
}

int main(){
  cout << "----- Question 2 -----\n";
  int a;
  cout << "Please enter an integer: ";
  cin >> a;
  OddorEven EorO;
  cout << boolalpha << EvenorOdd(a,EorO) << endl;

  cout << "----- Question 3 -----" << endl;
  string stringnum1;
  string stringnum2;
  cout << "Please enter the first string: ";
  cin >> stringnum1;
  cout << "Please enter the second string: ";
  cin >> stringnum2;

  stringCompare strComp;
  cout << boolalpha << stringTrueorFalse(stringnum1, stringnum2, strComp) << endl;

}
