#ifndef __PASSGEN_H_
#define __PASSGEN_H_

#include <vector>
#include <iostream>

class PassGen {

private:
  std::vector<std::string> _collection;

public:
  /* GETTERS / SETTERS */
  std::vector<std::string> *getCollection() {return &_collection;}
  /* VECTOR-RELATED */
  void clear() {this->getCollection()->clear();}
  void push_back (std::string yourStr) {this->getCollection()->push_back(yourStr);}
  /* INTERFACE */
  void loadFile(std::string);
  void print();
  void removeDuplicates();

};


#endif // __PASSGEN_H_
