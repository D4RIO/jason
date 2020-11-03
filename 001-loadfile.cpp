#include "./passgen.hpp"

using namespace std;

int main(void)
{
  PassGen generator;

  generator.loadFile("lists/test-input-001");

  cout << "##### LOADED TESTFILE #####\n";

  generator.print();
  generator.removeDuplicates();

  cout << "#### REMOVED DUPLICATES ###\n";

  generator.print();

  return 0;
}
