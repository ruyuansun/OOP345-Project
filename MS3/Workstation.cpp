// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Nov 28, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm> 
#include <iomanip>
#include "Workstation.h"
using namespace std;
namespace sdds {
   //global variables
   std::deque<CustomerOrder> g_pending{};
   std::deque<CustomerOrder> g_completed{};
   std::deque<CustomerOrder> g_incomplete{};

   Workstation::Workstation(const std::string& str) :Station(str) {}

   void Workstation::fill(std::ostream& os) {  //once the item handeled by the workstation has been processed (either fulfilled or not fulfilled), move the order to the next station by attemptToMoveOrder()
      if (!m_orders.empty()) {  //if there are CustomerOrders in the queue (i.e. g_pending is not empty)
         m_orders.front().fillItem(*this, os);  //fills the item, handled by this station, in the order at the front of the queue. //front() - returns a reference to the first element of the queue
      }
   }

   bool Workstation::attemptToMoveOrder() {
      //check if the item in the order that is handled by the workstation has been processed by the workstation (i.e. Workstation::fill() has been called). 
      //Before Workstation::fill() is attampted, the order can only be passed to the next station (if there's one) directly when no inventory is at current station(considered as unfulfilled).
      /*If Workstation::fill() has been attempted, the order can be passed to the next station(if there's one) when none 
         of items in the order is needed from this station(considered as fulfilled).If the order needs item from this
         station, the status of the item should be either fulfilled or unfulfilled(i.e.it runs out of inventory at this
            station).We can use the status of item to verifies the qualification of passing to the next station.*/
      if (!m_orders.empty()) {
         if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0) {  //If the order requires no more service at this station (i.e. item is fulfilled) or cannot be filled
            //OR the order cannot be filled (i.e. item is not fulfilled because of not enough inventory at this station)
            if (m_pNextStation != nullptr) {  //if there's a next station
               *m_pNextStation += std::move(m_orders.front());
            }
            else {
               if (m_orders.front().isOrderFilled()) {   //if the whole order is fulfilled
                  g_completed.push_back(std::move(m_orders.front()));
               }
               else {
                  g_incomplete.push_back(std::move(m_orders.front()));
               }
            }
            m_orders.pop_front();  //removes the first element from the queue
            return true;
         }
      }
      return false;
   }

   void Workstation::setNextStation(Workstation* station) {
      m_pNextStation = station;
   }
   Workstation* Workstation::getNextStation() const {
      return m_pNextStation;
   }
   void Workstation::display(std::ostream& os) const {
      if (m_pNextStation != nullptr) {
         os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
      }
      else {
         os << getItemName() << " --> " << "End of Line" << endl;
      }
   }
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
      m_orders.push_back(std::move(newOrder));   //append newOrder to the end of the old m_orders queue
      return *this;
   }

}