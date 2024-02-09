//incomplete 
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <string>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment
    or the product name, book author, and clothing brand we define a keyword to be any string of 2 or more characters. 
    If such a word has punctuation it should be split at each punctuation character and the resulting substrings (of 2 or more characters) should be used as keywords. Here are some examples:
    Men's should yield just a keyword of Men
    J. would not yield any keyword since the remaining substring J is only 1 character
    I'll would yield just ll since that substring is 2 or more characters (this is obviously a poor keyword but we’ll follow this rule for simplicity)
    For other keywords (book ISBN and movie genre) no punctuation or size analysis is necessary and it should be used verbatim as a keyword. Here is an example:
    The ISBN 978-000000000-1 should be used exactly as is for the keyword entry
    It is suggested you store your keywords in a common case so that searching is easy and case-insensitive 
    **/
    //call product.cpp
//parse the word to 
std::set<std::string> parseStringToWords(string rawWords)
{
    //check if word is 2 characters or more 
     //make raw words a stringstream
    std::stringstream ss(rawWords);
    //define set string variable to return 
    std::set<std::string> words; 

    //while the stringstream of words can go into word string 
    while (ss >> rawWords) {
        
        //check the words stringstream is more than 2 characters 

        for (size_t i = 0; i<rawWords.size(); i++) {
            // If the character is punctuation, split the word and add substrings as keywords
            if (ispunct(rawWords[i])) {
                //start begins at first index
                size_t start = 0;
                // if substring before the punctuation is greater than two 
                std::string substring = rawWords.substr(start, i - start);
                if (substring.size() >= 2) {
                    //than the substring equal the characters before the punctuation 
                    words.insert(substring); 
                }
                start = i + 1; 
                   

                    }
                }
                
            
    }
    return words; 
}


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
