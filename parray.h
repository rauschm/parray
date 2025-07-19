/*******************************************************************************
  P A R R A Y . H

  Ein "normales" Array könnte man als Potenz-Array bezeichnen, denn der
  Speicherbedarf ergibt sich aus dem Produkt der Größen der einzelnen
  Dimensionen, und wenn diese alle gleich sind, als Potenz dieser Größe K
  hoch der Anzahl der Dimensionen N: K^N. Bei N = 3 und K = 8 sind das
  8³ = 512 Speicherplätze.

  Ein Parray<N,K> (Pascalsches Array) dagegen benötigt nur (N+K-1)! / N!(K-1)!
  (= N+K-1 über K-1) Speicherplätze. Analog zum obigen Beispiel benötigt ein
  Parray<3,8> also (3+8-1)! / 3! / 7! = 10*9*8 / (3*2) = 120 Speicherplätze,
  also weniger als ein Viertel.

  Mit zunehmendem N wird die Einsparung immer größer. Bei <20,10> braucht man
  für die gigantische Menge eines Potenz-Arrays nur noch ca. 10 Millionen
  Einträge, was locker in den Hauptspeicher eines Computers passt.

  Erkauft wird das dadurch, dass die Indices eines Parray nicht beliebig
  gewählt werden dürfen. Es gilt folgende Einschänkung: Die Summe der
  (nur positiven) Indices muss immer N ergeben.

  Das ist beispielsweise gegeben, wenn man bei einer N-stelligen Zahl die
  Vorkommen der K verschiedenen Ziffern zählt.

  Das Parray kommt auch aus der Kombinatorik. Es wird dort eingesetzt, um
  theorethische Überlegungen praktisch schnell überprüfen zu können.
*******************************************************************************/
#pragma once

//------------------------------------------------------------------------------
template<unsigned int N, unsigned int K>
class Pindex {
//------------------------------------------------------------------------------
public:
  Pindex(unsigned int i = 0) {
    vectorize(i);
  }

  Pindex& operator = (unsigned int i) {
    vectorize(i);
    return *this;
  }

  operator unsigned int() {
    return scalarize();
  }

  unsigned int operator [] (unsigned int k) {
    return ix[k];
  }
protected:
  unsigned int& operator() (unsigned int k) {
    return ix[k];
  }

  void inc(unsigned int k, unsigned int n) {
    ix[k] -= 1;
    ix[k + 1] += 1;
    if (n > 0) {
      ix[K - 1] -= n;
      ix[0] += n;
    }
  }

  void dec(unsigned int k, unsigned int n) {
    ix[k] -= 1;
    ix[k - 1] += 1;
    if (n > 0) {
      ix[0] -= n;
      ix[K - 1] += n;
    }
  }
private:
  static constexpr unsigned int binom(unsigned int n, unsigned int k) noexcept {
    return k > n ? 0 : k == 0 ? 1 : binom(n - 1, k - 1) * n / k;
  }

  typedef struct { unsigned int pv[N + 1][K]; } PV;

  static constexpr auto init_pv() {
    PV pv = {};
    for (int n = N; n >= 0; --n) {
      for (int k = K - 1; k >= 0; --k) {
        pv.pv[n][k] = (n == N)                   ? 0
                    : (n == N - 1 || k == K - 1) ? 1
                    :                              pv.pv[n + 1][k] + pv.pv[n][k + 1];
      }
    }
    return pv;
  }

  unsigned int scalarize() {
    unsigned int i = 0;
    for (unsigned int n = 0, k = 0; n + ix[k] < N; ++k) {
      int i0 = i;
      i += pv.pv[n += ix[k]][k];
    }
    return i;
  }

  void vectorize(unsigned int i) {
    if (i >= binom(N + K - 1, K - 1)) {
      throw(0);
    }
    unsigned int n = 0;
    unsigned int k = 0;
    do {
      unsigned int h = n;
      while (i < pv.pv[n][k]) {
        n += 1;
      }
      ix[k] = n - h;
    } while ((i -= pv.pv[n][k++]) > 0);
    ix[k] = N - n;
    while (++k < K) {
      ix[k] = 0;
    }
  }

  static constexpr PV pv = init_pv();
  unsigned int        ix[K] = {N, 0};
};

template<unsigned int N, unsigned int K>
constexpr typename Pindex<N, K>::PV Pindex<N, K>::pv;

template<unsigned int N, unsigned int K>
inline std::ostream& operator << (std::ostream& os, Pindex<N, K>& i) {
  unsigned int k = 0;
  os << '[';
  do {
    os << i[k] << (k < K - 1 ? ',' : ']');
  } while (++k < K);
  return os;
}

//------------------------------------------------------------------------------
template <unsigned int N, unsigned int K>
class Parray {
//------------------------------------------------------------------------------
public:
  unsigned int& operator [] (Pindex<N, K>& pi) { return pa[pi]; }
  unsigned int& operator [] (unsigned int i)   { return pa[i]; }
  unsigned int* begin() { return &pa[0]; }
  unsigned int* end()   { return &pa[size()]; }
  static constexpr unsigned int size() { return sizeof(pa) / sizeof(pa[0]); }
 private:
  static constexpr unsigned int binom(unsigned int n, unsigned int k) noexcept {
    return k > n ? 0 : k == 0 ? 1 : binom(n - 1, k - 1) * n / k;
  }

  unsigned int pa[binom(N + K - 1, K - 1)] = {0};
};
