/*
* Copyright (c) 1994-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Default locale settings for SPR -- the locale used for American Sprint.
*
*/


#include "ls_std.h"
#include "complocl.h"

const TLanguage ELangAmericanSprint=static_cast<TLanguage>(ELangAmerican|1024/*EDialectSprint*/);
// The configuration data
const TLanguage LLocaleData::Language = ELangAmericanSprint;
const TInt LLocaleData::CountryCode = 1;
const TInt LLocaleData::UniversalTimeOffset = -6*3600;
const TDateFormat LLocaleData::DateFormat = EDateAmerican;
const TTimeFormat LLocaleData::TimeFormat = ETime12;
const TLocalePos LLocaleData::CurrencySymbolPosition = ELocaleBefore;
const TBool LLocaleData::CurrencySpaceBetween = EFalse;
const TInt LLocaleData::CurrencyDecimalPlaces = 2;
const TLocale::TNegativeCurrencyFormat LLocaleData::NegativeCurrencyFormat=TLocale::TNegativeCurrencyFormat(0); // replacing CurrencyNegativeInBrackets
const TBool LLocaleData::CurrencyTriadsAllowed = ETrue;
const TText * const LLocaleData::ThousandsSeparator = _S(",");
const TText * const LLocaleData::DecimalSeparator = _S(".");
const TText * const LLocaleData::DateSeparator[KMaxDateSeparators] = {_S(""),_S("/"),_S("/"),_S("")};
const TText * const LLocaleData::TimeSeparator[KMaxTimeSeparators] = {_S(""),_S(":"),_S(":"),_S("")};
const TLocalePos LLocaleData::AmPmSymbolPosition = ELocaleAfter;
const TBool LLocaleData::AmPmSpaceBetween = ETrue;
//const TUint LLocaleData::DaylightSaving = EDstNone;
const TDaylightSavingZone LLocaleData::HomeDaylightSavingZone = EDstNorthern;
const TUint LLocaleData::WorkDays = 0x1f;
const TText * const LLocaleData::CurrencySymbol = _S("\x0024");
const TText* const LLocaleData::ShortDateFormatSpec = _S("%F%*M/%*D/%Y"); // needs checking by a localisation team (this item was added since real localisation - the value given here has been set by a software developer so it may be wrong)
const TText* const LLocaleData::LongDateFormatSpec = _S("%F%*D%X %N %Y"); // needs checking by a localisation team (this item was added since real localisation - the value given here has been set by a software developer so it may be wrong)
const TText* const LLocaleData::TimeFormatSpec = _S("%F%*I:%T:%S %*A"); // needs checking by a localisation team (this item was added since real localisation - the value given here has been set by a software developer so it may be wrong)
const TFatUtilityFunctions* const LLocaleData::FatUtilityFunctions = NULL;
const TDay LLocaleData::StartOfWeek = ESunday;
const TClockFormat LLocaleData::ClockFormat = EClockAnalog;
const TUnitsFormat LLocaleData::UnitsGeneral = EUnitsImperial;
const TUnitsFormat LLocaleData::UnitsDistanceShort = EUnitsImperial;
const TUnitsFormat LLocaleData::UnitsDistanceLong = EUnitsImperial;
const TUint LLocaleData::ExtraNegativeCurrencyFormatFlags = 0;
const TLanguage LLocaleData::LanguageDowngrade[3] = {ELangAmerican, ELangEnglish, ELangNone};

