#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>
#include <cassert>

#include <divsufsort.h>

#include "cpi2.hpp"

namespace cpm {

  /**
   * Search for the character c in the string T with "offset".
   * This function is based on the libdivsufsort function sa_simplesearch().
   * For a suffix SA[i] = j, the original function compares the character c
   * to T[j].  This modified version instead compares c to T[j + offset].
   * Thus, given T and the suffixes of T that have a pattern P as a prefix,
   * this function can be used to find the subset of those rows that have
   * pattern Pc as a prefix in O(log n) time.  (See Lemma 1 of Huynh et al
   * - "Approximate string matching using compressed suffix arrays" (2006).)
   * @param T[0..Tsize-1] The input string.
   * @param Tsize The length of the given string.
   * @param SA[0..SAsize-1] The input suffix array.
   * @param SAsize The length of the given suffix array.
   * @param c The input character.
   * @param idx The output index.
   * @param offset Offset from the beginning of each suffix.
   * @return The count of matches if no error occurred, -1 otherwise.
   */
  saidx_t sa_simplesearch_offset(const sauchar_t *T, saidx_t Tsize,
                                 const saidx_t *SA, saidx_t SAsize,
                                 saint_t c, saidx_t *idx,
                                 saidx_t offset) {
    saidx_t size, lsize, rsize, half;
    saidx_t i, j, k, p;
    saint_t r;

    if(idx != NULL) { *idx = -1; }
    if((T == NULL) || (SA == NULL) || (Tsize < 0) || (SAsize < 0)) { return -1; }
    if((Tsize == 0) || (SAsize == 0)) { return 0; }

    for(i = j = k = 0, size = SAsize, half = size >> 1;
        0 < size;
        size = half, half >>= 1) {
      p = SA[i + half] + offset;
      r = (p < Tsize) ? T[p] - c : -1;
      if(r < 0) {
        i += half + 1;
        half -= (size & 1) ^ 1;
      } else if(r == 0) {
        lsize = half, j = i, rsize = size - half - 1, k = i + half + 1;

        /* left part */
        for(half = lsize >> 1;
            0 < lsize;
            lsize = half, half >>= 1) {
          p = SA[j + half] + offset;
          r = (p < Tsize) ? T[p] - c : -1;
          if(r < 0) {
            j += half + 1;
            half -= (lsize & 1) ^ 1;
          }
        }

        /* right part */
        for(half = rsize >> 1;
            0 < rsize;
            rsize = half, half >>= 1) {
          p = SA[k + half] + offset;
          r = (p < Tsize) ? T[p] - c : -1;
          if(r <= 0) {
            k += half + 1;
            half -= (rsize & 1) ^ 1;
          }
        }

        break;
      }
    }

    if(idx != NULL) { *idx = (0 < (k - j)) ? j : i; }
    return k - j;
  }

  /**
   * Given interval [s1, e1] for P_1[0..m1 - 1] and interval [s2, e2] for P_2, find interval for P_1P_2.
   * (See Lemma 2 of Huynh et al - "Approximate string matching using compressed suffix arrays" (2006).)
   * @param sa[0..n-1] The input suffix array.
   * @param inv_sa[0..n-1] The input inverse suffix array.
   * @param n Length of sa and inv_sa.
   * @param s1 Start of the interval for P_1.
   * @param e1 End of the interval for P_1.
   * @param m1 Length of P_1.
   * @param s2 Start of the interval for P_2.
   * @param e2 End of the interval for P_2.
   * @param idx The output index.
   * @return The count of matches if no error occurred, -1 otherwise.
   */
  int sa_search_concat(const int* sa,
                       const int* inv_sa,
                       const int n,
                       const int s1, const int e1, const int m1,
                       const int s2, const int e2,
                       int* idx) {
    int size = 0, lsize = 0, rsize = 0, half = 0;
    int i = 0, j = 0, k = 0;
    for (i = s1, size = e1 - s1 + 1, half = size >> 1;
         0 < size;
         size = half, half >>= 1) {
      int p = inv_sa[sa[i + half] + m1];
      if (p < s2) {
        i += half + 1;
        half -= (size & 1) ^ 1;
      } 
      else if (s2 <= p && p <= e2) {
        lsize = half, j = i, rsize = size - half - 1, k = i + half + 1;;
        // left part
        for (half = lsize >> 1;
             0 < lsize;
             lsize = half, half >>= 1) {
          p = inv_sa[sa[j + half] + m1];
          if (p < s2) {
            j += half + 1;
            half -= (lsize & 1) ^ 1;
          }
        }
        // right part
        for (half = rsize >> 1;
             0 < rsize;
             rsize = half, half >>= 1) {
          p = inv_sa[sa[k + half] + m1];
          if (s2 <= p && p <= e2) {
            k += half + 1;
            half -= (rsize & 1) ^ 1;
          }
        }
        break;
      }
    }
    if (idx != NULL) {
      *idx = (0 < (k - j)) ? j : i;
    }
    return k - j;
  }

