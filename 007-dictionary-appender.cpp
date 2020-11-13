#include "chainsaws.hpp"

using namespace std;

int main(void)
{
  cout << "TRYING A SIMPLE DICTIONARY" << endl;
  Chainsaw *dict;
  try
    {
      dict = ChainsawFactory::create("DICTIONARY");
      dict->setAttribute("src", "data/007-dictionary");

      while (1)
        {
          string temp = dict->nextChainValue();
          cout << temp << endl;
        }
    }
  catch (ChainsawExcept e)
    {
      cout << e.describe() << endl;
    }
  catch (...)
    {
      cerr << "Unexpected error" << endl;
    }

  return 0;
}
