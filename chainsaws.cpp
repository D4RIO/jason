#include "chainsaws.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

Chainsaw* ChainsawFactory::create(string type)
{
  if (type == "NUMBER")
	  return new ChainsawNumber();
  if (type == "CHARSET")
	  return new ChainsawCharset();
  if (type == "DICTIONARY")
	  return new ChainsawDictionary();

  throw ChainsawExcept(ChainsawExcept::UnknownType);
}



string Chainsaw::nextChainValue()
{
	string appendix = "";

	while (this->getCurrentLength() < this->getMinLength())
		this->increaseCurrentLength();

	// if there is a next member, ask it for a new value
	if (this->getNextChainsaw())
	{
		try
		{
			if (this->firstRun)
			{
				this->doAdvance();
				this->firstRun = false;
			}
			appendix = this->getNextChainsaw()->nextChainValue();
		}
		catch (ChainsawExcept e)
		{
			// but if he runs out of strings, then we need to
			// rewindBlock it and start again, with our next
			if (e.type == ChainsawExcept::NoMore)
			{
				// this method can also throw ChainsawExcept::NoMore
				this->doAdvance();

				this->getNextChainsaw()->rewindBlock();

				appendix = this->getNextChainsaw()->nextChainValue();
			}
		}
		catch (...)
		{
			throw ChainsawExcept(ChainsawExcept::UnknownError);
		}
	}
	else
	{
		this->doAdvance();
		this->firstRun = false;
	}

	return ("{" + this->getBlockValue() + "}" + appendix);
}

void Chainsaw::addChain(Chainsaw *ref)
{
	if (this->getNextChain())
		this->getNextChain()->addChain(ref);
	else
		this->_nextChainsaw = ref;
}



#include <math.h> // pow
void ChainsawNumber::doAdvance()
{
	/* Adavnce is considered by:
	 * 1. moving the number forwards up to the current number of digits
	 * 2. getting bigger
	 */
	_number++;

	if (_number >= pow(10,this->getCurrentLength()))
	{
		if (this->getCurrentLength() < this->getMaxLength())
		{
			this->increaseCurrentLength();
		}
		else
		{
			throw ChainsawExcept(ChainsawExcept::NoMore);
		}
	}
}

void ChainsawNumber::rewindBlock()
{
	_number = -1L;
	this->resetCurrentLength();
	Chainsaw::rewindBlock();
}


string ChainsawNumber::getBlockValue()
{
	if (this->getCurrentLength())
	{
		stringstream s;
		s << right << setw(this->getCurrentLength())
		  << setfill('0') << _number;
		return s.str();
	}

	return string("");
}


void ChainsawNumber::increaseCurrentLength()
{
	Chainsaw::increaseCurrentLength();
	_number = 0L;
}


void ChainsawNumber::setAttribute(string attrName, string value)
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
		throw ChainsawExcept(ChainsawExcept::UnknownAttribute,
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
		throw ChainsawExcept(ChainsawExcept::UnknownAttribute,
				     temp.c_str());
	}
}

string ChainsawNumber::getChainDescription()
{
	string ret = "NUMBER";
	ret += "{min="+to_string(getMinLength())+"}";
	ret += "{max="+to_string(getMaxLength())+"}";
	if (this->getNextChain())
		ret += this->getNextChain()->getChainDescription();
	return ret;
}

unsigned long long ChainsawNumber::size()
{
	unsigned long long retval = 0L;
	int i;

	for (i = this->getMinLength();
	     i <= this->getMaxLength();
	     i++)
	{
		retval += pow (10, i);
	}

	if (this->getNextChain())
	{
		retval *= this->getNextChain()->size();
	}

	return retval;
}




string ChainsawCharset::getBlockValue()
{
	string ret = "";
	int i=0;
	if (this->getCurrentLength())
	{
		for (i = 0;
		     i < this->getCurrentLength();
		     i++)
		{
			ret += symbolList[indexes[i]];
		}
	}
	return ret;
}

