// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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

/**
 @file
 @test
 @internalComponent
*/

#if (!defined __TEF_EFM_BURSUITESIMSTEPBASE__)
#define __TEF_EFM_BURSUITESIMSTEPBASE__

#include "tef_efm_bursuitedefs.h"
#include <babackup.h>
#include <e32property.h>

/**
 * Simulation base class for simulating a backup and restore operation.
 * The functionality allows copying and restoring a feature.dat file, and 
 * checking that the registration file exists.
 */ 
class CTefEfmBURSuiteSimStepBase
	{
public:
	virtual ~CTefEfmBURSuiteSimStepBase();
	
	static CTefEfmBURSuiteSimStepBase* NewLC();
public:
	
	/** Use external API to start a backup. */
	void Simulate_StartBackupL();
	/** Use external API to stop a backup. */
	void Simulate_EndBackupL( TBool aNormal = ETrue );
	/** Use external API to start a restore. */
	void Simulate_StartRestoreL();
	/** Use external API to stop a restore. */
	void Simulate_EndRestoreL( TBool aNormal = ETrue );
	
	
	void Simulate_StartUndefinedL();
	void Simulate_EndUndefinedL( TBool aNormal = ETrue );
	
	/** 
	 * Confirm that the registration.xml file is present.
	 * @leave KErrNotFound if file not present.
	 */	
	void Simulate_CheckRegFileL();	

private:
	CTefEfmBURSuiteSimStepBase();
	void ConstructL();
private:
	CBaBackupSessionWrapper* iBackupClient;
	};

#endif
