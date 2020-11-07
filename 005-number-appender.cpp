#include "appenders.hpp"

using namespace std;

int main(void)
{
  Appender *nums = AppenderFactory::create("NUMBER");
  nums->setMinLength(0);
  nums->setMaxLength(1);
  try {
	while(1)
	  cout << "[" << nums->nextChainValue() << "]" << std::endl;
  }
  catch (...){}
}
