// Copyright (c) 2003-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __CLIENTREQUEST_H__
#define __CLIENTREQUEST_H__

#include <e32std.h>

#include <ecom/implementationinformation.h>
//
// MClientRequest
//
// Provides an interface identical to RMessage.
// This facilitiates unit testing of the session by enabling RMessage to be
// replaced in unit test code.
//

class MClientRequest
/**
@internalComponent
*/
	{
	public:
	
		virtual TBool IsNull() const = 0;
	
		virtual TInt Function() const = 0;
	
		virtual void Complete(TInt aReason) const = 0;	
	
		virtual void Panic(const TDesC& aCategory, TInt aReason) const = 0;
	public:
	
		virtual TInt Int0() const = 0;
	
		virtual TInt Int1() const = 0;
	
		virtual TInt Int2() const = 0;
	
		virtual TInt Int3() const = 0;
	public:
	
		virtual TInt GetDesLength(TInt aParam) const = 0;
	
		virtual TInt GetDesMaxLength(TInt aParam) const = 0;
	
		virtual void ReadL(TInt aParam, TDes8& aDes, TInt aOffset=0) const = 0;
	
		virtual void ReadL(TInt aParam, TDes& aDes,  TInt aOffset=0) const = 0;
	
		virtual TInt Write(TInt aParam, const TDesC8& aDes, TInt aOffset=0) const = 0;
	
		virtual void WriteL(TInt aParam, const TDesC8& aDes) const = 0;
	
		virtual void WriteL(TInt aParam, const TDesC& aDes, TInt aOffset=0) const = 0;
	};

//
//

# ifndef __ECOMSERVER_TESTING__
//
// TClientRequest
//
// Concrete implementation of MClientRequest that acts as an adaptor for
// RMessage.
//

class TClientRequest : public MClientRequest
/**
@internalComponent
*/
	{
	public:
	
		TClientRequest() {}
	
		TClientRequest(const RMessage2&);
	
		virtual TBool IsNull() const;
	
		virtual TInt Function() const;
	
		virtual void Complete(TInt aReason) const;
	
		virtual void Panic(const TDesC& aCategory, TInt aReason) const;
	
		virtual TInt Int0() const;
	
		virtual TInt Int1() const;
	
		virtual TInt Int2() const;
	
		virtual TInt Int3() const;
	
		virtual TInt GetDesLength(TInt aParam) const;
	
		virtual TInt GetDesMaxLength(TInt aParam) const;
	
		virtual void ReadL(TInt aParam, TDes8& aDes, TInt aOffset=0) const;
	
		virtual void ReadL(TInt aParam, TDes& aDes,  TInt aOffset=0) const;
	
		virtual TInt Write(TInt aParam, const TDesC8& aDes, TInt aOffset=0) const;
	
		virtual void WriteL(TInt aParam, const TDesC8& aDes) const;
	
		virtual void WriteL(TInt aParam, const TDesC& aDes, TInt aOffset=0) const;
		TBool CheckCapability(const TCapabilitySet& aCapabilities, const CImplementationInformation& aImplInfo) const;
	private:
#ifndef __REMOVE_PLATSEC_DIAGNOSTICS__
		void EmitDiagnostic(const TCapabilitySet& aCapabilities, const CImplementationInformation& aImplInfo) const;
#endif
		TBool HasCapabilities(const TCapabilitySet& aCapabilities) const;
	private:
	
		RMessage2 iMessage;
		TSecurityInfo iSecurityInfo;
	};

//
//
# else //_UNIT_TESTING_
//
// TClientRequest
//
// Unit test version.
//
class TClientRequest : public MClientRequest
/**
@internalComponent
*/
	{
	public:
		TClientRequest();
		TClientRequest(const RMessage2&) {}; // Needed for compilation, but not used in testing.
		virtual TBool IsNull() const;
		virtual TInt Function() const;
		virtual void Complete(TInt aReason) const;
		virtual void Panic(const TDesC& aCategory, TInt aReason) const;
		virtual TInt Int0() const;
		virtual TInt Int1() const;
		virtual TInt Int2() const;
		virtual TInt Int3() const;
		virtual TInt GetDesLength(TInt aParam) const;
		virtual TInt GetDesMaxLength(TInt aParam) const;
		virtual void ReadL(TInt aParam, TDes8& aDes, TInt aOffset=0) const;
		virtual void ReadL(TInt aParam, TDes& aDes, TInt aOffset=0) const;
		virtual TInt Write(TInt aParam, const TDesC8& aDes, TInt aOffset=0) const;
		virtual void WriteL(TInt aParam, const TDesC8& aDes) const;
		virtual void WriteL(TInt aParam, const TDesC& aDes, TInt aOffset=0) const;
		TBool CheckCapability(const TCapabilitySet& aCapabilities, const CImplementationInformation& aImplInfo) const;
	private:
		TBool HasCapabilities(const TCapabilitySet& aCapabilities) const;
#ifndef __REMOVE_PLATSEC_DIAGNOSTICS__
		void EmitDiagnostic(const TCapabilitySet& aCapabilities, const CImplementationInformation& aImplInfo) const;
#endif
	public://debug only
		inline void SetRequest(TRequestStatus& aStatus);
		inline void SetFunction(TInt);
		inline void SetCapability(TUint32);
		inline void SetParam(TInt aParam, TInt aValue);
		inline void SetParam(TInt aParam, TDes8* aValue);
		inline void SetParam(TInt aParam, const TDesC8* aValue);
		inline void SetParam(TInt aParam, TDes* aValue);
		inline void SetParam(TInt aParam, const TDesC* aValue);
		inline void SetIdentity(TUid aIdentity);
		TUid Identity() const;
		inline TInt CompletionCode() const;
		inline void Reset();
		
	private:
		TInt iFunction;
		TUint32 iCapability;
		mutable TInt iCompletion;
		TInt iParams[KMaxMessageArguments];
		mutable TRequestStatus* iStatus;
		TBool iStatusActive;
		TUid iIdentity;
	};

//
inline void TClientRequest::SetRequest(TRequestStatus& aStatus) {iStatus = &aStatus; iStatusActive = ETrue;}
inline void TClientRequest::SetFunction(TInt aFunction) { iFunction = aFunction; }
inline void TClientRequest::SetCapability(TUint32 aCap) { iCapability = aCap; }
inline void TClientRequest::SetParam(TInt aParam, TInt aValue) { iParams[aParam] = aValue; }
inline void TClientRequest::SetParam(TInt aParam, TDes8* aValue) { iParams[aParam] = TInt(aValue); }
inline void TClientRequest::SetParam(TInt aParam, const TDesC8* aValue) { iParams[aParam] = TInt(aValue); }
inline void TClientRequest::SetParam(TInt aParam, TDes* aValue) { iParams[aParam] = TInt(aValue); }
inline void TClientRequest::SetParam(TInt aParam, const TDesC* aValue) { iParams[aParam] = TInt(aValue); }
inline void TClientRequest::SetIdentity(TUid aIdentity) { iIdentity = aIdentity; }
inline TInt TClientRequest::CompletionCode() const { return iCompletion; }
inline void TClientRequest::Reset() { *this = TClientRequest(); }

//
//
#endif //__ECOMSERVER_TESTING__

//
//
//
#endif //__CLIENTREQUEST_H__
