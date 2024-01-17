// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Nov 18, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm> 
#include <iomanip>
#include "Utilities.h"
using namespace std;
namespace sdds {
   char Utilities::m_delimiter = ' ';

   void Utilities::setFieldWidth(size_t newWidth) {
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth() const {
      return m_widthField;
   }

   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
      string nextToken;
      size_t delim_pos = 0;
      const string WHITESPACE = " \n\r\t\f\v";
      size_t start = 0;
      size_t end = 0;
      char delim = getDelimiter();
      delim_pos = str.find(delim, next_pos);  //start from next_post, find the position of the first match
      if (delim_pos == std::string::npos) {   //if m_delimiter is not found in str (i.e. now read the last token in the string)
         nextToken = str.substr(next_pos);   //get from "next_pos" to the end of string
         if (m_widthField < nextToken.length())
            m_widthField = nextToken.length();    
         start = nextToken.find_first_not_of(WHITESPACE);
         end = nextToken.find_last_not_of(WHITESPACE);
         nextToken = nextToken.substr(start, end - start + 1);   //trim the token
         more = false;  
      }
      else if (delim_pos == next_pos) {   //if delimiter is found at next_pos (i.e. the delimiter was found to be the first char of the string)
         more = false;
         throw next_pos;
      }
      else {  //if successful, return a copy of the extracted token found (without spaces at the beginning/end)
         nextToken = str.substr(next_pos, delim_pos - next_pos);
         if (m_widthField < nextToken.length())
            m_widthField = nextToken.length();  //updates the current object's m_widthField if its current value is less than the size of the token extracted
         start = nextToken.find_first_not_of(WHITESPACE);
         end = nextToken.find_last_not_of(WHITESPACE);
         nextToken = nextToken.substr(start, end - start + 1);   //trim the token
         more = true;
         next_pos = delim_pos + 1;
      }
      return nextToken;
   }

   void Utilities::setDelimiter(char newDelimiter) {
      m_delimiter = newDelimiter;
   }

   char Utilities::getDelimiter() {
      return m_delimiter;
   }


}