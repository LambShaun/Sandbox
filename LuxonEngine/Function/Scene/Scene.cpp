#include "Scene.h"
#include "resource/ResourceManager.h"
#include "function/component/TransformComponent.h"
#include "function/rendering/AnimatedSpriteComponent.h"
#include "function/input/PlayerInputComponent.h"

#include <fstream>
#include <nlohmann/json.hpp>

namespace Luxon {
namespace Function {
namespace Scene {

    // 辅助函数，现在改为返回 Component* 以便后续加载
    Core::Component* AddComponentByType(Core::GameObject& gameObject, const std::string& type) {
        if (type == "Transform") return gameObject.AddComponent<Component::TransformComponent>();
        if (type == "AnimatedSprite") return gameObject.AddComponent<Rendering::AnimatedSpriteComponent>();
        if (type == "PlayerInput") return gameObject.AddComponent<Input::PlayerInputComponent>();
        return nullptr;
    }

    std::unique_ptr<Scene> Scene::Load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {  }
        nlohmann::json sceneData = nlohmann::json::parse(file);
        auto scene = std::make_unique<Scene>();

        for (const auto& goInstanceData : sceneData["gameObjects"]) {
            if (goInstanceData.contains("prefab")) {
                std::string prefabPath = goInstanceData["prefab"];
                std::ifstream prefabFile(prefabPath);
                if (!prefabFile.is_open()) continue;
                nlohmann::json prefabData = nlohmann::json::parse(prefabFile);

                std::string goName = goInstanceData.value("instanceName", prefabData.value("name", "GameObject"));
                scene->m_GameObjects.emplace_back(goName);
                auto& newGameObject = scene->m_GameObjects.back();

                // 从预制体加载组件
                if (prefabData.contains("components")) {
                    for (const auto& componentData : prefabData["components"]) {
                        auto* component = AddComponentByType(newGameObject, componentData.value("type", ""));
                        if (component) component->Load(componentData);
                    }
                }
                
                // 应用场景文件中的重载数据
                if (goInstanceData.contains("overrides")) {
                    for (auto& overrideItem : goInstanceData["overrides"].items()) {
                        std::string componentType = overrideItem.key();
                        // TODO... 此处需要一个更复杂的机制来找到并更新组件，暂时简化
                        if (componentType == "Transform") {
                            auto* comp = newGameObject.GetComponent<Component::TransformComponent>();
                            if(comp) comp->Load(overrideItem.value());
                        }
                    }
                }
            }
        }
        return scene;
    }
} // namespace Scene
} // namespace Function
} // namespace Luxon