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
#include "Station.h"
using namespace std;
namespace sdds {

   size_t Station::m_widthField = 0;
   int Station::id_generator = 0;

   Station::Station(const std::string& str) {
      m_stationID = ++id_generator;

      //1.txt m_item,    m_nextSerial,   m_stock,   m_description\n
      //2.txt m_item | m_nextSerial | m_stock |  m_description\n

      Utilities temp;
      bool more = true;
      size_t pos = 0u;

      m_item = temp.extractToken(str, pos, more);
      m_nextSerial = stoi(temp.extractToken(str, pos, more));
      m_stock = stoi(temp.extractToken(str, pos, more));
      //before extracting description, it updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField
      if (m_widthField < temp.getFieldWidth())
         m_widthField = temp.getFieldWidth();
      m_description = temp.extractToken(str, pos, more);
   }

   const std::string& Station::getItemName() const {
      return m_item;
   }

   size_t Station::getNextSerialNumber() {
      return m_nextSerial++;
   }

   size_t Station::getQuantity() const {
      return m_stock;
   }

   void Station::updateQuantity() {
      if (m_stock >= 1) 
      m_stock -= 1;
   }

   void Station::display(std::ostream& os, bool full) const {
      //if(full) //ID | NAME | SERIAL |
      //if(!full)  //ID | NAME | SERIAL | QUANTITY | DESCRIPTION
      if (!full) {
         os << right << setfill('0') << setw(3) << m_stationID << " | " << left << setfill(' ') << setw(m_widthField) << m_item << " | "
            << right << setfill('0') << setw(6) << m_nextSerial << " | " << endl;
      }
      else {
         os << right << setfill('0') << setw(3) << m_stationID << " | " << left << setfill(' ') << setw(m_widthField) << m_item << " | "
            << right << setfill('0') << setw(6) << m_nextSerial << " | "
            << right << setfill(' ') << setw(4) << m_stock << " | " << m_description << endl;
      }
   }
}