/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/** @file
@internalComponent
*/

#ifndef MOTGOBSERVER_H
#define MOTGOBSERVER_H

#include <e32def.h>
#include <e32property.h> //Publish & Subscribe header
#include <e32cmn.h>
#include <e32base.h>
#include <usbotgdefs.h>

//To observe ID-pin, VBus and OtgState properties via Publish and Subscribe
NONSHARABLE_CLASS(MOtgPropertiesObserver)
	{
public:
// For host OTG enabled charging plug-in
#ifdef SYMBIAN_ENABLE_USB_OTG_HOST_PRIV 
	virtual void MpsoIdPinStateChanged(TInt aValue) = 0;
	virtual void MpsoOtgStateChangedL(TUsbOtgState aNewState) = 0;
#endif	
	virtual void MpsoVBusStateChanged(TInt aNewState) = 0;
	};


#endif //MOTGOBSERVER_H