  Cpi2::Cpi2(std::string text) {
    assert(sizeof(char) == sizeof(sauchar_t) && sizeof(int) == sizeof(saidx_t));
    n_ = text.size(); 
    text_ = (char*)malloc((n_ + 1) * sizeof(unsigned char));
    assert(text_ != NULL);
    strncpy(text_, text.c_str(), n_ + 1);

    sa_ = (int*)malloc(n_ * sizeof(int));
    inv_sa_ = (int*)malloc(n_ * sizeof(int));
    
    divsufsort((sauchar_t*)text_, sa_, n_); // build suffix array
    for (int i = 0; i < n_; i++) { // build inverse suffix array:
      inv_sa_[sa_[i]] = i;
    }
  }
  
  Cpi2::~Cpi2() {
    free(text_);
    free(sa_);
    free(inv_sa_);
  }

  // Finds all occurrences of a circular pattern.
  std::set<int> Cpi2::cmatch(std::string pattern) {
    const int m = pattern.size();
    int int_left = 0, int_len = 0; // the start and length of an interval
    int prev_int_left = 0;

    // SA intervals for all prefixes of P
    std::vector< std::pair<int, int> > pref;
    pref.reserve(m);
    int_left = 0;
    int_len = n_;
    for (int i = 0; i < m; i++) {
      prev_int_left = int_left;
      int_len = sa_simplesearch_offset((sauchar_t*)text_, n_, sa_ + int_left, int_len, pattern[i], &int_left, i);
      int_left += prev_int_left;
      pref.push_back(std::make_pair(int_left, int_left + int_len - 1));
    }
    
    // SA intervals for all suffixes of P
    std::vector< std::pair<int, int> > suff(m);
    std::map<char, std::pair<int, int> > char_ints;
    int_len = sa_simplesearch((sauchar_t*)text_, n_, sa_, n_, pattern[m - 1], &int_left);
    suff[m - 1] = std::make_pair(int_left, int_left + int_len - 1);
    char_ints[pattern[m - 1]] = suff.back();
    for (int i = m - 2; i >= 0; i--) {
      char c = pattern[i];
      std::map<char, std::pair<int, int> >::iterator iter = char_ints.find(c);
      if (iter == char_ints.end()) {
        int_len = sa_simplesearch((sauchar_t*)text_, n_, sa_, n_, c, &int_left);
        char_ints[c] = std::make_pair(int_left, int_left + int_len - 1);
        iter = char_ints.find(c);
      }
      int_len = sa_search_concat(sa_, inv_sa_, n_,
                                 iter->second.first, iter->second.second, 1,
                                 suff[i + 1].first, suff[i + 1].second,
                                 &int_left);
      suff[i] = std::make_pair(int_left, int_left + int_len - 1);
    }
    
    // SA intervals for all rotations of P
    std::set<int> occ;
    for (int i = pref[m - 1].first; i <= pref[m - 1].second; i++) {
      occ.insert(sa_[i]);
    }
    for (int i = 1; i < m; i++) {
      int_len = sa_search_concat(sa_, inv_sa_, n_,
                                 suff[i].first, suff[i].second, m - i,
                                 pref[(i + m - 1) % m].first, pref[(i + m - 1) % m].second,
                                 &int_left);
      for (int j = int_left; j <= int_left + int_len - 1; j++) {
        occ.insert(sa_[j]);
      }
    }

    return occ;
  }

};
