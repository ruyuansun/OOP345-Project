// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Nov 18, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H__
#define SDDS_STATION_H__
#include <iostream>
#include <string>
#include "Utilities.h"
namespace sdds {
   class Station {
      int m_stationID;    //the id of the station
      std::string m_item;  //the name of the item handled by the station
      std::string m_description;   //the description of the station(string)
      unsigned int m_nextSerial;   //the next serial number to be assigned to an item at this station
      unsigned int m_stock;   //the number of items currently in stock
      static size_t m_widthField;
      static int id_generator;
   public:
      Station(const std::string& str);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
} 
#endif