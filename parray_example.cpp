/*******************************************************************************
  P A R R A Y _ E X A M P L E . C P P

  Dieses Programm zeigt die Fähigkeiten der Klassen Parray und Pindex.

  Auf wie viele und welche untwerschiedliche Weisen können K Ziffern auf N
  Stellen verteilt werden?
*******************************************************************************/
#include <iostream>
#include "parray.h"

constexpr unsigned int STELLEN = 4;
constexpr unsigned int ZIFFERN = 8;


class Zahl : public Pindex <STELLEN, ZIFFERN> {
public:
  bool         increment();
  unsigned int operator [] (unsigned int n);
private:
  unsigned int ziffern[STELLEN + 1] = {0};
};
std::ostream& operator << (std::ostream& os, Zahl& z);


int main() {
  Parray<STELLEN, ZIFFERN> groups;
  Zahl                     z;

  // zählen
  do {
     groups[z] += 1;
  } while (z.increment());
  
  // ausgeben
  unsigned int i = 0;
  for (auto count : groups) {
    Pindex <STELLEN, ZIFFERN> pi(i);
    std::cout << i++ <<" : " << pi << " = " << count << std::endl;
  }

  return 0;
}


bool Zahl::increment() {
  unsigned int n = 0;
  while (ziffern[n] == ZIFFERN - 1) { n += 1; }
  if (n == STELLEN) { return false; }
  inc(ziffern[n]++, n);
  while (n > 0) { ziffern[--n] = 0; }
  return true;
}

unsigned int Zahl::operator [] (unsigned int n) {
  return ziffern[n];
}

std::ostream& operator << (std::ostream& os, Zahl& z) {
  unsigned int n = STELLEN;
  do {
    os << z[--n];
  } while (n > 0);
  os << " :";
  unsigned int k = 0;
  do {
    os << ' ' << z.Pindex::operator[](k++);
  } while (k < ZIFFERN);
  return os;
}

