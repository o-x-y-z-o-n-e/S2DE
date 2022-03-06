#include "Util.h"
#include <string>
#include <stdlib.h>
#include <stddef.h>

namespace S2DE {

	

	int16_t BytesToInt16(uint8_t* buffer) {
		int16_t value = 0;

		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}


	uint16_t BytesToUInt16(uint8_t* buffer) {
		uint16_t value = 0;

		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}



	int32_t BytesToInt32(uint8_t* buffer) {
		int32_t value = 0;

		value = (value << 8) + buffer[3];
		value = (value << 8) + buffer[2];
		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}


	uint32_t BytesToUInt32(uint8_t* buffer) {
		uint32_t value = 0;

		value = (value << 8) + buffer[3];
		value = (value << 8) + buffer[2];
		value = (value << 8) + buffer[1];
		value = (value << 8) + buffer[0];

		return value;
	}


	uint64_t Hash(void* ptr) {
		uint64_t a = (uint64_t)ptr;

		a -= (a << 6);
		a ^= (a >> 17);
		a -= (a << 9);
		a ^= (a << 4);
		a -= (a << 3);
		a ^= (a << 10);
		a ^= (a >> 15);

		return a;
	}

}