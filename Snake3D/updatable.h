#ifndef UPDATABLE_H
#define UPDATABLE_H
#include "skTypes.h"

class Updatable
{
public:
	virtual void update(sk_double dt) = 0;

	virtual ~Updatable() {};
};

#endif
