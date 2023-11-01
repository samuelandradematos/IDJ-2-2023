#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject& ass) : associated(ass) {}

Component::~Component() {}

void Component::Start() {}

void Component::NotifyCollision(GameObject &other) {}
