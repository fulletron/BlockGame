#ifndef __DEFINE_GETTERSETTER_H_
#define __DEFINE_GETTERSETTER_H_

// MACROS FOR GETTING AND SETTING (INSPIRED BY DXUT)
#define SET_ACCESSOR( x, y )       inline void set__##y( x a_newValue )   { y = a_newValue; }
#define GET_ACCESSOR( x, y )       inline x get__##y()           { return y; }
#define GET_SET_ACCESSOR( x, y )   SET_ACCESSOR( x, y ) GET_ACCESSOR( x, y )

#define SETP_ACCESSOR( x, y )      inline void set__##y( x* a_newValue )  { y = *a_newValue; };
#define GETP_ACCESSOR( x, y )      inline x* get__##y()          { return &y; };
#define GETP_SETP_ACCESSOR( x, y ) SETP_ACCESSOR( x, y ) GETP_ACCESSOR( x, y )

#define SETRP_ACCESSOR( x, y )      inline void set__##y( x* a_newValue )  { y = a_newValue; };
#define GETRP_ACCESSOR( x, y )      inline x* get__##y()          { return y; };
#define GETRP_SETRP_ACCESSOR( x, y ) SETRP_ACCESSOR( x, y ) GETRP_ACCESSOR( x, y )

#endif