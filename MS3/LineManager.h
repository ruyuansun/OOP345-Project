// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Nov 28, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H__
#define SDDS_LINEMANAGER_H__
#include <iostream>
#include <string>
#include <vector>
#include "Workstation.h"
namespace sdds {
   class LineManager {
      std::vector<Workstation*> m_activeLine; //the collection of workstations for the current assembly line.
      size_t m_cntCustomerOrder;  //the total number of CustomerOrder objects
      Workstation* m_firstStation{};  //points to the first active station on the current line
   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);
      void reorderStations();
      bool run(std::ostream& os);
      void display(std::ostream& os) const;
   };
}
#endif