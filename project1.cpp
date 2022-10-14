/*
Name: Danni Du
Class: CPSC 122
Date Submitted: Sepetember 08, 2021
Assignment: Project 1
Description: Input number in command line, and find this numbers of prime number
*/


#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int);//prototype of isPrime function
void display(int, int);//prototype of display function

int main(int argc, char* argv[])
{
    int num1 = atoi(argv[1]);  //change a c-string to an integer
    int num2 = atoi(argv[2]);  //change a c-string to an integer
    display(num1,num2);//use display function
    cout << endl;
    return 0;
 }
 



bool isPrime(int num)
{
    for(int i = 2; i < num; i++){
        if((num % i) == 0){
            return false;
        }
    }
    return true;
}


void display(int totalPrimes, int cols)
{
 int candPrime = 2;//the first candidate prime number is 2
 int ct = 1;//if begin with 0, the first line will just have one number

 while (ct < totalPrimes)
  {
    if (isPrime(candPrime))
    {
     cout << candPrime << '\t';  //tab to next col 
     if (ct % cols == 0)
      cout << endl;
      ct++;
    }
    candPrime++;
  }
}
