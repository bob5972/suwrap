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
