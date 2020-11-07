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



string Appender::nextChainValue()
{

  string appendix = "";

  // if there is a next member, ask it for a new value
  if (this->getNextAppender())
	{
	  try {
		appendix = this->getNextAppender()->nextChainValue();
	  }
	  catch (AppenderExcept e) {
		// but if he runs out of strings, then we need to
		// rewindBlock it and start again, with our next
		if (e.type == AppenderExcept::NoMore)
		  {
			// this method can also throw AppenderExcept::NoMore
			this->doAdvance();

			this->getNextAppender()->rewindBlock();

			appendix = this->getNextAppender()->nextChainValue();
		  }
	  }
	}

  else this->doAdvance();

  return (this->getBlockValue() + appendix);
}


#include <math.h> // pow
void AppendNumber::doAdvance()
{
  /* Adavnce is considered by:
   * 1. moving the number forwards up to the current number of digits
   * 2. getting bigger
   */
  _number++; //TODO implement

  if (_number >= pow(10,this->getCurrentLength())) {
	if (this->getCurrentLength() < this->getMaxLength())
	  this->increaseCurrentDigits();
	else
	  throw AppenderExcept(AppenderExcept::NoMore);
  }
}

void AppendNumber::rewindBlock()
{
	_number = -1L;
	resetCurrentLength();
}


string AppendNumber::getBlockValue()
{
  if (this->getCurrentLength()) {
	stringstream s;
	s << std::right << std::setw(this->getCurrentLength())
	  << std::setfill('0') << _number;
	return s.str();
  }
  else {
	return string("");
  }
}
