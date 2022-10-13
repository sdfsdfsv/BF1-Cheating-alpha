#ifndef _GAME_MATH_HPP
#define _GAME_MATH_HPP

/* Includes */
#include "Vec3.hpp"
#include "Vec2.hpp"
#include "Matrix4x4.hpp"
#include <cstdint>


/* 世界3维坐标转2维屏幕坐标 */
Vec2 W2S(Vec3 origin, Matrix4x4* view_Matrix4x4, uint64_t camera);

#endif 