#include "./passgen.hpp"

using namespace std;

int main(void)
{
  PassGen generator;

  try {
    generator.loadConfigFile("data/003-testconfig");
  }
  catch (...) {
    cerr << "Some unexpected error happened trying to read data/003-testconfig.\n";
  }

  return 0;
}
