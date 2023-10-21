#ifndef INCLUDE_COMPONENT_H_
#define INCLUDE_COMPONENT_H_
#include <string>

class GameObject;

class Component {
    public:
        Component(GameObject& ass);  // NOLINT
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;
        virtual void Start();
    protected:
        GameObject& associated;
};

#endif  // INCLUDE_COMPONENT_H_
