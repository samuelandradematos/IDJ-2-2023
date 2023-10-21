
#ifndef INCLUDE_CAMERAFOLLOWER_H_
#define INCLUDE_CAMERAFOLLOWER_H_
#include "Component.h"
#include "Camera.h"



class CameraFollower : public Component{
    public:
        CameraFollower(GameObject& go);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Start();
};


#endif  // INCLUDE_CAMERAFOLLOWER_H_
