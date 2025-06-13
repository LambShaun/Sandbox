/**
 * @file	Collision.h
 * @brief	游戏碰撞检测
 * @author	LambShaun
 **/

#pragma once

#include "Core/Math/Vec2D.h"
#include "Platform/Window.h"

namespace Luxon {
namespace Function {
namespace Physics {
	class Collision {
	public:
		// 静态函数：检查一个给定的矩形位置是否在窗口边界内，并返回修正后的位置
				// rectPos: 矩形当前的位置
				// rectSize: 矩形的大小
				// window: 游戏窗口的引用，用于获取边界
		static Core::Math::Vector2f CheckWindowCollision(
			const Core::Math::Vector2f& rectPos,
			const Core::Math::Vector2f& rectSize,
			const Platform::Window& window
		);	
	};
} // namespace Physics
} // namespace Function
} // namespace Luxon