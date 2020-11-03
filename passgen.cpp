#include <fstream>
#include <algorithm>
#include "./passgen.hpp"

using namespace std;



void PassGen::loadFile(string fileName)
{
  ifstream input;
  string word;

  input.open(fileName, ifstream::in);

  while (input >> word) {
    this->push_back(word);
  }

  input.close();
}



void PassGen::removeDuplicates()
{
  size_t i;
  string last;
  vector<string> vectemp;

  sort(this->getCollection()->begin(), this->getCollection()->end());

  for (i = 0;
       i < this->getCollection()->size();
       i++)
    {
      string wordAtPos = this->getCollection()->at(i);

      if (wordAtPos != last) {
        vectemp.push_back(wordAtPos);
        last = wordAtPos;
      }
    }

  this->_collection = vectemp;
}



void PassGen::print()
{
  size_t i;
  for (i = 0;
       i < getCollection()->size();
       i++)
    {
      cout << this->getCollection()->at(i) << "\n";
    }
}
