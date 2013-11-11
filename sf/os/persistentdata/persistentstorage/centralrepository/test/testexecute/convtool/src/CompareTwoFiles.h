// Copyright (c) 1999-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//
 
#ifndef __COMPARETWOFILES_H__
#define __COMPARETWOFILES_H__

#include <f32file.h>


TBool FilesAreIdenticalL(RFs& aFs,
						const TDesC& aFile1,
						const TDesC& aFile2);

#endif