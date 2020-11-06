#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main (void)
{

	XMLDocument document;
# define fileName "data/004-passml.xml"

	if (document.LoadFile( fileName )) {
	  cerr << fileName << " no se pudo cargar =/\n";
	}

	else {

		XMLElement *pass = document.RootElement();
		const char *name = pass->Name();

		cout << "root:" << name << "\n";

		if (pass->NoChildren()) {
			cerr << "Empty PASS tag, nothing to do.\n";
		}

		else {
			XMLElement *tag = pass->FirstChildElement();
			while (tag) {
				cout << "tag:" << tag->Name() << "\n";
				tag = tag->NextSiblingElement();
			}
		}

	}

	return 0;
}
