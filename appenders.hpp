#ifndef __APPENDERS_H_
#define __APPENDERS_H_

#include <iostream>
#include <vector>


class AppenderExcept {
public:
  AppenderExcept(const int t) {this->type = t; this->info = "";}
	AppenderExcept(const int t, const char *x) {this->type = t; this->info = x;}
  int         type;
	std::string info;
	const char * describe() {
		std::string temp = "";
		switch (this->type)
			{
			case AppenderExcept::NoMore:
				return "No more values in the block, but you can still rewindBlock()";
			case AppenderExcept::UnknownType:
				return "An unknown appender type was received";
			case AppenderExcept::UnknownAttribute:
				return this->info.c_str();
			case AppenderExcept::OK:
				return "No error was found";
			}
		return NULL;
	}
  static const int NoMore = 1;
	static const int UnknownType = 2;
	static const int UnknownAttribute = 3;
  static const int OK = 0;
};



class Appender {
	Appender *_nextAppender;
	int _minLength;
	int _maxLength;
	int _currentLength;

protected:
	virtual std::string getBlockValue() = 0;
	virtual void doAdvance() = 0; // can throw AppenderExcept (::NoMore)
	virtual void increaseCurrentLength() {_currentLength++;}
	int getCurrentLength() {return _currentLength;}
	void resetCurrentLength() {_currentLength = 0;}

public:
	Appender() {
		_nextAppender = NULL;
		_currentLength = 0;
	}
	~Appender() {}
	Appender *getNextAppender() {
		return this->_nextAppender;
	}
	int getMinLength() {return _minLength;}
	int getMaxLength() {return _maxLength;}
	void setMinLength(int yourMin) {_minLength = yourMin;_currentLength = _minLength;}
	void setMaxLength(int yourMax) {_maxLength = yourMax;}
	std::string nextChainValue();
	virtual void rewindBlock() = 0;
	virtual void setAttribute(std::string, std::string) = 0;
};



class AppendNumber : public Appender {
	long int _number;

protected:
	std::string getBlockValue();
	void doAdvance();
	void increaseCurrentLength();

public:
	AppendNumber() {
		_number = -1L; // so that next starts from 0
		this->setMinLength(0);
		this->setMaxLength(2);
	}
	void rewindBlock();
	void setAttribute(std::string,std::string);
};




class AppendCharset : public Appender {
	std::vector<size_t> indexes;
	std::string         symbolList;
protected:
	std::string getBlockValue();
	void doAdvance();
	void increaseCurrentLength();

public:
	AppendCharset() {
		this->setMinLength(0);
		this->setMaxLength(2);
		this->indexes.clear();
		this->symbolList="";
	}
	void rewindBlock();
	void setAttribute(std::string,std::string);
};




class AppenderFactory {
public:
  static Appender *create(std::string);
};



#endif // __APPENDERS_H_
