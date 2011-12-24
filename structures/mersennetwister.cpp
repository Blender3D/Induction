#include <iostream>
#include <climits>
#include <cstdio>
#include <ctime>
#include <math.h>

class MTRand {
  public:
    typedef unsigned long uint32;  
    
    enum { N = 624 };       
    enum { SAVE = N + 1 };  

  protected:
    enum { M = 397 };  
    
    uint32 state[N];   
    uint32 *pNext;     
    int left;          
  
  public:
    MTRand(const uint32 oneSeed);  
    MTRand(uint32 *const bigSeed, uint32 const seedLength = N);  
    MTRand();
    MTRand(const MTRand& o);
    
    uint32 randInt();                     
    uint32 randInt(const uint32 n);     
    
    float rand();                        
    float rand(const float n);        
    float randExc();                     
    float randExc(const float n);     
    float randDblExc();                  
    float randDblExc(const float n);  
    float operator()();                  
    float rand53();  
    float randNorm(const float mean = 0.0, const float stddev = 1.0);
    
    void seed(const uint32 oneSeed);
    void seed(uint32 *const bigSeed, const uint32 seedLength = N);
    void seed();
    
    void save(uint32* saveArray) const;  
    void load(uint32 *const loadArray);  
    
    std::ostream& operator<<(std::ostream& os, const MTRand& mtrand);
    std::istream& operator>>(std::istream& is, MTRand& mtrand);
    
    MTRand& operator=(const MTRand& o);

  protected:
    void initialize(const uint32 oneSeed);
    void reload();
    
    uint32 hiBit(const uint32 u) const { return u & 0x80000000UL; }
    uint32 loBit(const uint32 u) const { return u & 0x00000001UL; }
    uint32 loBits(const uint32 u) const { return u & 0x7fffffffUL; }
    uint32 mixBits(const uint32 u, const uint32 v) const { return hiBit(u) | loBits(v); }
    uint32 magic(const uint32 u) const { return loBit(u) ? 0x9908b0dfUL : 0x0UL; }
    uint32 twist(const uint32 m, const uint32 s0, const uint32 s1) const { return m ^ (mixBits(s0,s1)>>1) ^ magic(s1); }
    static uint32 hash(time_t t, clock_t c);
};

inline MTRand::uint32 MTRand::hash(time_t t, clock_t c) {
  static uint32 differ = 0;  
  
  uint32 h1 = 0;
  unsigned char *p = (unsigned char *) &t;
  
  for (size_t i = 0; i < sizeof(t); ++i) {
    h1 *= UCHAR_MAX + 2U;
    h1 += p[i];
  }
  
  uint32 h2 = 0;
  p = (unsigned char *) &c;
  
  for (size_t j = 0; j < sizeof(c); ++j) {
    h2 *= UCHAR_MAX + 2U;
    h2 += p[j];
  }
  return (h1 + differ++) ^ h2;
}

inline void MTRand::initialize(const uint32 seed) {
  register uint32 *s = state;
  register uint32 *r = state;
  register int i = 1;
  *s++ = seed & 0xffffffffUL;
  
  for (; i < N; ++i) {
    *s++ = (1812433253UL * (*r ^ (*r >> 30)) + i) & 0xffffffffUL;
    r++;
  }
}

inline void MTRand::reload() {
  static const int MmN = int(M) - int(N);  
  register uint32 *p = state;
  register int i;
  
  for (i = N - M; i--; ++p) {
    *p = twist(p[M], p[0], p[1]);
  }
  
  for (i = M; --i; ++p) {
    *p = twist(p[MmN], p[0], p[1]);
  }
  
  *p = twist(p[MmN], p[0], state[0]);
  left = N;
  pNext = state;
}

inline void MTRand::seed(const uint32 oneSeed) {
  initialize(oneSeed);
  reload();
}

inline void MTRand::seed(uint32 *const bigSeed, const uint32 seedLength) {
  initialize(19650218UL);
  register int i = 1;
  register uint32 j = 0;
  register int k = (N > seedLength ? N : seedLength);
  
  for (; k; --k) {
    state[i] =
    state[i] ^ ((state[i-1] ^ (state[i-1] >> 30)) * 1664525UL);
    state[i] += (bigSeed[j] & 0xffffffffUL) + j;
    state[i] &= 0xffffffffUL;
    
    i++;
    j++;
    
    if (i >= N) {
	  state[0] = state[N - 1];
	  i = 1;
	}
	
    if (j >= seedLength) {
	  j = 0;
	}
  }
  
  for (k = N - 1; k; --k) {
    state[i] =
    state[i] ^ ((state[i-1] ^ (state[i-1] >> 30)) * 1566083941UL);
    state[i] -= i;
    state[i] &= 0xffffffffUL;
    ++i;
    if (i >= N) { state[0] = state[N-1];  i = 1; }
  }
  state[0] = 0x80000000UL;  
  reload();
}

