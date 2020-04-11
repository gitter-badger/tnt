// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "ecs/Sprite.hpp"
#include "utils/Timer.hpp"
#include "core/Window.hpp"

tnt::Sprite::Sprite(Window const *win, std::string_view filename, float angle)
    : sprite{new SpriteComponent{win, filename}},
      rotate{new RotateComponent{angle}},
      scale{new ScaleComponent{VECTOR_ONE}}
{
    animations[filename.data()] = new AnimationComponent{
        win, filename, 1, 0.f, true,
        Rectangle{
            0.f, 0.f, static_cast<float>(sprite->getWidth()),
            static_cast<float>(sprite->getHeight())}};
}

tnt::Sprite::Sprite(Window const *win, std::string_view filename,
                    Rectangle const &area, float angle)
    : sprite{new SpriteComponent{win, filename, area}},
      rotate{new RotateComponent{angle}},
      scale{new ScaleComponent{VECTOR_ONE}}
{
    animations[filename.data()] = new AnimationComponent{
        win, filename, 1, 0.f, true, area};
}

tnt::Sprite::~Sprite() noexcept
{
    for (auto obj : animations)
        if (obj.second != nullptr)
        {
            delete obj.second;
            obj.second = nullptr;
        }

    animations.clear();
    std::map<std::string, AnimationComponent *>{}.swap(animations);

    delete sprite;
    sprite = nullptr;

    delete rotate;
    rotate = nullptr;

    delete scale;
    scale = nullptr;
}

tnt::RotateComponent *tnt::Sprite::getRotate() const noexcept { return rotate; }
tnt::ScaleComponent *tnt::Sprite::getScale() const noexcept { return scale; }
tnt::SpriteComponent *tnt::Sprite::getSprite() const noexcept { return sprite; }

void tnt::Sprite::playAnimation(std::string_view animation) noexcept
{
    animations[animation.data()]->update(timer);
    timer->reset();
}