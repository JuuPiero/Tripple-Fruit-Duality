#pragma once

#include <cstdint>
#include <functional>

#include <glm/glm.hpp>

#include "DualityEngine/ECS/Entity.h"

namespace DuTween {
    using TweenHandle = uint32_t;
    constexpr TweenHandle InvalidTween = 0;

    enum class Ease { Linear, InQuad, OutQuad, InOutQuad, InCubic, OutCubic, OutBack, OutBounce };

    class Tween final {
    public:
        static TweenHandle MoveTo(Duality::Entity target, const glm::vec3& destination,
            float duration, Ease ease = Ease::OutQuad);
        static TweenHandle MoveTo2D(Duality::Entity target, const glm::vec2& destination,
            float duration, Ease ease = Ease::OutQuad);
        static TweenHandle ScaleTo(Duality::Entity target, const glm::vec3& destination,
            float duration, Ease ease = Ease::OutQuad);
        static TweenHandle RotateTo(Duality::Entity target, const glm::vec3& destinationDegrees,
            float duration, Ease ease = Ease::OutQuad);
        static TweenHandle Value(float from, float to, float duration,
            std::function<void(float)> setter, Ease ease = Ease::OutQuad);

        static bool SetDelay(TweenHandle handle, float delaySeconds);
        // extra repeats after the first pass; -1 loops forever.
        static bool SetLoops(TweenHandle handle, int additionalLoops, bool yoyo = false);
        static bool OnComplete(TweenHandle handle, std::function<void()> callback);
        static bool IsPlaying(TweenHandle handle);
        static void Kill(TweenHandle handle, bool complete = false);
        static void KillTarget(Duality::Entity target, bool complete = false);
        static void Clear();

        // DuTweenRunner calls this once every game frame.
        static void Update(float deltaTime);
    };
}
