// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Object.hpp"

tnt::Object::Object(Vector p, float angl, Vector scal)
    : pos{p}, angle{angle}, scale{scal}, parent{nullptr} {}

tnt::Object::~Object() noexcept
{
    parent = nullptr; // should this be like this? We don't want do delete the parent, just the pointer.
}

void tnt::Object::setAngle(float a) noexcept { angle = a; }

float tnt::Object::getAngle() const noexcept { return angle; }

void tnt::Object::setScale(Vector s) noexcept { scale = s; }
tnt::Vector tnt::Object::getScale() const noexcept { return scale; }

void tnt::Object::setPosition(Vector p) noexcept { pos = p; }
tnt::Vector tnt::Object::getPosition() const noexcept { return pos; }

void tnt::Object::setParent(Object *obj) noexcept { parent = obj; }
tnt::Object *tnt::Object::getParent() const noexcept { return parent; }

void tnt::Object::Rotate(float rad) noexcept { angle += rad; }
void tnt::Object::Scale(Vector s) noexcept { scale = {scale.x * s.x, scale.y = s.y}; }
void tnt::Object::Transform(Vector p) noexcept { pos += p; }