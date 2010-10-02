#ifndef _env_h_201010012216
#define _env_h_201010012216


extern void addenv (const char *, /*@null@*/const char *);
extern void initenv (void);
extern void set_env (int, char *const *);
extern void sanitize_env (void);

#endif //_env_h_201010012216
