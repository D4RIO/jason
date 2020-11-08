#include "appenders.hpp"

using namespace std;

int main(void)
{
	Appender *nums = AppenderFactory::create("NUMBER");
	nums->setMinLength(0);
	nums->setMaxLength(1);



	try
		{
			while(1)
				{
					string value = nums->nextChainValue();
					cout << "A:[" << value << "]" << endl;
				}
		}
	catch (AppenderExcept e)
		{
			cout << e.describe() << endl;
		}



	try
		{
			cout << "REWINDING..." << endl;
			nums->rewindBlock();
			while(1)
				{
					string value = nums->nextChainValue();
					cout << "B:[" << value << "]" << endl;
				}
		}
	catch (AppenderExcept e)
		{
			cout << e.describe() << endl;
		}



	try
		{
			cout << "NOW CREATING AN UNKNOWN TYPE (EXCEPTION EXPECTED)"
				 << endl;
			nums = AppenderFactory::create("SomethingUnknown");
		}
	catch (AppenderExcept e)
		{
			cout << e.describe() << endl;
		}



	try
		{
			cout << "NOW TRYING TO SET AN UNKNOWN ATTRIBUTE (EXCEPTION EXPECTED)"
				 << endl;
			nums = AppenderFactory::create("NUMBER");
			nums->setAttribute("Something", 0);
		}
	catch (AppenderExcept e)
		{
			cout << e.describe() << endl;
		}



	return 0;
}
