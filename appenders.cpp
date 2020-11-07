#include "appenders.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

Appender* AppenderFactory::create(string type)
{
  if (type == "NUMBER")
	return new AppendNumber();

  return NULL;
}



string Appender::nextValue()
{

  string appendix = "";

  // if there is a next member, ask it for a new value
  if (this->getNextAppender())
	{
	  try {
		appendix = this->getNextAppender()->nextValue();
	  }
	  catch (AppenderExcept e) {
		// but if he runs out of strings, then we need to
		// rewind it and start again, with our next
		if (e.type == AppenderExcept::NoMore)
		  {
			// this method can also throw AppenderExcept::NoMore
			this->doAdvance();

			this->getNextAppender()->rewind();

			appendix = this->getNextAppender()->nextValue();
		  }
	  }
	}

  else this->doAdvance();

  return (this->getCurrent() + appendix);
}


#include <math.h> // pow
void AppendNumber::doAdvance()
{
  /* Adavnce is considered by:
   * 1. moving the number forwards up to the current number of digits
   * 2. getting bigger
   */
  _number++; //TODO implement

  if (_number >= pow(10,this->getCurrentDigits())) {
	if (this->getCurrentDigits() < this->getMax())
	  this->increaseCurrentDigits();
	else
	  throw AppenderExcept(AppenderExcept::NoMore);
  }
}

void AppendNumber::rewind()
{
  _number = 0L;
}


string AppendNumber::getCurrent()
{
  if (this->getCurrentDigits()) {
	stringstream s;
	s << std::right << std::setw(this->getCurrentDigits())
	  << std::setfill('0') << _number;
	return s.str();
  }
  else {
	return string("");
  }
}
