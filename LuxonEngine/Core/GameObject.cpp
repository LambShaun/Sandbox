#include "GameObject.h"

namespace Luxon {
namespace Core {
    GameObject::GameObject(std::string name) : m_Name(std::move(name)) {}
    GameObject::~GameObject() = default;
    GameObject::GameObject(GameObject&& other) noexcept = default;
    GameObject& GameObject::operator=(GameObject&& other) noexcept = default;

    void GameObject::StartAllComponents() {
        for (const auto& pair : m_Components) {
            if (pair.second) {
                pair.second->Start();
            }
        }
    }

    void GameObject::UpdateAllComponents() {
        for (const auto& pair : m_Components) {
            if (pair.second) {
                pair.second->Update();
            }
        }
    }

} // namespace Core
} // namespace Luxon