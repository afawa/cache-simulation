#ifndef SYS_SETTING
#define SYS_SETTING

typedef unsigned long long  md_addr_t;
typedef signed long long tick_t;
typedef unsigned char byte_t;

enum mem_cmd{
    Read,
    Write
};

typedef signed long long counter_t;

#ifndef MAX
#define MAX(a, b)    (((a) < (b)) ? (b) : (a))
#endif
#ifndef MIN
#define MIN(a, b)    (((a) < (b)) ? (a) : (b))
#endif

/* host-dependent canonical type definitions */
typedef int bool_t;			/* generic boolean type */
typedef unsigned char byte_t;		/* byte - 8 bits */
typedef signed char sbyte_t;
typedef unsigned short half_t;		/* half - 16 bits */
typedef signed short shalf_t;
typedef unsigned int word_t;		/* word - 32 bits */
typedef signed int sword_t;
typedef float sfloat_t;			/* single-precision float - 32 bits */
typedef double dfloat_t;		/* double-precision float - 64 bits */

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif

