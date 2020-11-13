#ifndef __APPENDERS_H_
#define __APPENDERS_H_

#include <iostream>
#include <fstream>
#include <vector>


class ChainsawExcept {
public:
	ChainsawExcept(const int t) {this->type = t; this->info = "";}
	ChainsawExcept(const int t, const char *x) {this->type = t; this->info = x;}
	int         type;
	std::string info;
	const char * describe() {
		std::string temp = "";
		switch (this->type)
			{
			case ChainsawExcept::NoMore:
				return "No more values in the block, but you can still rewindBlock()";
			case ChainsawExcept::UnknownType:
				return "An unknown appender type was received";
			case ChainsawExcept::UnknownAttribute:
				return this->info.c_str();
			case ChainsawExcept::IOFailure:
				return "Some I/O error happened";
			case ChainsawExcept::OK:
				return "No error was found";
			}
		return NULL;
	}
	static const int NoMore = 1;
	static const int UnknownType = 2;
	static const int UnknownAttribute = 3;
	static const int IOFailure = 4;
	static const int OK = 0;
};



class Chainsaw {
	Chainsaw *_nextChainsaw;
	int _minLength;
	int _maxLength;
	int _currentLength;

protected:
	virtual std::string getBlockValue() = 0;
	virtual void doAdvance() = 0; // can throw ChainsawExcept (::NoMore)
	virtual void increaseCurrentLength() {_currentLength++;}
	int getCurrentLength() {return _currentLength;}
	void resetCurrentLength() {_currentLength = 0;}

public:
	Chainsaw() {
		_nextChainsaw = NULL;
		_currentLength = 0;
	}
	~Chainsaw() {}
	Chainsaw *getNextChainsaw() {
		return this->_nextChainsaw;
	}
	int getMinLength() {return _minLength;}
	int getMaxLength() {return _maxLength;}
	void setMinLength(int yourMin) {_minLength = yourMin;_currentLength = _minLength;}
	void setMaxLength(int yourMax) {_maxLength = yourMax;}
	std::string nextChainValue();
	virtual void rewindBlock() = 0;
	virtual void setAttribute(std::string, std::string) = 0;
};



class ChainsawNumber : public Chainsaw {
	long int _number;

protected:
	std::string getBlockValue();
	void doAdvance();
	void increaseCurrentLength();

public:
	ChainsawNumber() {
		_number = -1L; // so that next starts from 0
		this->setMinLength(0);
		this->setMaxLength(2);
	}
	void rewindBlock();
	void setAttribute(std::string,std::string);
};




class ChainsawCharset : public Chainsaw {
	std::vector<size_t> indexes;
	std::string         symbolList;
protected:
	std::string getBlockValue();
	void doAdvance();
	void increaseCurrentLength();

public:
	ChainsawCharset() {
		this->setMinLength(0);
		this->setMaxLength(2);
		this->indexes.clear();
		this->symbolList="";
	}
	void rewindBlock();
	void setAttribute(std::string,std::string);
};



class ChainsawDictionary : public Chainsaw {
	std::ifstream input;
	std::string line;
protected:
	std::string getBlockValue();
	void doAdvance();
	void increaseCurrentLength();

public:
	ChainsawDictionary() {
		this->setMinLength(1);
		this->setMaxLength(2);
	}
	void rewindBlock();
	void setAttribute(std::string,std::string);
};



class ChainsawFactory {
public:
  static Chainsaw *create(std::string);
};



#endif // __APPENDERS_H_
