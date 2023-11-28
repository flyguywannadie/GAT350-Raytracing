#pragma once
#include <glm/glm.hpp>

using color3_t = glm::vec3;
using color4_t = glm::vec4;
using rgba_t = uint32_t;

inline color4_t RGBAToColor(const rgba_t& rgba) {
	color4_t newColor{ 0 };

	newColor.r = ((rgba >> 24) & 0xff) / 255.0f;
	newColor.g = ((rgba >> 16) & 0xff) / 255.0f;
	newColor.b = ((rgba >> 8) & 0xff) / 255.0f;
	newColor.a = ((rgba) & 0xff) / 255.0f;

	return newColor;
}

inline rgba_t ColorToRGBA(const color4_t& color) {
	rgba_t newRGBA{ 0 };

	newRGBA |= ((uint8_t)(glm::clamp(color.r, 0.0f, 1.0f) * 255) << 24);
	newRGBA |= ((uint8_t)(glm::clamp(color.g, 0.0f, 1.0f) * 255) << 16);
	newRGBA |= ((uint8_t)(glm::clamp(color.b, 0.0f, 1.0f) * 255) << 8);
	newRGBA |= ((uint8_t)(glm::clamp(color.a, 0.0f, 1.0f) * 255));

	return newRGBA;
}