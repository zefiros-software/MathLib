#pragma once

#if _PLATFORM_WIN 

#define StackAlign( x ) __declspec(align( x ))

#elif _PLATFORM_UNIX

#define StackAlign( x ) __attribute__ ((aligned ( x )))

#endif
