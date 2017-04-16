//Shiv Lakhanpal
//Data Structures Fall 2016
//Net ID: svl238
//Homework 8 - Programming Part 1


#define CATCH_CONFIG_MAIN
#include<istream>
#include "Tokenizer.cpp"
#include "catch.hpp"

using namespace std;

// Code from Weiss
// Symbol is the class that will be placed on the Stack.
struct Symbol
{
    char token;
    int  theLine;

};


// NOTE. THE HW ONLY REQUIRED YOU TO CHECK FOR PARENTHESIS ONLY. I WROTE THE CODE THAT CHECKS FOR EVERY BRACKET
//
class Balance
{
public:
    Balance( istream & is ):tok( is ),errors( 0 ){}
    int checkBalance(); // returns the number of mismatched parenthesis
private:
    Tokenizer tok;
    int errors;
    void checkMatch( const Symbol & oParen, const Symbol & cParen );
};

int Balance::checkBalance(){
  stack<Symbol> s;
  char sym = tok.getNextOpenClose();
  while(sym != '\0'){
    if (sym == '('){
      Symbol nSym;
      nSym.token = sym;
      nSym.theLine = tok.getLineNumber();
      s.push(nSym);
    }
  else if (sym == ')'){
    if (s.empty()){
        errors++;
        cout << "The Stack was empty and mismatched parentheses on line: " << tok.getLineNumber();
      }
    else{
      Symbol stackTop = s.top();
      Symbol clParen;
      clParen.theLine = tok.getLineNumber();
      clParen.token = sym;
      checkMatch(stackTop, clParen);
      s.pop();
      }
    }
    sym = tok.getNextOpenClose();
  }
  while(!s.empty()){
    errors++;
    s.pop();
  }
  return errors;
}

void Balance::checkMatch(const Symbol & oParen, const Symbol & cParen ){
if(oParen.token == '('&& cParen.token == ')')
  return;
else{
  errors++;
  cout << "Mismatched parentheses" << endl;
  }
}

SCENARIO("Checking your Balancer"){
    GIVEN("a test file test.cc with 2 known issues taken in as a ifstream"){
        ifstream ifs("test_cases/test.cc");
        if (!ifs) cerr << "Failure to open file" << endl;
        cerr << "test.cc" << endl;
        WHEN("Given a balancer"){
            Balance b(ifs);
            THEN("CheckBalance should return 2"){
                REQUIRE(b.checkBalance() == 2);
            }
        }
        ifs.close();
    }
    GIVEN("a test file test2.cc with 3 known issues taken in as a ifstream"){
        ifstream ifs("test_cases/test2.cc");
        if(!ifs) cerr << "Failure to open file" << endl;
        cerr << "test2.cc" << endl;
        WHEN("Given a balancer"){
            Balance b(ifs);
            THEN("Check balance should return 3"){
                REQUIRE(b.checkBalance() == 3);
            }
        }
    }
    GIVEN("a test file test3.cc with 0 known issues taken in as a ifstream"){
        ifstream ifs("test_cases/test3.cc");
        if(!ifs) cerr << "Failure to open file" << endl;
        cerr << "test3.cc" << endl;
        WHEN("Given a balancer"){
            Balance b(ifs);
            THEN("Check balance should return 0"){
                REQUIRE(b.checkBalance() == 0);
            }
        }
    }
}
