#include "./passgen.hpp"

using namespace std;

int main(void)
{
  PassGen generator;

  try {
    generator.loadConfigFile("data/002-testconfig");
  }
  catch (...) {
    cerr << "Some unexpected error happened trying to read data/002-testconfig.\n";
  }

  try {
    cout << generator.getCharSet("common-symbols") << "\n";
  }
  catch (...) {
    cerr << "Some unexpected error happened trying to read common-symbols.\n";
  }

  return 0;
}
