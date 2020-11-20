#include "chainsaws.hpp"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main (int argCount, char **argVec) {

  if (argCount < 2)
	{
	  cerr << "Need an argument" << endl;
	  return 1;
	}

  XMLDocument document;

  if (document.LoadFile(argVec[1]))
	{
	  cerr << argVec[1] << " no se pudo cargar... =/\n";
	  return 1;
	}

  XMLElement *root = document.RootElement();
  const char *name = root->Name();

  if (string(name) != "PASS")
	{
	  cerr << "The XML that I understand starts with a <PASS> tag."
		   << endl;
	  return 1;
	}

  if (root->NoChildren())
	{
	  cerr << "No rules were found." << endl;
	  return 1;
	}

  XMLElement *tag = root->FirstChildElement();

  Chainsaw *jason = NULL;

  while (tag)
	{
	  Chainsaw *saw;
	  saw = ChainsawFactory::create(tag->Name());

	  const XMLAttribute *attribute = tag->FirstAttribute();

	  while (attribute)
		{
		  saw->setAttribute(attribute->Name(), attribute->Value());
		  attribute = attribute->Next();
		}

	  if (!jason) {jason = saw;}
	  else        {jason->addChain( saw );}

	  tag = tag->NextSiblingElement();
	}

  if (!jason)
	{
	  cerr << "Something went wrong and Jason is not here..." << endl;
	  return 1;
	}

  string value = "";

  try
	{
		cerr << "Total number will be: "
		     <<	jason->size() << endl;

		while (1)
		{
			value = jason->nextChainValue();
			cout << value << endl;
		}
	}
  catch (ChainsawExcept e)
	{
	  if (e.type != ChainsawExcept::NoMore)
		{
		  cerr << e.describe() << endl;
		  return 1;
		}
	}

  return 0;
}

