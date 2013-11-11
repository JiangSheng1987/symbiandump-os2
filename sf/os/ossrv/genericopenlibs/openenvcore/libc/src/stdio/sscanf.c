/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * � Portions copyright (c) 2005-2006  Nokia Corporation.  All rights reserved.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)sscanf.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */
#include <sys/cdefs.h>
#ifndef __SYMBIAN32__
__FBSDID("$FreeBSD: src/lib/libc/stdio/sscanf.c,v 1.11 2002/10/12 16:13:41 mike Exp $");
#endif
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "local.h"
#include "common_def.h"

static int eofread(void *, char *, int);

/* ARGSUSED */
static int
eofread(void *cookie,
	char *buf,
	int len)
{
#ifdef __SYMBIAN32__
	cookie = cookie; /*dummy implementations to fix warning 'variable/argument not used in function' */
	buf = buf;
	len = len;
#endif //__SYMBIAN32__    
	return (0);
}

EXPORT_C int
sscanf(const char * __restrict str, char const * __restrict fmt, ...)
{
	int ret;
	va_list ap;
	struct __sFILEX extra;
	FILE f;

	f._file = -1;
	f._flags = __SRD;
	f._bf._base = f._p = (unsigned char *)str;
	f._bf._size = f._r = strlen(str);
	f._read = eofread;
	f._ub._base = NULL;
	f._lb._base = NULL;
	f._extra = &extra;
	INITEXTRA(&f);
	va_start(ap, fmt);
	ret = __svfscanf(&f, fmt, ap);
	va_end(ap);
	return (ret);
}