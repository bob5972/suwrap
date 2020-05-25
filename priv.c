/*
 * priv.c -- Part of suwrap
 *
 * Copyright (c) 2010-2020 Michael Banack <github@banack.net>
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef priv_c_201010012205
#define priv_c_201010012205

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>

#include "priv.h"

int drop_priv_perm(uid_t new_uid)
{
	uid_t ruid, euid, suid;
	if (setresuid(new_uid, new_uid, new_uid) < 0) {
		return -1;
	}
	
	if (getresuid(&ruid, &euid, &suid) < 0) {
		return -1;
	}
	
	if (ruid != new_uid || euid != new_uid || suid != new_uid) {
		return -1;
	}
	
	return 0;
}

int drop_priv_temp(uid_t new_uid)
{
	if (setresuid(-1, new_uid, geteuid()) < 0) {
		return -1;
	}
	
	if (geteuid() != new_uid) {
		return -1;
	}
	
	return 0;
}

int restore_priv()
{
	uid_t ruid, euid, suid;
	if (getresuid(&ruid, &euid, &suid) < 0) {
		return -1;
	}
	
	if (setresuid(-1, suid, -1) < 0) {
		return -1;
	}
	
	if (geteuid() != suid) {
		return -1;
	}
	
	return 0;
}

#endif // priv_c_201010012205
