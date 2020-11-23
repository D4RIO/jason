#ifndef __APPENDERS_H_
#define __APPENDERS_H_

#include <iostream>
#include <fstream>
#include <vector>


class ChainsawExcept {
public:
	ChainsawExcept (const int t);
	ChainsawExcept (const int t, const char *i);

	int         type;
	std::string  info;
	const char * describe ();

	static const int OK               = 0;
	static const int NoMore           = 1;
	static const int UnknownType      = 2;
	static const int UnknownAttribute = 3;
	static const int IOFailure        = 4;
	static const int UnknownError     = 5;
};





class Chainsaw {
	Chainsaw* _nextChainsaw;
	int       _minLength;
	int       _maxLength;
	int       _currentLength;
	
protected:
	bool    firstRun;

	virtual std::string getBlockValue () = 0;
	virtual void doAdvance () = 0; // can throw ChainsawExcept (::NoMore)
	virtual void increaseCurrentLength () {_currentLength++;}
	int getCurrentLength () {return _currentLength;}
	void resetCurrentLength () {_currentLength = 0;}

public:
	Chainsaw ();

	Chainsaw *getNextChainsaw () { return _nextChainsaw;}
	int getMinLength () {return _minLength;}
	int getMaxLength () {return _maxLength;}
	virtual std::string getChainDescription () = 0;

	void setMinLength (int yourMin) {_minLength = yourMin;}
	void setMaxLength (int yourMax) {_maxLength = yourMax;}
	virtual void setAttribute (std::string, std::string) = 0;

	void addChain (Chainsaw *);
	std::string nextChainValue ();
	virtual void rewindBlock ();
	virtual unsigned long long size () = 0;
};





class ChainsawNumber : public Chainsaw {
	long int _number;

protected:
	std::string getBlockValue ();
	void doAdvance ();
	void increaseCurrentLength ();

public:
	ChainsawNumber ();

	void rewindBlock ();
	void setAttribute (std::string,std::string);
	std::string getChainDescription ();
	unsigned long long size ();
};





class ChainsawCharset : public Chainsaw {
	std::vector<size_t> indexes;
	std::string         symbolList;
protected:
	std::string getBlockValue ();
	void doAdvance ();
	void increaseCurrentLength ();

public:
	ChainsawCharset ();
	void rewindBlock ();
	void setAttribute (std::string,std::string);
	std::string getChainDescription ();
	unsigned long long size ();
};





class ChainsawDictionary : public Chainsaw {
	std::ifstream input;
	std::string   src;
	std::string   line;
	size_t       number_of_lines;

protected:
	std::string getBlockValue ();
	void doAdvance ();
	void increaseCurrentLength ();

public:
	ChainsawDictionary ();
 	void rewindBlock ();
	void setAttribute (std::string,std::string);
	std::string getChainDescription ();
	unsigned long long size ();
};





class ChainsawFactory {
public:
  static Chainsaw *create (std::string);
};





#endif // __APPENDERS_H_
