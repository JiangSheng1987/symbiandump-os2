/*
* Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/


#ifndef __HELLOTRACETYPESINL_H__
#define __HELLOTRACETYPESINL_H__

#include "OstTraceDefinitions.h"
#ifdef OST_TRACE_COMPILER_IN_USE
#include "HelloTraceTypesTraces.h"
#endif

inline void HelloTraceTypes::SignedIntegersDup2()
    {
    TInt8  eightBit     = - (TInt8)  1 << 6;
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_SIGNEDINTEGERSDUP2_8, 
                  "8 bit signed: %hhd", eightBit );
    
    TInt16 sixteenBit   = - (TInt16) 1 << 14; 
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_SIGNEDINTEGERSDUP2_16, 
                  "16 bit signed: %hd", sixteenBit );

    TInt32 thirtyTwoBit = - (TInt32) 1 << 30; 
    OstTrace1( TRACE_INTERNALS, HELLOTRACETYPES_SIGNEDINTEGERSDUP2_32, 
               "32 bit signed: %d", thirtyTwoBit );

    TInt64 sixtyFourBit = - (TInt64) 1 << 62; 
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_SIGNEDINTEGERSDUP2_64, 
                  "64 bit signed: %Ld", sixtyFourBit );
    }

inline void HelloTraceTypes::UnsignedIntegersDup2()
    {
    TUint8  eightBit     = (TUint8)  1 << 6;
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_UNSIGNEDINTEGERSDUP2_8, 
                  "8 bit unsigned: %hhu", eightBit );
    
    TUint16 sixteenBit   = (TUint16) 1 << 14; 
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_UNSIGNEDINTEGERSDUP2_16, 
                  "16 bit unsigned: %hu", sixteenBit );

    TUint32 thirtyTwoBit = (TUint32) 1 << 30; 
    OstTrace1( TRACE_INTERNALS, HELLOTRACETYPES_UNSIGNEDINTEGERSDUP2_32, 
               "32 bit unsigned: %u", thirtyTwoBit );

    TUint64 sixtyFourBit = (TUint64) 1 << 62; 
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_UNSIGNEDINTEGERSDUP2_64, 
                  "64 bit unsigned: %Lu", sixtyFourBit );
    }

inline void HelloTraceTypes::DescriptorsDup2()
    {
    _LIT8(KAscii, "Some ASCII text");
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_ASCIIDUP2, "8 bit descriptor: %s", KAscii() );

    _LIT16(KUnicode, "Some unicode text");    
    OstTraceExt1( TRACE_INTERNALS, HELLOTRACETYPES_UNICODEDUP2, "16 bit descriptor: %S", KUnicode() );
    }

#endif  // __HELLOTRACETYPESINL_H__

