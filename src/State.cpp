#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"


State::State() : popRequested(false), quitRequested(false), started(false), objectHoldingEnd(false) {}

State::~State() {
    objectArray.clear();
    #ifdef DEBUG
        std::cout << "~State()" << std::endl;
    #endif // DEBUG
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object) {
    std::shared_ptr<GameObject> sharedPtrGO(object);
    objectArray.emplace_back(sharedPtrGO);
    if (started) {
        sharedPtrGO->Start();
    }
    std::weak_ptr<GameObject> weakPtrGO(sharedPtrGO);
    return weakPtrGO;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object) {
    for (long long unsigned it = 0; it < objectArray.size(); it++) {
        if (objectArray[it].get() == object)
            return std::weak_ptr<GameObject>(objectArray[it]);
    }
    return {};
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start() {
    LoadAssets();
    StartArray();
    started = true;
}

void State::Pause() {
    started = false;
}

void State::Resume() {
    started = true;
}

void State::Update(float dt) {}

void State::Render() {}

void State::StartArray() {
    for (long long unsigned it = 0 ; it < objectArray.size(); it++) {
        objectArray[it]->Start();
    }
}

void State::UpdateArray(float dt) {
    // Update Camera
    Camera::Update(dt);
    if (!objectArray.empty()) {
        for (long long unsigned i = 0; i < objectArray.size() - 1; i++) {
            objectArray[i]->Update(dt);
        }

        for (long long unsigned i = 0; i < objectArray.size() - 1; i++) {
            if (objectArray[i]->IsHoldingEnd()) {
                objectHoldingEnd = true;
            }
        }

        for (long long unsigned i = 0; i < objectArray.size() - 1; i++) {
            if (objectArray[i]->IsDead()) {
                objectArray.erase(objectArray.begin() + i);
            }
        }

        for (long long unsigned i = 0; i < objectArray.size(); i++) {
            if (objectArray.at(i)->GetComponent("Collider") != nullptr) {
                for (long long unsigned j = i + 1; j < objectArray.size(); j++) {
                    Collider *iCollider = (Collider *) (objectArray.at(i)->GetComponent("Collider"));
                    if (objectArray.at(j)->GetComponent("Collider") != nullptr) {
                        Collider *jCollider = (Collider *) (objectArray.at(j)->GetComponent("Collider"));
                        if (
                                Collider::IsColliding(
                                        iCollider->box,
                                        jCollider->box,
                                        objectArray.at(i)->angleDeg * DEGREE_TO_RAD,
                                        objectArray.at(j)->angleDeg * DEGREE_TO_RAD
                                )
                                ) {
                            std::cout << "Collision entre 0x" << &objectArray.at(j) << " e 0x" << &objectArray.at(i)
                                      << std::endl;
                            objectArray.at(i)->NotifyCollision(*objectArray.at(j));
                            objectArray.at(j)->NotifyCollision(*objectArray.at(i));
                        }
                    }
                }
            }
        }
    }
}

void State::RenderArray() {
    for (long long unsigned it = 0 ; it < objectArray.size(); it++) {
        objectArray[it]->Render();
    }
}

std::weak_ptr<GameObject> State::GetObjectPtrThatHasCpt(std::string type) {
    for (long long unsigned it = 0; it < objectArray.size(); it++) {
        if (objectArray[it]->GetComponent(type) != nullptr) {
            return objectArray[it];
        }
    }
}

bool State::StateInHold() {
    return objectHoldingEnd;
}