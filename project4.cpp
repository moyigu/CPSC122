/*
Name: Danni Du
Class: CPSC 122 01
Date Submitted: October 01, 2022
Assignment: project 4 
*/
#include <iostream>
#include <fstream> 
#include <cstdlib>  //necessary for the constant EXIT_FAILURE
#include <string>
using namespace std;



/*
Description: Randomly generates and stores alpha and beta values.
The alpha value is randomly drawn from the the set: 
{1,3,5,7,9,11,15,17,19,21,23,25}
The beta value is randomly drawn from the range: [1..25]  
Input: name of file that stores the keys
Output: alpha and beta values on subsequent lines of keyFile
*/
void keyGen (string);

/*
Description: Encrypts an upper case alphabetic character using the affine cipher
Input: upper case alphabetic character, valid alpha and beta values
Returns: encrypted version of ch
*/
char encrypt (char, int, int);

/*
Description: Decrypts an upper case alphabetic character using the affine cipher. This requires a dictionary of multiplicative inverses mod 26.  See example program 4-dict.cpp (in my repository folder C-Sort-Search).
Input: upper case alphabetic character, valid alpha and beta values. 
Returns: decrypted version of input character
*/
char decrypt (char, int, int);

/*
Description: invokes fileOpen (../B-Files/7-openFileError.cpp in my GitHub repo) on all files.  Closes all files.  Reads key file. Reads the input file and either invokes encrypt or decrypt. If the action is encrypt, alphabetic characters are transformed to upper case.   Writes the result of encrypt or decrypt to the output file. 
Input: names of key file, input file and output file. mode value of 1 or 2
Output: writes to the output file
*/
void fileControl (string, string, string, int);

/*
Description: function opens a file
Input: file stream object reference, name of the file, mode of open
Output: input file name is opened. 
*/
void fileOpen(fstream&, string, char);

bool toDiscard(char);

const int MI[] = {0,1,0,9,0,21,0,15,0,0,0,19,0,0,0,0,0,23,0,11,0,0,0,0,0,25};

int main(int argc, char* argv[])
{
    int mode = atoi(argv[1]);
    string keyfile = argv[2];
    if(mode == 0)
    {
        keyGen(keyfile);
    }
    else
    {
        string fileIn = argv[3];
        string fileOut = argv[4];
        fileControl(keyfile, fileIn, fileOut, mode);
    }

}

void keyGen (string keyFile)
{
    int num[] = {1,3,5,7,9,11,15,17,19,21,23,25};
    fstream fin;
    fileOpen(fin, keyFile, 'w');
    unsigned seed = time(0);
    srand(seed);
    int x = 0 + rand() % 11;
    int a = num[x];
    fin << a;
    fin << endl;
    int b = 1 + rand() % 25;
    fin << b;
    fin.close();
}

char encrypt (char ch, int alpha, int beta)
{
    int pos = ch - 'A';
    pos = (alpha * pos + beta) % 26;
    ch = pos + 'A';
    return ch;
}

char decrypt (char ch, int alpha, int beta)
{
    int inverse_alpha = MI[alpha];
    int p = 0;
    int pos = ch - 'A';
    for(int i = 0; i <= 25; i++)
    {
        if((pos * inverse_alpha - inverse_alpha * beta + i * 26) > 0)
        {
            p = i;
            break;
        }
    }
    pos = (pos * inverse_alpha - inverse_alpha * beta + p * 26) % 26;
    ch = pos + 'A';
    return ch;
}

void fileControl (string keyFile, string fileIn, string fileOut, int mode)
{
    if(mode == 1)
    {
        int key = 0;
        char ch;
        fstream keyin;
        fileOpen(keyin, keyFile, 'r');
        int alpha = 0;
        keyin >> alpha;
        int beta = 0;
        keyin >> beta;
        keyin.close();
        fstream fin, fout;
        fileOpen(fin, fileIn, 'r');
        fileOpen(fout, fileOut, 'w');
        while(fin.peek() != EOF)
        {
            ch = fin.get();
            if(toDiscard(ch) == false)
            {
                ch = toupper(ch);
                ch = encrypt(ch, alpha, beta);
            }
            fout.put(ch);
        }
        fin.close();
        fout.close();
    }
    else if(mode == 2)
    {
        int key = 0;
        char ch;
        fstream keyin;
        fileOpen(keyin, keyFile, 'r');
        int alpha = 0;
        keyin >> alpha;
        int beta = 0;
        keyin >> beta;
        keyin.close();
        fstream fin, fout;
        fileOpen(fin, fileIn, 'w');
        fileOpen(fout, fileOut, 'r');
        while(fout.peek() != EOF)
        {
            ch = fout.get();
            if(toDiscard(ch) == false)
            {
                ch = decrypt(ch, alpha, beta);
            }
            fin.put(ch);
        }
        fin.close();
        fout.close();

    }
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


bool toDiscard(char ch)
{
    if(ch == '.' || ch ==','|| ch == ' ' || ch == '\n'|| ch == '-' || ch == '\n')
        return true;
    return false;
}