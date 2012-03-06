/*
  Copyright (c) 2012, Matthias Schiffer <mschiffer@universe-factory.net>
  Partly based on QuickTun Copyright (c) 2010, Ivo Smits <Ivo@UCIS.nl>.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef _FASTD_PACKET_H_
#define _FASTD_PACKET_H_

#include <asm/byteorder.h>
#include <stdint.h>


typedef enum _fastd_packet_type {
	PACKET_UNKNOWN = 0,
	PACKET_HANDSHAKE,
	PACKET_DATA,
} fastd_packet_type;

typedef enum _fastd_reply_code {
	REPLY_SUCCESS = 0,
} fastd_reply_code;


#if defined(__LITTLE_ENDIAN_BITFIELD)
#define FASTD_PACKET_COMMON \
	unsigned req_id : 6; \
	unsigned cp     : 1; \
	unsigned reply  : 1; \
	uint8_t rsv
#elif defined (__BIG_ENDIAN_BITFIELD)
#define FASTD_PACKET_COMMON \
	unsigned reply  : 1; \
	unsigned cp     : 1; \
	unsigned req_id : 6; \
	uint8_t rsv
#else
#error "Bitfield endianess not defined."
#endif


typedef struct __attribute__ ((__packed__)) _fastd_packet_any {
	FASTD_PACKET_COMMON;
} fastd_packet_any;

typedef struct __attribute__ ((__packed__)) _fastd_packet_request {
	FASTD_PACKET_COMMON;
	uint8_t flags;
	uint8_t proto;
	uint8_t method_len;
	char    method_name[];
} fastd_packet_request;

typedef struct __attribute__ ((__packed__)) _fastd_packet_reply {
	FASTD_PACKET_COMMON;
	uint8_t reply_code;
} fastd_packet_reply;

typedef union _fastd_packet {
	fastd_packet_any any;
	fastd_packet_request request;
	fastd_packet_reply reply;
} fastd_packet;

#endif /* _FASTD_PACKET_H_ */
