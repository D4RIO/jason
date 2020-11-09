#include "appenders.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

Appender* AppenderFactory::create(string type)
{
  if (type == "NUMBER")
		return new AppendNumber();
	if (type == "CHARSET")
		return new AppendCharset();

  throw AppenderExcept(AppenderExcept::UnknownType);
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
  _number++;

	if (_number >= pow(10,this->getCurrentLength()))
		{
			if (this->getCurrentLength() < this->getMaxLength())
				this->increaseCurrentLength();
			else
				throw AppenderExcept(AppenderExcept::NoMore);
		}
}

void AppendNumber::rewindBlock()
{
	_number = -1L;
	this->resetCurrentLength();
}


string AppendNumber::getBlockValue()
{
	if (this->getCurrentLength())
		{
			stringstream s;
			s << std::right << std::setw(this->getCurrentLength())
				<< std::setfill('0') << _number;
			return s.str();
		}

	return string("");
}


void AppendNumber::increaseCurrentLength()
{
	Appender::increaseCurrentLength();
	_number = 0L;
}


void AppendNumber::setAttribute(string attrName, string value)
{
	int ivalue;
	try
		{
			ivalue = stoi(value);
		}
	catch (...)
		{
			string temp = "Attribute \"" + attrName +
				"\", given to NUMBER, is not an integer";
			throw AppenderExcept(AppenderExcept::UnknownAttribute,
													 temp.c_str());
		}


	if (attrName == "minLength")
		{
			this->setMinLength(ivalue);
		}
	else if (attrName == "maxLength")
		{
			this->setMaxLength(ivalue);
		}
	else
		{
			string temp = "Attribute \"" + attrName + "\" is not recognized by NUMBER";
			throw AppenderExcept(AppenderExcept::UnknownAttribute,
													 temp.c_str());
		}
}




string AppendCharset::getBlockValue()
{
	string ret = "";
	int i;
	if (this->getCurrentLength())
		{
			for (i = 1;
					 i <= this->getCurrentLength();
					 i++)
				{
					ret += symbolList[indexes[i]];
				}
		}
	return ret;
}

void AppendCharset::doAdvance()
{
	int i;
	if (this->getCurrentLength()>0)
		{
			indexes[this->getCurrentLength()]++;
			for (i = (this->getCurrentLength());
					 i > 0;
					 i--)
				{
					if (this->indexes[i] == this->symbolList.length())
						{
							indexes[i] = 0;
							if (i > 1) indexes[i-1]++;
							else this->increaseCurrentLength();
						}
				}
	}
	else
		this->increaseCurrentLength();
}

void AppendCharset::increaseCurrentLength()
{
	if (this->getCurrentLength() == this->getMaxLength())
		throw AppenderExcept(AppenderExcept::NoMore);

	Appender::increaseCurrentLength();
	indexes.push_back(0);
}

void AppendCharset::rewindBlock()
{
	this->indexes.clear();
	this->resetCurrentLength();
}

void AppendCharset::setAttribute(string attrName,string value)
{
	int ivalue;

	if (attrName == "minLength" || attrName == "maxLength")
		{
			try
				{
					ivalue = stoi(value);
				}
			catch (...)
				{
					string temp = "Attribute \"" + attrName +
						"\", given to NUMBER, is not an integer";
					throw AppenderExcept(AppenderExcept::UnknownAttribute,
															 temp.c_str());
				}
		}


	if (attrName == "minLength")
		{
			this->setMinLength(ivalue);
		}
	else if (attrName == "maxLength")
		{
			this->setMaxLength(ivalue);
		}
	else if (attrName == "charset")
		{
			this->symbolList = value;
		}
	else
		{
			string temp = "Attribute \"" + attrName + "\" is not recognized by NUMBER";
			throw AppenderExcept(AppenderExcept::UnknownAttribute,
													 temp.c_str());
		}
}
