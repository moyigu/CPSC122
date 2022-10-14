/*
Name: Danni Du
Class: CPSC 122 01
Date Submitted: September 25, 2022
Assignment: project 3 
*/



#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;


const string BKFile = "BKFile";

void encryptctl(string, string, string);
void decryptctl(string, string, string);
bool toDiscard(char);

/*
Description: Randomly generates an integer in the range: [1..25]
Input: name of keyFile
Output: Stores randomly generated integer in keyFile
*/
void keyGen(string);
/*
Description: Transforms ptFile into block text
Input: name of PTfile, BKfile
Output: BKfiile contains block text version of  PTFile
BKfiile is a hard-coded constant file name 
Block text has::
1. periods, commas, spaces removed
2. all alphabetic characters are upper case
3. no more than 50 characters per line
*/
void toBlock(string);
/*
Description: Encrypts an upper case alphabetic character using the Caesar cipher
Input: upper case alphabetic character, valid key
Returns: encrypted version of ch
    */
char encrypt(char, int);
/*
Description: Decrypts an upper case alphabetic character using the Caesar cipher
Input: upper case alphabetic character, valid key
Returns: decrypted version of input
    */
char decrypt (char, int);
/*
    Description: function opens a file
         Input: file stream object reference, name of the file, mode of open
Output: input file name is opened. 
*/
void fileOpen(fstream&, string, char);

int main(int argc, char* argv[])
{
    int mode = atoi(argv[1]);
    string keyfile = argv[2];
    if(mode == 0)
    {
        keyGen(keyfile);
    }
    else if(mode == 1)
    {
        string PTfile = argv[3];
        string CTfile = argv[4];
        toBlock(PTfile);
        encryptctl(keyfile, BKFile, CTfile);
    }
    else if(mode == 2)
    {
        string CTfile = argv[3];
        string DCfile = argv[4];
        decryptctl(keyfile, CTfile, DCfile);
    }
return 0;

}



void keyGen(string keyFile)
{
    fstream fin;
    fileOpen(fin, keyFile, 'w');
    unsigned seed = time(0);
    srand(seed);
    int x = 1 + rand() % 25;
    fin << x;
    fin.close();
}



void toBlock(string PTFile)
{
    fstream inFile, outFile;
    fileOpen(inFile, PTFile, 'r');
    fileOpen(outFile, BKFile, 'w');

    int ct = 0;
    char ch;
    while(inFile.peek() != EOF)
    {
     ch = inFile.get();
     if (!toDiscard(ch))
      {
       if (isalpha(ch))
       {
         ch = toupper(ch);
       }
       outFile.put(ch);
       ct++;
       if(ct % 50 == 0)
       {
         outFile << endl; 
       }
      }
    }
    inFile.close();
    outFile.close();
}

char encrypt(char ch, int key)
{
    if(ch == '\n')
    {
        ch = '\n';
    }
    else if(ch != '\n')
    {
        int pos = ch - 'A';
        pos = (pos + key) % 26;
        ch = pos + 'A';
    }
    return ch;
}

char decrypt(char ch, int key)
{
    if(ch == '\n')
    {
        ch = '\n';
    }
    else if(ch != '\n')
    {
    int pos = ch - 'A';
    pos = (pos - key + 26) % 26;
    ch = pos + 'A';
    }
    return ch;
}

void fileOpen(fstream& file, string name, char mode)
{
    string fileType;

    if (mode == 'r')
        fileType = "input";
    if (mode == 'w')
        fileType = "output";

    if (mode == 'r')
        file.open(name, ios::in);  //available thorugh fstream
    else
      if (mode == 'w')
         file.open(name, ios::out);  //available through fstream;

    if (file.fail()) //error condition 
        {
            cout << "Error opening " << fileType << " file" << endl;
            exit(EXIT_FAILURE);
}
}

void encryptctl(string keyfile, string BKFile, string CTfile)
{
    int key = 0;
    char ch;
    fstream Keyin;
    fileOpen(Keyin, keyfile, 'r');
    Keyin >> key;
    Keyin.close();
    fstream Block, CTin;
    fileOpen(Block, BKFile, 'r');
    fileOpen(CTin, CTfile, 'w');
    while(Block.peek() != EOF)
    {
        ch = Block.get();
        ch = encrypt(ch, key);
        CTin.put(ch);
    }
    Block.close();
    CTin.close();

}

void decryptctl(string keyfile, string CTfile, string DCfile)
{
    int key;
    char ch;
    fstream Keyin;
    fileOpen(Keyin, keyfile, 'r');
    Keyin >> key;
    Keyin.close();
    fstream CTin, DCin;
    fileOpen(CTin, CTfile, 'r');
    fileOpen(DCin, DCfile, 'w');
    while(CTin.peek() != EOF)
    {
        ch = CTin.get();
        ch = decrypt(ch, key);
        DCin.put(ch);
    }
    CTin.close();
    DCin.close();
}

bool toDiscard(char ch)
{
    if(ch == '.' || ch ==','|| ch == ' ' || ch == '\n'|| ch == '-')
        return true;
    return false;
}