/*
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *
 * $FreeBSD: src/usr.bin/make/lst.lib/lstDestroy.c,v 1.7 1999/08/28 01:03:49 peter Exp $
 * $DragonFly: src/usr.bin/make/lst.lib/Attic/lstDestroy.c,v 1.10 2004/12/17 00:02:57 okumoto Exp $
 *
 * @(#)lstDestroy.c	8.1 (Berkeley) 6/6/93
 */

/*-
 * LstDestroy.c --
 *	Nuke a list and all its resources
 */

#include "make.h"
#include "lst.h"

/*-
 *-----------------------------------------------------------------------
 * Lst_Destroy --
 *	Destroy a list and free all its resources. If the freeProc is
 *	given, it is called with the datum from each node in turn before
 *	the node is freed.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The given list is freed in its entirety.
 *
 *-----------------------------------------------------------------------
 */
void
Lst_Destroy(Lst *list, FreeProc *freeProc)
{
    LstNode *ln;
    LstNode *tln;

    if (!Lst_Valid(list)) {
	/*
	 * Note the check to catch uninitialized static Lst's.
	 * Gross, but useful.
	 */
	return;
    }

    if (list->lastPtr == NULL) {
	free(list);
	return;
    }
    /* To ease scanning */
    list->lastPtr->nextPtr = NULL;

    if (freeProc) {
	for (ln = list->firstPtr; ln != NULL; ln = tln) {
	     tln = ln->nextPtr;
	     (*freeProc)(ln->datum);
	     free(ln);
	}
    } else {
	for (ln = list->firstPtr; ln != NULL; ln = tln) {
	     tln = ln->nextPtr;
	     free(ln);
	}
    }

    free(list);
}
