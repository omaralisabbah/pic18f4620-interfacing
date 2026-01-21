
#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* SECTION : INCLUDES */
#include "std_libraries.h"
#include "compiler.h"


/* SECTION : DATATYPE DECLARATIONS */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef uint8 STD_RETURN_TYPE; // E_OK, E_NOT_OK


/* SECTION : MACRO DECLARATIONS */
#define STD_HIGH       0x01
#define STD_LOW        0x00

#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define E_OK         (STD_RETURN_TYPE)0x01
#define E_NOT_OK     (STD_RETURN_TYPE)0x00

#define ZERO_INIT 0

/* SECTION : MACRO FUNCTION DECLARATIONS */

/* SECTION : FUNCTION DECLARATIONS */


#endif	/* MCAL_STD_TYPES_H */

