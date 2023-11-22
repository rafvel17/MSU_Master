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

bool comparePairs(      // Return true iff x < y
    const pair<unicodeString, int>& x,
    const pair<unicodeString, int>& y
);

ostream& operator<<(ostream& s, const unicodeString& txt);

bool operator<(const unicodeString& s1, const unicodeString& s2);  






int main()
{
    map <unicodeChar,int> rusSymb_Ord;
    for (int i = 1; i < 66; i+=2)
    {
        rusSymb_Ord[russianLetter(i)] = i/2;
    }

    // for (auto elem : rusSymb_Ord)
    //     cout << elem.second << endl;
    vector<int> s;
    int l = 0;
    cout << "Choose a base word:" << endl;
    cin >> l;
    while (l != -1)
    {   
        s.push_back(l);
        cin >> l;
    }
    cout << s.size() << endl;
    unicodeString baseWord;
    for (int i = 0; i < s.size(); ++i)
    {
        baseWord[i] = russianLetter(s.at(i)*2+1);
    }
    
    std::map<int,int> baseRule;
    for (int i = 0; i < s.size(); ++i)
    {
        baseRule[i] = russianLetterOrder_NoCase(baseWord[i]);
    }
     for (auto elem : baseRule)
        cout << elem.second << endl;


    ifstream infile ("text.txt");
    ofstream outfile ("encoded_text.txt");
    
    for (auto elem : baseWord)
        output_utf8(outfile, elem);


    int counter = 0;
    //unicodeString current;

    while (true)
    {
        bool readFails = false;
        unicodeChar c;
        // cin >> c; 
        c = unicodeChar(get_utf8_code_point(infile, readFails));
        if (readFails)
            break;
        if (isRussianLetter(c))
        {
            //c = toLowerLetter(c);
            int cOrd = russianLetterOrder_NoCase(c);
            cOrd += baseRule[counter % s.size()];
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








bool comparePairs(      // Return true iff x < y
    const pair<unicodeString, int>& x,
    const pair<unicodeString, int>& y
) {
    if (x.second > y.second) {
        return true;
    } else if (x.second < y.second) {
        return false;
    }
    assert(x.second == y.second);
    return (x.first < y.first);
}

bool operator<(const unicodeString& s1, const unicodeString& s2) {
    size_t l1 = s1.length();
    size_t l2 = s2.length();
    for (size_t i = 0; i < l1; ++i) {
        if (i >= l2) {
            // s2 is a beginning of s1
            return false;
        }
        int c = compareRussianLetters(s1[i], s2[i]);
        if (c < 0) {
            return true;
        } else if (c > 0) {
            return false;
        }
        assert(s1[i] == s2[i]);
    }
    if (l2 > l1) {
        return true;
    }
    assert(l1 == l2);
    return false;
}

ostream& operator<<(ostream& s, const unicodeString& txt) {
    size_t l = txt.length();
    for (size_t i = 0; i < l; ++i) {
        output_utf8(s, txt[i]);     
    }
    return s;    
}