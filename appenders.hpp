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
  int _min;
  int _max;
  int _current;

protected:
  virtual std::string getCurrent() = 0;
  virtual void doAdvance() = 0; // can throw AppenderExcept (::NoMore)
  int getCurrentDigits() {return _current;}
  void increaseCurrentDigits() {_current++;}

public:
  Appender() {
	_nextAppender = NULL;
	_current = 0;
  }
  ~Appender() {}
  Appender *getNextAppender() {
	return this->_nextAppender;
  }
  int getMin() {return _min;}
  int getMax() {return _max;}
  void setMin(int yourMin) {_min = yourMin;_current = _min;}
  void setMax(int yourMax) {_max = yourMax;}
  std::string nextValue();
  virtual void rewind() = 0;
};



class AppendNumber : public Appender {
  long int _number;

protected:
  std::string getCurrent();
  void doAdvance();
  void increaseCurrentDigits() {
	Appender::increaseCurrentDigits();
	_number = 0L;
  }

public:
  AppendNumber() {
	_number = -1L; // so that next starts from 0
	this->setMin(0);
	this->setMax(2);
  }
  void rewind();
};



class AppenderFactory {
public:
  static Appender *create(std::string);
};



#endif // __APPENDERS_H_
