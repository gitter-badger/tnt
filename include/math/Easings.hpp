#ifndef TNT_EASINGS_HPP
#define TNT_EASINGS_HPP

#include <cmath>
#include "math/GenericMath.hpp"

// NOTE: if any undesired effect happens, consider changing math functions like
// sinf, powf, etc... to normal form(e. sinf to sin).

namespace tnt
{
    inline constexpr float PennerNumber{1.70158f};

    namespace back
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            time /= duration;
            return change * time * time *
                       ((PennerNumber + 1) * time - PennerNumber) +
                   begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            time = time / duration - 1;
            return change * (time * time *
                                 ((PennerNumber + 1) * time + PennerNumber) +
                             1) +
                   begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            float s = PennerNumber * 1.525f;
            if ((time /= duration / 2) < 1)
                return change / 2 * (time * time * ((s + 1.f) * time - s)) +
                       begin;
            time -= 2;
            return change / 2 * (time * time * ((s + 1.f) * time + s) + 2) +
                   begin;
        }
    } // namespace back

    namespace bounce
    {
        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            if ((time /= duration) < (1 / 2.75f))
                return change * (7.5625f * time * time) + begin;
            else if (time < (2 / 2.75f))
            {
                time -= (1.5f / 2.75f);
                return change * (7.5625f * time * time + .75f) + begin;
            }
            else if (time < (2.5f / 2.75f))
            {
                time -= (2.25f / 2.75f);
                return change * (7.5625f * time * time + .9375f) + begin;
            }
            else
            {
                time -= (2.625f / 2.75f);
                return change * (7.5625f * time * time + .984375f) + begin;
            }
        }

        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            return change - EaseOut(duration - time, 0, change, duration) +
                   begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if (time < duration / 2)
                return EaseIn(time * 2, 0, change, duration) * .5f + begin;
            else
                return EaseOut(time * 2 - duration, 0, change, duration) * .5f +
                       change * .5f + begin;
        }
    } // namespace bounce

    namespace circular
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            time /= duration;
            return -change * (sqrtf(1 - time * time) - 1) + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            time = time / duration - 1.f;
            return change * sqrtf(1 - time * time) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if ((time /= duration / 2) < 1)
                return -change / 2 * (sqrtf(1 - time * time) - 1) + begin;
            else
                return change / 2 * (sqrtf(1 - time * (time -= 2)) + 1) + begin;
        }
    } // namespace circular

    namespace cubic
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            time /= duration;
            return change * time * time * time + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            time = time / duration - 1.f;
            return change * (time * time * time + 1) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if ((time /= duration / 2) < 1)
                return change / 2 * time * time * time + begin;
            else
            {
                time -= 2;
                return change / 2 * (time * time * time + 2) + begin;
            }
        }
    } // namespace cubic

    namespace elastic
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            if (time == 0)
                return begin;
            if ((time /= duration) == 1)
                return begin + change;
            float p = duration * .3f;
            float s = p / 4;
            time -= 1;
            return -(change * powf(2, 10 * time) *
                     sinf((time * duration - s) * (2 * PI) / p)) +
                   begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            if (time == 0)
                return begin;
            if ((time /= duration) == 1)
                return begin + change;
            float p = duration * .3f;
            float s = p / 4;
            return (change * powf(2, -10 * time) *
                        sinf((time * duration - s) * (2 * PI) / p) +
                    change + begin);
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if (time == 0)
                return begin;
            if ((time /= duration / 2) == 2)
                return begin + change;
            float p = duration * (.3f * 1.5f);
            float s = p / 4.f;
            if (time < 1)
            {
                time -= 1;
                return -.5f * (change * powf(2, 10 * time) *
                               sinf((time * duration - s) * (2 * PI) / p)) +
                       begin;
            }
            time -= 1;
            return change * powf(2, -10 * time) *
                       sinf((time * duration - s) * (2 * PI) / p) * .5f +
                   change + begin;
        }
    } // namespace elastic

    namespace exponential
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            if (time == 0)
                return begin;
            else
                return change * powf(2, 10 * (time / duration - 1)) + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            if (fabs(time - duration) < 1e-11)
                return begin + change;
            else
                return change * (-powf(2, -10 * time / duration) + 1) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if (time == 0)
                return begin;
            if (fabs(time - duration) < 1e-11)
                return change;
            if ((time /= duration / 2) < 1)
                return change / 2 * powf(2, 10 * (time - 1)) + begin;
            return change / 2 * (-powf(2, -10 * (--time)) + 2) + begin;
        }
    } // namespace exponential

    namespace linear
    {
        inline float NoEase(float time, float begin, float change,
                            float duration)
        {
            return change * time / duration + begin;
        }

        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            return change * time / duration + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            return change * time / duration + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            return change * time / duration + begin;
        }
    } // namespace linear

    namespace quad
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            time /= duration;
            return change * time * time + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            time /= duration;
            return -change * time * (time - 2) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if ((time /= duration / 2) < 1)
                return ((change / 2) * (time * time)) + begin;
            else
                return ((-change / 2) * (((time - 2) * (time - 1)) - 1) +
                        begin);
        }
    } // namespace quad

    namespace quart
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            time /= duration;
            return change * time * time * time * time + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            time = time / duration - 1;
            return -(change * (time * time * time * time - 1)) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if ((time /= duration / 2) < 1)
                return change / 2 * time * time * time * time + begin;
            else
            {
                time -= 2;
                return -change / 2 * (time * time * time * time - 2) + begin;
            }
        }
    } // namespace quart

    namespace quint
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            time /= duration;
            return change * time * time * time * time * time + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            time = time / duration - 1;
            return change * (time * time * time * time * time + 1) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            if ((time /= duration / 2) < 1)
                return change / 2 * time * time * time * time * time + begin;
            else
            {
                time -= 2;
                return change / 2 * (time * time * time * time * time + 2) +
                       begin;
            }
        }
    } // namespace quint

    namespace sine
    {
        inline float EaseIn(float time, float begin, float change,
                            float duration)
        {
            return -change * cosf(time / duration * (PI / 2)) + begin;
        }

        inline float EaseOut(float time, float begin, float change,
                             float duration)
        {
            return -change * sinf(time / duration * (PI / 2)) + begin;
        }

        inline float EaseInOut(float time, float begin, float change,
                               float duration)
        {
            return -change / 2 * (cosf(PI * time / duration) - 1) + begin;
        }
    } // namespace sine
} // namespace tnt

#endif //! TNT_EASINGS_HPP