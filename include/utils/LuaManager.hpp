#ifndef TNT_LUA_MANAGER_HPP
#define TNT_LUA_MANAGER_HPP

#include <span>
#include <sol/sol.hpp>

// TODO: register AND test all engine types and functions.
// TODO: Add support for .tmx maps and text on Lua's AssetManager when available.
// TODO: remove the need of passing a state on each argument.
// TODO: dissolve each one of these functions on the corresponding files.

// TODO(maybe):
// lib::CORE for window, input, timer ??

namespace tnt::lua
{
    enum class lib : uint32_t
    {
        MATH = 0u,
        TIMER,
        OBJECT,
        INPUT,
        WINDOW,
        IMGUI,
        CAMERA,
        SCENE,
        SPRITE_COMP,
        PHYS_COMP,
        UTILS,

        ALL
    };

    template <typename T>
    concept lua_lib = std::is_same_v<T, tnt::lua::lib>;

    void loadVector(sol::state_view lua_);           // done
    void loadRectangle(sol::state_view lua_);        // done
    void loadTimer(sol::state_view lua_);            // needs tests
    void loadObject(sol::state_view lua_);           // needs tests
    void loadInput(sol::state_view lua_);            // needs tests
    void loadWindow(sol::state_view lua_);           // needs test TODO(maybe): add more mebers functions
    void loadImGui(sol::state_view lua_);            // needs tests
    void loadSpace(sol::state_view lua_);            // needs tests
    void loadScene(sol::state_view lua_);            // needs tests
    void loadSpriteComp(sol::state_view lua_);       // TODO
    void loadPhysComp(sol::state_view lua_);         // TODO
    inline void loadCameras(sol::state_view lua_) {} // TODO
    void loadWidgets(sol::state_view lua_);          // TODO
    inline void loadUtils(sol::state_view lua_) {}   // last_write_time, etc
    // void loadAssetManager(sol::state const&lua_); // needs tests
    // void loadAudioPlayer(sol::state const&lua_); // needs tests
    // void loadSprite(sol::state const&lua_);      // TODO
    // void loadRigidBody(sol::state& lua_); // TODO

    /// @brief Load all binding functions that are NOT marked as TODO.
    void loadAll(sol::state_view lua_);

    void load(sol::state_view lua_, std::span<lua::lib> libs);
} // namespace tnt::lua

#endif //!TNT_LUA_MANAGER_HPP