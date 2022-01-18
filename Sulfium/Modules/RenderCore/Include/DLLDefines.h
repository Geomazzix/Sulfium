#pragma once
//https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
// Define EXPORTED for windows and Linux
#if defined _WIN32 || defined __CYGWIN__
	#ifdef WIN_EXPORT
	 // Exporting...
		#ifdef __GNUC__
			#define MODULE_EXPORT __attribute__ ((dllexport))
		#else
			#define MODULE_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
		#endif
	#else
		#ifdef __GNUC__
			#define MODULE_EXPORT __attribute__ ((dllimport))
		#else
			#define MODULE_EXPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
		#endif
	#endif
#define MODULE_NO_EXPORT
#else
	#if __GNUC__ >= 4
		#define MODULE_EXPORT __attribute__ ((visibility ("default")))
		#define MODULE_NO_EXPORT  __attribute__ ((visibility ("hidden")))
	#else
		#define MODULE_EXPORT
		#define MODULE_NO_EXPORT
	#endif
#endif