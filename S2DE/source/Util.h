#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>

namespace S2DE {

	uint64_t Hash(void* ptr);


	int16_t BytesToInt16(uint8_t* buffer);
	uint16_t BytesToUInt16(uint8_t* buffer);
	int32_t BytesToInt32(uint8_t* buffer);
	uint32_t BytesToUInt32(uint8_t* buffer);
}

#endif