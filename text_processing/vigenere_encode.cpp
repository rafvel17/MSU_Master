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
    std::string baseWord;
    cout << "Choose a base word:" << endl; 
    cin >> baseWord;
    int baseWordLength = baseWord.length();
    std::map<int,unicodeChar> baseRule;
    for (int i = 0; i < baseWordLength; ++i)
    {
        baseRule[i] = russianLetterOrder_NoCase(baseWord[i]);
    }

    fstream file;
    file.open("text.txt", ios_base::in | ios_base::out);
    int counter = 0;
    char current;
    while ((current = getchar()) != EOF)
    {
        if (current == ' ')
            counter = 0;
        if (isRussianLetter(current))
        {
            current = lowerRussianLetter(russianLetterOrder_NoCase(current) + baseRule[counter % baseWordLength]);
            putchar(current);//?????????????????????
            counter++;
        }
    }
    file.close();



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