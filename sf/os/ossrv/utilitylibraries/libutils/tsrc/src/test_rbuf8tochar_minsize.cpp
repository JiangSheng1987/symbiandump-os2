/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <stdio.h>
#include<e32std.h>
#include<e32base.h>
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
int main()
{
    __UHEAP_MARK;
    RBuf8 myrbuf;
    TBufC8<5> myTBufC (_L8("hello"));
    myrbuf.Create(myTBufC);
    myrbuf.CleanupClosePushL();
    char *des= new char[5];
    int retval=ESuccess;
    int size=5;
    retval= Rbuf8ToChar(myrbuf,des,size);

    if(retval ==ESuccess)
    {
    printf("Test_rbuf8tochar_minsize passed\n");
    }
    else
    {
    assert_failed = true;
    printf("Test_rbuf8tochar_minsize FAILURE\n");
    }
    delete[] des;
    des=NULL;
    CleanupStack::PopAndDestroy(1);
    __UHEAP_MARKEND;
    testResultXml("Test_rbuf8tochar_minsize");
	return 0;
}
