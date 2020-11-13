#include "chainsaws.hpp"

using namespace std;

int main(void)
{
  Chainsaw *dict;
  Chainsaw *nums;
  Chainsaw *syms;

  try
    {
      dict = ChainsawFactory::create("DICTIONARY");
      nums = ChainsawFactory::create("NUMBER");
      syms = ChainsawFactory::create("CHARSET");

      nums->setAttribute("minLength", "1");
      nums->setAttribute("maxLength", "3");

      syms->setAttribute("minLength", "1");
      syms->setAttribute("maxLength", "1");

      dict->setAttribute("src",       "data/007-dictionary");
      syms->setAttribute("charset",   "#!+-%$");

      dict->addChain(nums);
      dict->addChain(syms);

      cout << "SETUP OK, NOW READING" << endl;
      while (1)
        {
          string temp = dict->nextChainValue();
          cout << temp << endl;
        }
    }
  catch (ChainsawExcept e)
    {
      cerr << "FAIL: " << e.describe() << endl;
    }
  catch (...)
    {
      cerr << "UNEXPECTED ERROR" << endl;
    }

  return 0;
}
