#ifndef __APPENDERS_H_
#define __APPENDERS_H_

#include <iostream>


class AppenderExcept {
public:
  AppenderExcept(const int t) {this->type = t;}
  int       type;
  static const int NoMore = 1;
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
	int getCurrentLength() {return _currentLength;}
	void increaseCurrentDigits() {_currentLength++;}
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
};



class AppendNumber : public Appender {
  long int _number;

protected:
  std::string getBlockValue();
  void doAdvance();
  void increaseCurrentDigits() {
	Appender::increaseCurrentDigits();
	_number = 0L;
  }

public:
  AppendNumber() {
	_number = -1L; // so that next starts from 0
	this->setMinLength(0);
	this->setMaxLength(2);
  }
  void rewindBlock();
};



class AppenderFactory {
public:
  static Appender *create(std::string);
};



#endif // __APPENDERS_H_
