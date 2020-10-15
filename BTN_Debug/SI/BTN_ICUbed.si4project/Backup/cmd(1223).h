
#ifndef __CMD_H
#define	__CMD_H

#define	BOARD_LR	1

#if	BOARD_LR //left board
/* inside */
const static char* INBACK_UP   = "AA03010F";
const static char* INBACK_DOWN = "AA03010F";
const static char* INLEG_UP    = "AA030111";
const static char* INLEG_DOWN  = "AA030112";
const static char* IN_CALL     = "AA030113";

/* outside */
const static char* OUTBED_UP      = "AA030101";
const static char* OUTBED_DOWN    = "AA030102";
const static char* OUTBACK_UP     = "AA030103";
const static char* OUTBACK_DOWN   = "AA030104";
const static char* OUTLEG_UP      = "AA030105";
const static char* OUTLEG_DOWN    = "AA030106";
const static char* OUTPITCH_FRONT  = "AA030107";
const static char* OUTPITCH_AFTER  = "AA030108";
const static char* OUTROLL_LEFT    = "AA030109";
const static char* OUTROLL_RIGHT   = "AA03010A";
const static char* OUT_CALL        = "AA03010B";
const static char* OUT_FLOWER      = "AA03010C";
const static char* OUT_CCP         = "AA03010D";
const static char* OUT_CPR         = "AA03010E";

#else //right board
/* inside */
const static char* INBACK_UP   = "AA03010F";
const static char* INBACK_DOWN = "AA03010F";
const static char* INLEG_UP    = "AA030111";
const static char* INLEG_DOWN  = "AA030112";
const static char* IN_CALL     = "AA030113";

/* outside */
const static char* OUTBED_UP      = "AA030101";
const static char* OUTBED_DOWN    = "AA030102";
const static char* OUTBACK_UP     = "AA030103";
const static char* OUTBACK_DOWN   = "AA030104";
const static char* OUTLEG_UP      = "AA030105";
const static char* OUTLEG_DOWN    = "AA030106";
const static char* OUTPITCH_FRONT  = "AA030107";
const static char* OUTPITCH_AFTER  = "AA030108";
const static char* OUTROLL_LEFT    = "AA030109";
const static char* OUTROLL_RIGHT   = "AA03010A";
const static char* OUT_CALL        = "AA03010B";
const static char* OUT_FLOWER      = "AA03010C";
const static char* OUT_CCP         = "AA03010D";
const static char* OUT_CPR         = "AA03010E";




#endif



#endif




