/*	$NetBSD: poll.h,v 1.12 2008/04/28 20:24:11 martin Exp $	*/

/*-
 * Copyright (c) 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Charles M. Hannum.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SYS_POLL_H_
#define	_SYS_POLL_H_

#include <sys/featuretest.h>

#ifndef T2EX
typedef unsigned int	nfds_t;
#else
#ifndef nfds_t
typedef unsigned int    nfds_t;
#define	nfds_t		nfds_t
#endif
#endif

#ifndef T2EX
struct pollfd {
	int	fd;		/* file descriptor */
	short	events;		/* events to look for */
	short	revents;	/* events returned */
};
#endif

/*
 * Testable events (may be specified in events field).
 */
#define	POLLIN		0x0001
#define	POLLPRI		0x0002
#define	POLLOUT		0x0004
#define	POLLRDNORM	0x0040
#define	POLLWRNORM	POLLOUT
#define	POLLRDBAND	0x0080
#define	POLLWRBAND	0x0100

/*
 * Non-testable events (may not be specified in events field).
 */
#define	POLLERR		0x0008
#define	POLLHUP		0x0010
#define	POLLNVAL	0x0020

#if defined(_NETBSD_SOURCE)
/*
 * Infinite timeout value.
 */
#define	INFTIM		-1
#endif

#ifdef _KERNEL
#ifndef T2EX
#include <sys/signal.h>		/* for sigset_t */
#endif

struct lwp;
struct timeval;

#ifndef T2EX
int	pollcommon(struct lwp *, register_t *, struct pollfd *, u_int,
	    struct timeval *, sigset_t *);
#endif
#else
#include <sys/cdefs.h>

__BEGIN_DECLS
int	poll(struct pollfd *, nfds_t, int);
__END_DECLS

#ifdef _NETBSD_SOURCE
#include <sys/sigtypes.h>	/* for sigset_t */
struct timespec;

__BEGIN_DECLS
int	pollts(struct pollfd * __restrict, nfds_t,
	    const struct timespec * __restrict, const sigset_t * __restrict);
__END_DECLS
#endif /* _NETBSD_SOURCE */

#endif /* _KERNEL */

#endif /* !_SYS_POLL_H_ */