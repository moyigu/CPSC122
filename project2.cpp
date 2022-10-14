/*
Name: Danni Du
Class: CPSC 122 01
Date Submitted: September 15, 2022
Assignment: project 3 
Description: Create functions achieving changing char to int, and use fstream put the value in the .txt file
Usage: .\a.out inFile outFile
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int myAtoi(char str[]);
int myStrnlen(char str[]);

int main(int argc, char* argv[])
{
    int product;
    int a = myAtoi(argv[1]);
    int b = myAtoi(argv[2]);
    product = a * b; // find two input values' product
    cout << product << endl;
    
    ofstream fout;
    fout.open(argv[3]); // create .txt file and this file's name need user input
    fout << product; // put the product value into this .txt file
    fout.close();

 
}

//let char input value becoming int
int myAtoi(char str[])
{
    int i = 0;
    int totalnum = 0;
    int len = myStrnlen(str);
    for(int j = len; j > 0; j--){
        int num1 = str[j - 1] - '0';
        totalnum = totalnum + num1 * pow(10,i);
        i++;
    }
        //cout << totalnum << endl;
    return totalnum;
}

//find the lenth of argv[]'s char value
int myStrnlen(char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        i++;
        cout << str[i] << endl;
    }
    return i;
}
