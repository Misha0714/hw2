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


//parse words that have punctuation 
std::set<std::string> parseStringToWords(string rawWords)
{
  // convert to lower
    std::cout << rawWords << std::endl;
    rawWords = convToLower(rawWords); 
    //check if word is 2 characters or more 
     //make raw words a stringstream
    std::stringstream ss(rawWords);
    //define set string variable to return 
    std::set<std::string> words; 

    std::string curWord;
    std::string substring;
    //problem with parser 
    //while the stringstream of words can go into word string 
    while (ss >> curWord) {
        
        //check the words stringstream is more than 2 characters 
      int start=0; 
        for (size_t i = 0; i<curWord.size(); i++) {
            // If the character is punctuation, split the word and add substrings as keywords
            substring = curWord.substr(start, i-start);
            if (ispunct(curWord[i])) {
                if (substring.size() >= 2) {
                    //than the substring equal the characters before the punctuation 
                    words.insert(substring); 
                }
                start = start+(i-start) + 1; 
                }
          }  
          if (substring.size() >= 2) {
                    //than the substring equal the characters before the punctuation 
                    words.insert(curWord.substr(start,curWord.size()-start)); 
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
