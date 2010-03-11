///////////////////////////////////////////////////////////////////////////////
//
// MODULE: target.h
// DESCRIPTION: Klasse Target
// HISTORY:
//		$Log: target.cc,v $
// 	Revision 1.1  1998/04/11 22:51:43  buchholz
// 	Initial revision
//
///////////////////////////////////////////////////////////////////////////////
#include	"target.h"

// Systemincludes

// Projektincludes

//---Konstanten--------------------------------------------------------------

//---Implementation----------------------------------------------------------
Target::Target()
	: 	Obj_(NULL),
		radius_(0.0),
		name_()
{}
Target::Target(pl_Obj	*Obj, pl_Float	radius, const string &name)
	: 	Obj_(Obj),
		radius_(radius),
		name_(name)
{}

Target&  Target::operator =  (const Target&  other)
{
 if (this != &other) {
	Obj_ = other.Obj_;
	name_= other.name_;
 }
 return *this;
}