void ChainsawCharset::doAdvance()
{
	int i;
	if (!this->firstRun)
	{
		if (this->getCurrentLength()>0)
		{
			indexes[this->getCurrentLength()-1]++;
			for (i = (this->getCurrentLength()-1);
			     i >= 0;
			     i--)
			{
				if (this->indexes[i] == this->symbolList.length())
				{
					indexes[i] = 0;
					if (i > 0) indexes[i-1]++;
					else this->increaseCurrentLength();
				}
			}
		}
		else
		{
			this->increaseCurrentLength();
		}
	}
}

void ChainsawCharset::increaseCurrentLength()
{
	if (this->getCurrentLength() == this->getMaxLength())
		throw ChainsawExcept(ChainsawExcept::NoMore);

	Chainsaw::increaseCurrentLength();
	indexes.push_back(0);
}

void ChainsawCharset::rewindBlock()
{
	this->indexes.clear();
	this->resetCurrentLength();
	Chainsaw::rewindBlock();
}

void ChainsawCharset::setAttribute(string attrName,string value)
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
				"\", given to CHARSET, is not an integer";
			throw ChainsawExcept(ChainsawExcept::UnknownAttribute,
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
		string temp = "Attribute \"" + attrName + "\" is not recognized by CHARSET";
		throw ChainsawExcept(ChainsawExcept::UnknownAttribute,
				     temp.c_str());
	}
}

string ChainsawCharset::getChainDescription()
{
  string ret = "CHARSET";
  ret += "{min="+to_string(getMinLength())+"}";
  ret += "{max="+to_string(getMaxLength())+"}";
  if (this->getNextChain())
	ret += this->getNextChain()->getChainDescription();
  return ret;
}

unsigned long long ChainsawCharset::size()
{
	unsigned long long retval = 0L;
	int i;

	for (i = this->getMinLength();
	     i <= this->getMaxLength();
	     i++)
	{
		size_t n = this->symbolList.length();
		retval += pow(n, i);
	}

	if (this->getNextChain())
	{
		retval *= this->getNextChain()->size();
	}

	return retval;
}




string ChainsawDictionary::getBlockValue()
{
	return line;
}

void ChainsawDictionary::doAdvance()
{
	try
	{
		if(! getline(this->input, this->line))

			throw ChainsawExcept(ChainsawExcept::NoMore);
	}
	catch (...)
	{
		throw ChainsawExcept(ChainsawExcept::NoMore);
	}
}

void ChainsawDictionary::increaseCurrentLength()
{
	Chainsaw::increaseCurrentLength();
}

void ChainsawDictionary::rewindBlock()
{
	this->input.clear();
	this->input.seekg (0, this->input.beg);
	Chainsaw::rewindBlock();
}

#include <algorithm> // std::count
void ChainsawDictionary::setAttribute(string attrName, string value)
{
	if (attrName == "src")
	{
		try
		{
			this->input.open(value, ifstream::in);

			// count lines in the buffer and store
			this->number_of_lines = count(istreambuf_iterator<char>(this->input),
						     istreambuf_iterator<char>(), '\n');
			this->number_of_lines++;

			this->rewindBlock();
		}
		catch (...)
		{
			throw ChainsawExcept(ChainsawExcept::IOFailure);
		}

		if (this->input.bad() || this->input.fail())
			throw ChainsawExcept(ChainsawExcept::IOFailure);

		this->src = value;

	}
	else
	{
		string temp = "Attribute \"" + attrName + "\" is not recognized by DICTIONARY";
		throw ChainsawExcept(ChainsawExcept::UnknownAttribute,
				     temp.c_str());
	}
}

string ChainsawDictionary::getChainDescription()
{
	string ret = "DICTIONARY";
	ret += "{src="+this->src+"}";
	if (this->getNextChain())
		ret += this->getNextChain()->getChainDescription();
	return ret;
}

unsigned long long ChainsawDictionary::size()
{
	unsigned long long retval = this->number_of_lines;

	if (this->getNextChain())
	{
		retval *= this->getNextChain()->size();
	}

	return retval;
}

