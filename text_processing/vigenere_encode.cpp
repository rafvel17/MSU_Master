#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>
#include "utf8/utf8.h"

using namespace std;

typedef int unicodeChar;
typedef basic_string<unicodeChar> unicodeString;

int main()
{
    map <unicodeChar,int> rusSymb_Ord;
    for (int i = 1; i < 66; i+=2)
    {
        rusSymb_Ord[russianLetter(i)] = i/2;
    }

    ifstream key ("key.txt");
    unicodeString baseWord;

    while (true)
    {
        bool readFails = false;
        unicodeChar c;
        // cin >> c; 
        c = unicodeChar(get_utf8_code_point(key, readFails));
        if (readFails)
            break;
        if(isRussianLetter(c))
            baseWord.push_back(c);
    }

    key.close();
    std::map<int,int> baseRule;
    for (int i = 0; i < baseWord.size(); ++i)
    {
        baseRule[i] = russianLetterOrder_NoCase(baseWord[i]);
    }

    ifstream infile ("text.txt");
    ofstream outfile ("encoded_text.txt");

    int counter = 0;

    while (true)
    {
        bool readFails = false;
        unicodeChar c;
        c = unicodeChar(get_utf8_code_point(infile, readFails));
        if (readFails)
            break;
        if (isRussianLetter(c))
        {
            int cOrd = russianLetterOrder_NoCase(c);
            cOrd += baseRule[counter % baseWord.size()];
            cOrd%=33;
            c = russianLetter(cOrd * 2 + 1);
            counter++;
            output_utf8(outfile, c);
        }
        else
        {
            output_utf8(outfile, c);
            counter = 0;
        }
        
    }

    infile.close();
    outfile.close();



    return 0;
}








