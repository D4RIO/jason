#include "chainsaws.hpp"

using namespace std;

int main(void)
{
	Chainsaw *nums = ChainsawFactory::create("NUMBER");
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
	catch (ChainsawExcept e)
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
	catch (ChainsawExcept e)
		{
			cout << e.describe() << endl;
		}



	try
		{
			cout << "NOW CREATING AN UNKNOWN TYPE (EXCEPTION EXPECTED)"
				 << endl;
			nums = ChainsawFactory::create("SomethingUnknown");
		}
	catch (ChainsawExcept e)
		{
			cout << e.describe() << endl;
		}



	try
		{
			cout << "NOW TRYING TO SET AN UNKNOWN ATTRIBUTE (EXCEPTION EXPECTED)"
				 << endl;
			nums = ChainsawFactory::create("NUMBER");
			nums->setAttribute("Something", "0");
		}
	catch (ChainsawExcept e)
		{
			cout << e.describe() << endl;
		}



	return 0;
}
