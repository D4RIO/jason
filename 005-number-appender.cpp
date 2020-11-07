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
	catch (...) {}

	try
		{
			nums->rewindBlock();
			while(1)
				{
					string value = nums->nextChainValue();
					cout << "B:[" << value << "]" << endl;
				}
		}
	catch (...) {}

	return 0;
}
