
#include <fstream>
#include <string>
//using namespace std;

#ifndef BACKEND_MD5_H
#define BACKEND_MD5_H

class MD5 {

public:
// methods for controlled operation:
  MD5              ();  // simple initializer
  void  update     (unsigned char *input, unsigned int input_length);
  void  finalize   ();

// constructors for special circumstances.  All these constructors finalize
// the MD5 context.
  MD5              (const char *string,unsigned int string_length); // digest string, finalize
  
// methods to acquire finalized result
  unsigned char    *raw_digest ();  // digest as a 16-byte binary array
  std::string            hex_digest ();  // digest as a 33-byte ascii-hex string


//private:

// first, some types:
  typedef unsigned       int uint4; // assumes integer is 4 words long
  typedef unsigned short int uint2; // assumes short integer is 2 words long
  typedef unsigned      char uint1; // assumes char is 1 word long

// next, the private data:
  uint4 state[4];
  uint4 count[2];     // number of *bits*, mod 2^64
  uint1 buffer[64];   // input buffer
  uint1 digest[16];
  uint1 finalized;

// last, the private methods, mostly static:
  void init             ();               // called by all constructors
  void transform        (uint1 *buffer);  // does the real update work.  Note
                                          // that length is implied to be 64.

  static void encode    (uint1 *dest, uint4 *src, uint4 length);
  static void decode    (uint4 *dest, uint1 *src, uint4 length);
  static void memcpy    (uint1 *dest, uint1 *src, uint4 length);
  static void memset    (uint1 *start, uint1 val, uint4 length);

  static inline uint4  rotate_left (uint4 x, uint4 n);
  static inline uint4  F           (uint4 x, uint4 y, uint4 z);
  static inline uint4  G           (uint4 x, uint4 y, uint4 z);
  static inline uint4  H           (uint4 x, uint4 y, uint4 z);
  static inline uint4  I           (uint4 x, uint4 y, uint4 z);
  static inline void   FF  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);
  static inline void   GG  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);
  static inline void   HH  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);
  static inline void   II  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
			    uint4 s, uint4 ac);

};

//returns md5 for a given file
std::string getMD5(const char* str,unsigned int str_len);

#endif //BACKEND_MD5_H


