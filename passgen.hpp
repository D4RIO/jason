#ifndef __PASSGEN_H_
#define __PASSGEN_H_

#include <vector>
#include <unordered_map>
#include <iostream>

class PassGen {

private:
  std::vector<std::string>                     _collection;
  std::unordered_map<std::string,std::string>  _charsets;

protected:
  void configDataLoad (std::string, std::string, std::string);

public:
  /* GETTERS / SETTERS */
  std::vector<std::string> *getCollection()
  {return &_collection;}
  std::unordered_map<std::string,std::string> *getCharSets()
  {return &_charsets;}
  std::string getCharSet(std::string id)
  {return _charsets[id];}
  /* VECTOR-RELATED */
  void clear()
  {this->getCollection()->clear();}
  void push_back (std::string yourStr)
  {this->getCollection()->push_back(yourStr);}
  /* INTERFACE */
  void loadFile(std::string);
  void loadConfigFile(std::string);
  void print();
  void removeDuplicates();

};


#endif // __PASSGEN_H_
