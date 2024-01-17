// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Nov 28, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H__
#define SDDS_WORKSTATION_H__
#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
namespace sdds {
   //global variables
   extern std::deque<CustomerOrder> g_pending;   //orders to be placed onto the assembly line at the first station
   extern std::deque<CustomerOrder> g_completed;  //orders that have been removed from the last station and have been completely filled
   extern std::deque<CustomerOrder> g_incomplete;  //orders that have been removed from the last station and could not be filled completely

   class Workstation :public Station {
      std::deque<CustomerOrder> m_orders;   //orders placed on this station
      Workstation* m_pNextStation{};
   public:
      Workstation(const std::string& str);
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station = nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);

      //the object cannot be copied or moved
      Workstation(const Workstation& src) = delete;
      Workstation& operator=(const Workstation& src) = delete;
      Workstation(Workstation&& src) = delete;
      Workstation& operator=(Workstation&& src) = delete;
   };

}
#endif