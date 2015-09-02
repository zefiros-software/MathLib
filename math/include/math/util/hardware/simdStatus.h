#pragma once
#ifndef __SIMD_STATUS_H__
#define __SIMD_STATUS_H__

#include "math/types.h"

//
// CPUID
//

#include <vector>
#include <array>
#include <string>

#ifdef _WIN32
#define GetCpuID _cpuid
#else
#ifndef __LP64__
#error currently cpuid is only supported for x86_64 platforms!
#endif
#define GetCpuID(iarray, func)\
	    __asm__ __volatile__ ( \
       "cpuid":\
	   "=a" (iarray[0]),\
       "=b" (iarray[1]),\
       "=c" (iarray[2]),\
       "=d" (iarray[3]) :\
       "a" (func));
#endif

//
// Status
//

/*
#ifdef __AVX2__
#define SIMD_INSTRUCTION_SET 7

#elif  __AVX__
#define SIMD_INSTRUCTION_SET 6

#elif __SSE4_2__
#define SIMD_INSTRUCTION_SET 5

#elif ( __SSE4_1__ || ( _M_IX86_FP == 2 ) )
#define SIMD_INSTRUCTION_SET 4

#elif  __SSE3__
#define SIMD_INSTRUCTION_SET 3

#elif ( __SSE2__ || _M_X86 )
#define SIMD_INSTRUCTION_SET 2

#elif  __SSE__
#define SIMD_INSTRUCTION_SET 1
*/

class SimdStatus
{
public:

    inline SimdStatus() : mIntelCpu( false ), mAmdCpu( false )
    {
        CaptureCpuInfo();
        DefineVendor();
    }

    bool SupportsSSE() const
    {
        return mFunctionLevel1_DINT[25]; 
    }	
    
    bool SupportsSSE2() const
    {
        return mFunctionLevel1_DINT[26]; 
    }	
    
    bool SupportsSSE3() const
    {
        return mFunctionLevel1_CINT[9]; 
    }	

    bool SupportsSSE4_1() const
    {
        return mFunctionLevel1_CINT[19]; 
    }	
    
    bool SupportsSSE4_2() const
    {
        return mFunctionLevel1_CINT[20]; 
    }
    
    bool SupportsAVX() const
    {
        return mFunctionLevel1_CINT[28]; 
    }

    bool SupportsFMA() const
    {
        return mFunctionLevel1_CINT[12]; 
    }
    
    U32 SIMDLevel() const
    {
        U32 level = 0;
        
        if ( SupportsSSE() )   { level++; }
        if ( SupportsSSE2() )  { level++; }
        if ( SupportsSSE3() )  { level++; }
        if ( SupportsSSE4_1() ){ level++; }
        if ( SupportsSSE4_2() ){ level++; }
        if ( SupportsAVX() )   { level++; }
        if ( SupportsFMA() )   { level++; }
        
        return level;
    }
    
    const std::string &Vendor() const
    {
        return mVendor;
    }

private:

    inline void CaptureCpuInfo()
    {
        std::array<int, 4> cpuid;

        GetCpuID(cpuid.data(), 0);
        
        const S32 ilevels = cpuid[0];
        
        for ( S32 i=0; i < ilevels; ++i )
        {
            GetCpuID(cpuid.data(), i);
            mFuncLevels.push_back(cpuid);
        }
    }
    
    inline void DefineVendor()
    {
        char vendor[32];
        memset( vendor, 0, sizeof(vendor) );
        memcpy( vendor, (char*) &mFuncLevels[0][1], sizeof( S32 ) );
        memcpy( vendor + 4, (char*) &mFuncLevels[0][3], sizeof( S32 ) );
        memcpy( vendor + 8, (char*) &mFuncLevels[0][2], sizeof( S32 ) );
        
        mVendor = std::string( vendor );
        
        if ( mVendor == "AuthenticAMD" )
        {
            mAmdCpu = true;
        }
        
        if ( mVendor == "GenuineIntel" )
        {
            mIntelCpu = true;
        }
        
        if ( mFuncLevels.size() >= 1 )
        {
            mFunctionLevel1_CINT = mFuncLevels[1][2];
            mFunctionLevel1_DINT = mFuncLevels[1][3];
        }
        
        if ( mFuncLevels.size() >= 7 ) 
        {
            mFunctionLevel7_BINT = mFuncLevels[7][1];
            mFunctionLevel7_CINT = mFuncLevels[7][2];
        }
    }
    
    bool mIntelCpu;
    bool mAmdCpu;
    
    std::string mVendor;
    
    std::bitset<32> mFunctionLevel1_CINT;
    std::bitset<32> mFunctionLevel1_DINT;
    std::bitset<32> mFunctionLevel7_BINT;
    std::bitset<32> mFunctionLevel7_CINT;
    std::vector< std::array<S32, 4> > mFuncLevels;
};

#endif