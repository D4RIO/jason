#include "chainsaws.hpp"

using namespace std;

int main(void)
{
  Chainsaw *set;
  try
	{
	  set = ChainsawFactory::create("CHARSET");
	  set->setAttribute("minLength", "1");
	  set->setAttribute("maxLength", "1");
	}
  catch (ChainsawExcept e)
	{
	  cout << e.describe() << endl;
	  return -1;
	}
  catch(...)
	{
	  cout << "Unknown error building and setting CHARSET"
		   << endl;
	  return -1;
	}

  cout << "SETTING CHARSET TO '#$%&'" << endl;

  try
	{
	  set->setAttribute("charset", "#$%&");
	}
  catch (...)
	{
	  cout << "unexpected error" << endl;
	  return -1;
	}


  cout << "GETTING VALUES..." << endl;
  try
	{
	  int i = 1;
	  while (1)
		{
		  string value = set->nextChainValue();
		  cout << i << "[" << value << "]" << endl;
		  i++;
		}
	}
  catch (ChainsawExcept e)
	{
	  cout << e.describe() << endl;
	}
  catch (...)
	{
	  cout << "unexpected error" << endl;
	  return -1;
	}

  return 0;

}
