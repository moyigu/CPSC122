/*
Class: CPSC 122
GU Username: Danni Du
Date Submitted: October 9, 2022 
Assignment: Project5
*/

#include <iostream>
#include <cstdlib>
#include <string> 
#include <fstream>
using namespace std;

void bubbleSort(string array[], int);
void sink(string array[], int);
void shift(string array[], int);
string amend(string);

int main(int argc, char* argv[])
{
 string array[100];
 string line;

 ifstream fin;
 ofstream fout;

 fin.open(argv[1]);
 fout.open(argv[2]);
 int i = 0;  
 int j = 0;       
 while (!fin.eof())
 {
  getline(fin,line);
  array[j] = amend(line);
  j++;
 }
 bubbleSort(array,j);
 int index = 0;
 while(index < j)
 {
   fout << array[index] << endl;
   index++;
 }
 fin.close();
 fout.close(); 

 return 0;


}

void bubbleSort(string array[],int numLines)
{
 int pass = 0;
 int bottom = numLines - 1;
 while(pass < numLines - 1)
 { 
  sink(array, bottom);
  bottom--;
  pass++;
 }
}

void sink(string array[], int bottom)
{
 int cur = 0;
 while(cur < bottom - 1)
 {
  if (array[cur] > array[cur+1])
  {
    shift(array,cur);
  }
  cur++;
 }
}

void shift(string array[],int cur)
{
 string tmp = array[cur];
 array[cur] = array[cur+1];
 array[cur+1] = tmp;
}

string amend(string line)
{
for (int i = 0; i < line.length(); i++)
  if (isalpha(line[i]))
   line[i] = toupper(line[i]);
  return line;
}


