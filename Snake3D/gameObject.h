#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "drawable.h"
#include "updatable.h"

class GameObject : public Drawable, public Updatable {};

#endif
