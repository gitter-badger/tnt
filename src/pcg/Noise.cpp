// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "pcg/Noise.hpp"
#include "Random.hpp"
#include "utils/Logger.hpp"

#include <SDL2/SDL_render.h>

SDL_Texture *tnt::pcg::staticNoise(SDL_Renderer *ren, int w, int h)
{
    Uint32 format;
    SDL_Texture *ret{SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h)};
    SDL_QueryTexture(ret, &format, nullptr, nullptr, nullptr);

    SDL_PixelFormat pixelFmt;
    pixelFmt.format = format;

    Uint32 *pixels = new Uint32[w * h * 4];
    int pitch{0};
    if (SDL_LockTexture(ret, nullptr, (void **)&pixels, &pitch))
    {
        logger::debug("staticNoise couldn't lock texture!!\n Error: {}", SDL_GetError());
        return nullptr;
    }

    for (int i{0}; i < h; ++i)
        for (int j{0}; j < w; ++j)
        {
            uint8_t r{static_cast<Uint8>(randomValue(0, 255))};
            uint8_t g{static_cast<Uint8>(randomValue(0, 255))};
            uint8_t b{static_cast<Uint8>(randomValue(0, 255))};

            Uint32 color{SDL_MapRGB(&pixelFmt, r, g, b)};
            tnt::logger::debug("pitch: {}, i: {}, j: {}, color: {}\n", pitch, i, j, color);

            Uint32 pos{i * (pitch / sizeof(unsigned)) + j};
            pixels[pos] = color;
        }

    delete[] pixels;
    SDL_UnlockTexture(ret);
    return ret;
}