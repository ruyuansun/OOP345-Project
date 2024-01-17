// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Dec 02, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <iomanip>
#include <functional>
#include "LineManager.h"
using namespace std;
namespace sdds {
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {

      //vector<Workstation*>& stations stores all stations read from station1.txt and station2.txt. 
      if (file.empty()) {
         throw string("ERROR: No filename provided.");
      }
      ifstream filename(file);
      if (!filename)
         throw string("Unable to open [") + file + "] file.";
      
      try {
         string record;
         while (!filename.eof()) {
            getline(filename, record);
            string workstation = record.substr(0, record.find('|'));
            string nextWorkstation = record.erase(0, workstation.size() + 1);    //erase the first substring and the delimiter

            //iterate over all stations to find the address of matching station
            auto it = find_if(stations.begin(), stations.end(), [=](Workstation* station) {  //use [=] to get workstation string, Workstation* station repsents the current element of vector<Workstation*>& stations
               return workstation == station->getItemName();
               });
            m_activeLine.push_back(*it);

            if (nextWorkstation != "") {
               auto it_nw = find_if(stations.begin(), stations.end(), [=](Workstation* station) {
                  return nextWorkstation == station->getItemName();
                  });
               m_activeLine.back()->setNextStation(*it_nw);    //set the next staion for the current station
            }
            else {   //the last station with no next station
               m_activeLine.back()->setNextStation(nullptr);
            }
         }

         //find the first station = find the station in m_activeLine that is not the next station of any station
         for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation1) {
            //find_if: If pred is false for all elements, the function returns last. https://cplusplus.com/reference/algorithm/find_if/
            auto previousOfStation1 = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation2)
               {
                  return workStation1 == workStation2->getNextStation();
               });
            if (previousOfStation1 == m_activeLine.end())   //if previousOfStation1 is not found, workStation is the first station.
            {
               m_firstStation = workStation1;
            }
            });

         m_cntCustomerOrder = g_pending.size();
      }
      catch (...) {
         throw "Error in LineManager constructor.";
      }
   }

   void LineManager::reorderStations() {
      std::vector<Workstation*> orderedStations;
      orderedStations.push_back(m_firstStation);  //set the first element

      while (orderedStations.back()->getNextStation()) {   //while the next station is not nullptr (i.e. last station in line hasn't been pushed back to orderedStation)
         orderedStations.push_back(orderedStations.back()->getNextStation());
      };

      m_activeLine = orderedStations;
   }

   bool LineManager::run(std::ostream& os) {
      static int cnt = 1;  //count how many times the function has been called
      os << "Line Manager Iteration: " << cnt << std::endl;
      cnt++;
      if (!g_pending.empty()){
         *m_firstStation += std::move(g_pending.front()); //moves the order at the front of the g_pending queue to the m_firstStationand remove it from the queue.
         g_pending.pop_front();
      }
      //for each station on the line, executes one fill operation
      for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* workStation) {
         workStation->fill(os);
         });
      //for each station on the line, attempts to move an order down the line
      for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* workStation) {
         workStation->attemptToMoveOrder();
         });
      return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
   }

   void LineManager::display(std::ostream& os) const {
      for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* workStation) {
         workStation->display(os);
         });
   }
}