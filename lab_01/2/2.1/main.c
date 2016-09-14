#include "util.h"
#include "io.h"
#include "algorithm.h"

void main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  int g = unresolved("reference");
  maxx(a, b);
  logDebug('!');
}
