#include "appenders.hpp"

using namespace std;

int main(void)
{
  Appender *nums = AppenderFactory::create("NUMBER");
  nums->setMin(0);
  nums->setMax(1);
  try {
	while(1)
	  cout << "[" << nums->nextValue() << "]" << std::endl;
  }
  catch (...){}
}
