/****************************************************************************************************************************
  cdecode.c - c source to a base64 decoding algorithm implementation

  This is part of the libb64 project, and has been placed in the public domain.
  For details, see http://sourceforge.net/projects/libb64

  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
       
  Version: 1.1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries
 *****************************************************************************************************************************/

#include "cdecode.h"

int base64_decode_value(char value_in) {
  static const char decoding[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1, -1,
                                   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                                   25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
                                   42, 43, 44, 45, 46, 47, 48, 49, 50, 51
                                 };
                                 
  static const char decoding_size = sizeof(decoding);
  value_in -= 43;
  if (value_in < 0 || value_in > decoding_size) return -1;
  return decoding[(int)value_in];
}

void base64_init_decodestate(base64_decodestate* state_in) {
  state_in->step = step_a;
  state_in->plainchar = 0;
}

int base64_decode_block(const char* code_in, const int length_in, char* plaintext_out, base64_decodestate* state_in) {
  const char* codechar = code_in;
  char* plainchar = plaintext_out;
  char fragment;

  *plainchar = state_in->plainchar;

  switch (state_in->step) {
      while (1) {
      case step_a:
        do {
          if (codechar == code_in + length_in) {
            state_in->step = step_a;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (char)base64_decode_value(*codechar++);
        } while (fragment < 0);
        *plainchar    = (fragment & 0x03f) << 2;
      case step_b:
        do {
          if (codechar == code_in + length_in) {
            state_in->step = step_b;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (char)base64_decode_value(*codechar++);
        } while (fragment < 0);
        *plainchar++ |= (fragment & 0x030) >> 4;
        *plainchar    = (fragment & 0x00f) << 4;
      case step_c:
        do {
          if (codechar == code_in + length_in) {
            state_in->step = step_c;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (char)base64_decode_value(*codechar++);
        } while (fragment < 0);
        *plainchar++ |= (fragment & 0x03c) >> 2;
        *plainchar    = (fragment & 0x003) << 6;
      case step_d:
        do {
          if (codechar == code_in + length_in) {
            state_in->step = step_d;
            state_in->plainchar = *plainchar;
            return plainchar - plaintext_out;
          }
          fragment = (char)base64_decode_value(*codechar++);
        } while (fragment < 0);
        *plainchar++   |= (fragment & 0x03f);
      }
  }
  /* control should not reach here */
  return plainchar - plaintext_out;
}

int base64_decode_chars(const char* code_in, const int length_in, char* plaintext_out) {
  base64_decodestate _state;
  base64_init_decodestate(&_state);
  int len = base64_decode_block(code_in, length_in, plaintext_out, &_state);
  if (len > 0) plaintext_out[len] = 0;
  return len;
}