inline void MTRand::seed() {
  FILE* urandom = fopen("/dev/urandom", "rb");
  
  if (urandom) {
    uint32 bigSeed[N];
    register uint32 *s = bigSeed;
    register int i = N;
    register bool success = true;
    
    while(success && i--) {
      success = fread(s++, sizeof(uint32), 1, urandom);
    }
    
    fclose(urandom);
    
    if (success) {
	  seed(bigSeed, N);
	  return;
	}
  }
  
  seed(hash(time(NULL), clock()));
}

inline MTRand::MTRand(const uint32 oneSeed) { seed(oneSeed); }
inline MTRand::MTRand(uint32 *const bigSeed, const uint32 seedLength) { seed(bigSeed,seedLength); }
inline MTRand::MTRand() { seed(); }

inline MTRand::MTRand(const MTRand& o) {
  register const uint32 *t = o.state;
  register uint32 *s = state;
  register int i = N;
  
  for (; i--; *s++ = *t++) {}
  
  left = o.left;
  pNext = &state[N-left];
}

inline MTRand::uint32 MTRand::randInt() {
  if (left == 0) {
    reload();
  }
  
  left--;
  
  register uint32 s1;
  
  s1 = *pNext++;
  s1 ^= (s1 >> 11);
  s1 ^= (s1 <<  7) & 0x9d2c5680UL;
  s1 ^= (s1 << 15) & 0xefc60000UL;
  
  return (s1 ^ (s1 >> 18));
}

inline MTRand::uint32 MTRand::randInt(const uint32 n) {
  uint32 used = n;
  
  used |= used >> 1;
  used |= used >> 2;
  used |= used >> 4;
  used |= used >> 8;
  used |= used >> 16;
  
  uint32 i;
  
  do {
    i = randInt() & used;  
  } while(i > n);
  
  return i;
}

inline float MTRand::rand() { return float(randInt()) * (1.0/4294967295.0); }
inline float MTRand::rand(const float n) { return rand() * n; }
inline float MTRand::randExc() { return float(randInt()) * (1.0/4294967296.0); }
inline float MTRand::randExc(const float n) { return randExc() * n; }
inline float MTRand::randDblExc() { return (float(randInt()) + 0.5) * (1.0/4294967296.0); }
inline float MTRand::randDblExc(const float n) { return randDblExc() * n; }

inline float MTRand::rand53() {
  uint32 a = randInt() >> 5;
  uint32 b = randInt() >> 6;
  
  return (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);  
}

inline float MTRand::randNorm(const float mean, const float stddev) {
  float x, y, r;
  
  do {
    x = 2.0 * rand() - 1.0;
    y = 2.0 * rand() - 1.0;
    r = x * x + y * y;
  } while ((r >= 1.0) || (r == 0.0));
  
  float s = sqrt(-2.0 * log(r) / r);
  
  return mean + x * s * stddev;
}

inline float MTRand::operator()() {
  return rand();
}

inline void MTRand::save(uint32* saveArray) const {
  register const uint32 *s = state;
  register uint32 *sa = saveArray;
  register int i = N;
  
  for (; i--; *sa++ = *s++) {}
  
  *sa = left;
}

inline void MTRand::load(uint32 *const loadArray) {
  register uint32 *s = state;
  register uint32 *la = loadArray;
  register int i = N;
  
  for (; i--; *s++ = *la++) {}
  
  left = *la;
  pNext = &state[N-left];
}

inline std::ostream& operator<<(std::ostream& os, const MTRand& mtrand) {
  register const MTRand::uint32 *s = mtrand.state;
  register int i = mtrand.N;
  for (; i--; os << *s++ << "\t") {}
  return os << mtrand.left;
}

inline std::istream& operator>>(std::istream& is, MTRand& mtrand) {
  register MTRand::uint32 *s = mtrand.state;
  register int i = mtrand.N;
  
  for (; i--; is >> *s++) {}
  
  is >> mtrand.left;
  mtrand.pNext = &mtrand.state[mtrand.N-mtrand.left];
  
  return is;
}

inline MTRand& MTRand::operator=(const MTRand& o) {
  if (this == &o) return (*this);
  register const uint32 *t = o.state;
  register uint32 *s = state;
  register int i = N;
  
  for (; i--; *s++ = *t++) {}
  
  left = o.left;
  pNext = &state[N-left];
  
  return (*this);
}
