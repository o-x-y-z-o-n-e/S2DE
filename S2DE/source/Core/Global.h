#ifndef S2DE_GLOBAL_H
#define S2DE_GLOBAL_H

#define S2DE_VERSION "0.1.0"

#define PTR(T) std::shared_ptr<T>
#define PTR_THIS(T) std::dynamic_pointer_cast<T>(shared_from_this())

namespace S2DE {

#ifdef S2DE_UNIX
	typedef u_int8_t uint8_t;
	typedef u_int16_t uint16_t;
	typedef u_int32_t uint32_t;
	typedef u_int64_t uint64_t;
#endif

	void LogCore(const char* format, ...);
	void LogCoreWarning(const char* message, ...);
	void LogCoreError(const char* message, ...);

}

#endif