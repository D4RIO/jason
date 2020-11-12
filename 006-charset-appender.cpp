#include "appenders.hpp"

using namespace std;

int main(void)
{
  Appender *set;
  try
	{
	  set = AppenderFactory::create("CHARSET");
	  set->setMinLength(0);
	  set->setMaxLength(3);
	}
  catch (AppenderExcept e)
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
  catch (AppenderExcept e)
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
