#include <fstream>
#include <sstream>
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



void PassGen::configDataLoad(string type,
                             string identifier,
                             string content)
{
  if (type == "set") {
    this->getCharSets()->insert({identifier, content});
  }

  else {
    throw string("Unknown type '"+type+"' in this line (line ignored)");
  }
}



void PassGen::loadConfigFile(string fileName)
{
  ifstream input;
  string line;
  string word;
  vector<string> words;
  int linenumber = 0;

  input.open (fileName, ifstream::in);

  while (getline(input, line, '\n')) {
    linenumber++;
    // Tokenize input
    stringstream sline(line);
    while (getline(sline, word, '\t')) {
      words.push_back (word);
    }
    // TODO: Refactor this to another method
    if (words.size() < 3) {

      cout << "WRN [" << fileName << ":" << linenumber
           << "] Wrong line format (line ignored)\n";

      cout << "INF [" << fileName << ":" << linenumber
           << "] It should be a tab separated file like 'type<TAB>identifier<TAB>content'. "
           << " See --help.\n";

    } else {

      /*FIXME: tabs inside a content are missinterpreted */
      /*       it should be words[2]+words[3]+···        */
      try {
        //                     type      identifier content
        this->configDataLoad ( words[0], words[1],  words[2] );
      }
      catch (string e) {
        cout << "WRN [" << fileName << ":" << linenumber
             << "] " << e << "\n";
      }
      catch (...) {
        cout << "WRN [" << fileName << ":" << linenumber
             << "] UNEXPECTED ERROR LOADING CONFIG (please submit)\n";
      }
    }
    words.clear();
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
