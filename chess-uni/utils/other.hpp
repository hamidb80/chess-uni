#pragma once

#include <bitset>
#include <random>
using namespace std;

template <int LEN>
inline string binaryRepr(int n) {
	bitset<LEN> bit_repr(n);
	return bit_repr.to_string();
}

inline int freakin_random_number() {
	return rand();
}
