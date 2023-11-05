#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_
#include "GameObject.h"

class State {
public:
    State();
    virtual ~State();
    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual std::weak_ptr<GameObject> AddObject(GameObject *object);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject *object);
    virtual std::weak_ptr<GameObject> GetObjectPtrThatHasCpt(std::string type);

    virtual bool StateInHold();

    bool PopRequested();
    bool QuitRequested();
protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();

    bool popRequested;
    bool quitRequested;
    bool started;

    bool objectHoldingEnd;

    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif //INCLUDE_STATE_H_
