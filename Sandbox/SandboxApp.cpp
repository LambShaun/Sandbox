#include "Platform/Window.h"
#include "Function/Rendering/Renderer.h"
#include "Function/Input/Input.h"
#include "Function/Physics/Collision.h"
#include "Core/Math/Vec2D.h"
#include "Core/Time/Time.h"
#include "Resource/Texture.h"
#include "Resource/ResourceManager.h"
#include "Function/Animation/AnimationSet.h"
#include "Function/Animation/Animator.h"
#include "Function/Animation/AnimationStateMachine.h"

#include <memory>
#include <Windows.h>
#include <iostream>

class SandBoxApp {
public:
    SandBoxApp() {
        m_Window = std::unique_ptr<Luxon::Platform::Window>(Luxon::Platform::Window::Create());
        Luxon::Function::Rendering::Renderer::Init(m_Window->GetNativeWindow());

        // 加载包含所有动画帧的精灵图
        try {
            // 加载精灵图和JSON
            m_AnimationSet = Luxon::Resource::ResourceManager<Luxon::Function::Animation::AnimationSet>::Load("assets/player_animations.json");
            if (m_AnimationSet) {
                m_Texture = Luxon::Resource::ResourceManager<Luxon::Resource::Texture>::Load(m_AnimationSet->GetSpriteSheetPath());
            }
            // 配置动画状态机
            if (m_AnimationSet) {
                // 定义状态
                m_FSM.AddState("Idle", "idle"); // "Idle"状态播放名为"idle"的动画
                m_FSM.AddState("Run", "walk");   // "Run"状态播放名为"run"的动画

                // 定义切换规则
                m_FSM.AddTransition("Idle", "Run", [this](const auto& conditions) {
                    return m_IsMoving;
                    });
                m_FSM.AddTransition("Run", "Idle", [this](const auto& conditions) {
                    return !m_IsMoving;
                    });

                // 设置初始状态和播放初始动画
                m_FSM.SetInitialState("Idle");
                m_Animator.Play(m_AnimationSet->GetAnimation("idle"));
            }
        }
        catch (const std::exception& e) {
            MessageBoxA(NULL, e.what(), "Luxon Engine Error", MB_OK | MB_ICONERROR);
        }
    }

    ~SandBoxApp() {
        Luxon::Function::Rendering::Renderer::Shutdown();
    }

    void OnUpdate() {
        Luxon::Core::Time::Timestep ts = Luxon::Core::Time::Time::GetDeltaTime();

        // 逻辑更新 (移动和碰撞)
        Luxon::Core::Math::Vector2f direction = { 0.0f, 0.0f };
        if (Luxon::Function::Input::Input::IsKeyPressed('W')) direction.y = -1.0f;
        if (Luxon::Function::Input::Input::IsKeyPressed('S')) direction.y = 1.0f;
        if (Luxon::Function::Input::Input::IsKeyPressed('A')) {
            direction.x = -1.0f;
            m_IsFacingRight = false;
        }

        if (Luxon::Function::Input::Input::IsKeyPressed('D')) {
            direction.x = 1.0f;
            m_IsFacingRight = true;
        }

        m_IsMoving = direction.LengthSquared() > 0.0f;

        if (m_IsMoving) {
            direction.Normalize();
        }

        float speed = 500.0f;
        m_RectPosition += direction * speed * ts;
        // 状态机和动画更新
        if (m_AnimationSet) {
            m_FSM.Update(m_Animator, *m_AnimationSet, { {"isMoving", m_IsMoving} });
        }
        m_Animator.Update(ts);

        // 碰撞检测 
        const auto* currentFrame = m_Animator.GetCurrentFrame();
        if (currentFrame) {
            m_RectPosition = Luxon::Function::Physics::Collision::CheckWindowCollision(
                m_RectPosition,
                { (float)currentFrame->SourceSize.x, (float)currentFrame->SourceSize.y },
                *m_Window
            );
        }
    }
    void OnRender() {
        // 渲染
        Luxon::Function::Rendering::Renderer::BeginScene();
        Luxon::Function::Rendering::Renderer::SetClearColor({ 30,30,30,255 });
        Luxon::Function::Rendering::Renderer::Clear();

        if (m_Texture) {
            // 从动画控制器获取当前应该画哪一帧
            const auto* currentFrame = m_Animator.GetCurrentFrame();
            if (currentFrame) {
                // 调用升级后的 DrawSubTexture 函数
                Luxon::Function::Rendering::Renderer::DrawSubTexture(
                    (int)m_RectPosition.x, (int)m_RectPosition.y,
                    *m_Texture,
                    currentFrame->SourcePos,
                    currentFrame->SourceSize,
                    !m_IsFacingRight);
            }
        }

        Luxon::Function::Rendering::Renderer::EndScene();
    }

    void Run() {
        bool running = true;
        MSG msg = {};

        while (running) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) running = false;
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                Luxon::Core::Time::Time::Tick();
                OnUpdate(); 
                OnRender();
            }
        }
    }

private:
    std::unique_ptr<Luxon::Platform::Window> m_Window;
    Luxon::Core::Math::Vector2f m_RectPosition = { 100.0f, 100.0f };
    // 精灵图以及解析后的动画数据
    std::shared_ptr<Luxon::Resource::Texture> m_Texture;
    std::shared_ptr<Luxon::Function::Animation::AnimationSet> m_AnimationSet;
    // 动画控制器
    Luxon::Function::Animation::Animator m_Animator;
    Luxon::Function::Animation::AnimationStateMachine m_FSM;
    bool m_IsMoving = false; // 用于状态机判断的标志
    bool m_IsFacingRight = true;

};

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
    SandBoxApp* app = new SandBoxApp();
    app->Run();
    delete app;
    return 0;
}