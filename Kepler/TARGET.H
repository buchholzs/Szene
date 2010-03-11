#ifndef _TARGET_H
#define _TARGET_H
///////////////////////////////////////////////////////////////////////////////
//
// MODULE: target.h
// DESCRIPTION: Klasse Target
// HISTORY: $Log: target.h,v $
// HISTORY: Revision 1.1  1998/04/11 22:51:43  buchholz
// HISTORY: Initial revision
// HISTORY:
//
///////////////////////////////////////////////////////////////////////////////

// Systemincludes
#include <string>
using namespace std;

// Projektincludes
#include <plush.h>

class Target {
public:
  Target();

  Target(
			pl_Obj	*Obj,			// [i] zu verfolgendes Objekt
			pl_Float	radius,		// [i] Maximale Ausdehnung des Objektes
			const string &name	// [i] Name des Objektes
		  );

  	Target&  operator =  (const Target&  other);

	pl_Obj	*Obj_;	// zu verfolgendes Objekt
	pl_Float	radius_;	//	Maximale Ausdehnung des Objektes
	string	name_;	// Name des Objektes
private:
};

//---Inline------------------------------------------------------------------

#endif
