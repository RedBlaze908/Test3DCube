#pragma once

struct Vec3D { float x, y, z; };

sf::Vector2f project(const Vec3D& point, float width, float height, float fov, float distance) {
    float factor = fov / (distance + point.z);
    float x2d = point.x * factor + width / 2;
    float y2d = -point.y * factor + height / 2;
    return sf::Vector2f(x2d, y2d);
}


// ##### Rotate Functions #####

Vec3D rotateX(const Vec3D& point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    return { point.x, point.y * cosA - point.z * sinA, point.y * sinA + point.z * cosA };
}

Vec3D rotateY(const Vec3D& point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    return { point.x * cosA + point.z * sinA, point.y, -point.x * sinA + point.z * cosA };
}

Vec3D rotateZ(const Vec3D& point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);
    return { point.x * cosA - point.y * sinA, point.x * sinA + point.y * cosA, point.z };
}