// Name: Ruyuan Sun
// Seneca Student ID: 101836229
// Seneca email: rsun35@myseneca.ca
// Date of completion: Nov 23, 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm> 
#include <iomanip>
#include "CustomerOrder.h"
using namespace std;
namespace sdds {
   size_t CustomerOrder::m_widthField = 0;

   //CustomerOrder::CustomerOrder() : m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_lstItem{ nullptr } {}

   CustomerOrder::CustomerOrder(const std::string& str) {
      //m_name   | m_product    | *m_lstItem
      Utilities temp;
      bool more = true;
      size_t pos = 0u;
      m_name = temp.extractToken(str, pos, more);
      m_product = temp.extractToken(str, pos, more);
      //Count character occurrences in a string in C++: https://stackoverflow.com/questions/3867890/count-character-occurrences-in-a-string-in-c
      m_cntItem = std::count(str.begin(), str.end(), temp.getDelimiter()) - 1;
      m_lstItem = new Item*[m_cntItem];  //DMA for the list of Items
      int i = 0;
      while (more) {
         m_lstItem[i] = new Item(temp.extractToken(str, pos, more));   //DMA for each Item by calling the extractToken() function as the parameter passed to the custom constructor of Item class
         i++; 
      }
      if (m_widthField < temp.getFieldWidth())
         m_widthField = temp.getFieldWidth();
   }

   CustomerOrder::CustomerOrder(const CustomerOrder& src) {
      throw false;
   }

   CustomerOrder::CustomerOrder(CustomerOrder&& src)noexcept {
      *this = std::move(src);
   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)noexcept {
      if (this != &src) {  //check for self-assignment
         if (m_lstItem) {
            for (size_t i = 0; i < m_cntItem; i++) {
               delete m_lstItem[i];
            }
            delete[] m_lstItem;
         }
         //shallow copy
         m_name = src.m_name;
         m_product = src.m_product;
         m_cntItem = src.m_cntItem;
         m_widthField = src.m_widthField;

         //move the resource from parameter into current instance
         m_lstItem = src.m_lstItem;

         //empty src for the next call of custom constructor
         src.m_name = "";
         src.m_product = "";
         src.m_cntItem = 0;
         src.m_lstItem = nullptr; // the parameter doesn't have the resource anymore
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder() {
      if (m_lstItem) {
         for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
         }
         delete[] m_lstItem;
      }
   }

   bool CustomerOrder::isOrderFilled() const {
      for (size_t i = 0; i < m_cntItem; i++) {
         if (!m_lstItem[i]->m_isFilled) {
            return false;
         }
      }
      return true;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const {
      for (size_t i = 0; i < m_cntItem; i++) {
         if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
            return false;
         }
      }
      return true;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os) {
      for (size_t i = 0; i < m_cntItem; i++) {   //check all items in the order
         if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {  //if the order contains unfilled item handled by the station 
            if (station.getQuantity() > 0) { //if the item is in stock at the station
               station.updateQuantity();   //substract 1 from the inventory
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();   //update m_serialNumber
               m_lstItem[i]->m_isFilled = true;
               os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
               break;   //fills only one item each time
            }
            else {   //inventory is empty
               os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
         }
      }
   }

   void CustomerOrder::display(std::ostream& os) const {
      os << m_name << " - " << m_product << endl;
      for (size_t i = 0; i < m_cntItem; i++) {
         os << "[" << right << setw(6) << setfill('0') <<m_lstItem[i]->m_serialNumber << "] " << left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName << " - ";
         if (m_lstItem[i]->m_isFilled) os << "FILLED" << endl;
         else os << "TO BE FILLED" << endl;
      }
   }
}