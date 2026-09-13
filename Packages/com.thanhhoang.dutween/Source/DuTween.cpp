#include "DuTween.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

#include "DualityEngine/Scene/Components.h"
#include "DualityEngine/Scene/Scene.h"

namespace DuTween {
    namespace {
        enum class Property { Position, Scale, Rotation, Value };
        struct ActiveTween {
            TweenHandle Handle = InvalidTween;
            Duality::Entity Target;
            Property TargetProperty = Property::Position;
            glm::vec3 Start{};
            glm::vec3 End{};
            float Elapsed = 0.0f;
            float Duration = 0.0001f;
            float Delay = 0.0f;
            int RemainingLoops = 0;
            bool Yoyo = false;
            Ease Easing = Ease::OutQuad;
            std::function<void(float)> ValueSetter;
            std::function<void()> Completion;
        };
        std::vector<ActiveTween> s_Tweens;
        TweenHandle s_NextHandle = 1;

        float EaseValue(Ease ease, float t) {
            t = glm::clamp(t, 0.0f, 1.0f);
            switch (ease) {
            case Ease::InQuad: return t * t;
            case Ease::OutQuad: return 1.0f - (1.0f - t) * (1.0f - t);
            case Ease::InOutQuad: return t < 0.5f ? 2.0f * t * t : 1.0f - std::pow(-2.0f * t + 2.0f, 2.0f) * 0.5f;
            case Ease::InCubic: return t * t * t;
            case Ease::OutCubic: return 1.0f - std::pow(1.0f - t, 3.0f);
            case Ease::OutBack: {
                constexpr float c1 = 1.70158f, c3 = c1 + 1.0f;
                const float p = t - 1.0f;
                return 1.0f + c3 * p * p * p + c1 * p * p;
            }
            case Ease::OutBounce: {
                constexpr float n1 = 7.5625f, d1 = 2.75f;
                if (t < 1.0f / d1) return n1 * t * t;
                if (t < 2.0f / d1) { t -= 1.5f / d1; return n1 * t * t + 0.75f; }
                if (t < 2.5f / d1) { t -= 2.25f / d1; return n1 * t * t + 0.9375f; }
                t -= 2.625f / d1; return n1 * t * t + 0.984375f;
            }
            default: return t;
            }
        }

        ActiveTween* Find(TweenHandle handle) {
            auto found = std::find_if(s_Tweens.begin(), s_Tweens.end(), [handle](const ActiveTween& tween) { return tween.Handle == handle; });
            return found == s_Tweens.end() ? nullptr : &*found;
        }
        TweenHandle NextHandle() { const TweenHandle result = s_NextHandle++; return result == InvalidTween ? s_NextHandle++ : result; }

        TweenHandle AddTransformTween(Duality::Entity target, Property property, const glm::vec3& start,
            const glm::vec3& end, float duration, Ease ease) {
            if (!target || !target.HasComponent<Duality::TransformComponent>()) return InvalidTween;
            ActiveTween tween;
            tween.Handle = NextHandle(); tween.Target = target; tween.TargetProperty = property;
            tween.Start = start; tween.End = end; tween.Duration = std::max(0.0001f, duration); tween.Easing = ease;
            s_Tweens.push_back(std::move(tween));
            return s_Tweens.back().Handle;
        }
        void Apply(ActiveTween& tween, float progress) {
            const glm::vec3 value = glm::mix(tween.Start, tween.End, EaseValue(tween.Easing, progress));
            if (tween.TargetProperty == Property::Value) { if (tween.ValueSetter) tween.ValueSetter(value.x); return; }
            if (!tween.Target || !tween.Target.HasComponent<Duality::TransformComponent>()) return;
            auto& transform = tween.Target.GetComponent<Duality::TransformComponent>();
            if (tween.TargetProperty == Property::Position) transform.Translation = value;
            else if (tween.TargetProperty == Property::Scale) transform.Scale = value;
            else if (tween.TargetProperty == Property::Rotation) transform.Rotation = value;
        }
        void RemoveAt(size_t index, bool complete) {
            ActiveTween tween = std::move(s_Tweens[index]);
            if (complete) Apply(tween, 1.0f);
            s_Tweens[index] = std::move(s_Tweens.back());
            s_Tweens.pop_back();
            if (tween.Completion) tween.Completion();
        }
    }

    TweenHandle Tween::MoveTo(Duality::Entity target, const glm::vec3& destination, float duration, Ease ease) {
        return target && target.HasComponent<Duality::TransformComponent>() ? AddTransformTween(target, Property::Position, target.GetComponent<Duality::TransformComponent>().Translation, destination, duration, ease) : InvalidTween;
    }
    TweenHandle Tween::MoveTo2D(Duality::Entity target, const glm::vec2& destination, float duration, Ease ease) {
        if (!target || !target.HasComponent<Duality::TransformComponent>()) return InvalidTween;
        glm::vec3 end = target.GetComponent<Duality::TransformComponent>().Translation;
        end.x = destination.x; end.y = destination.y;
        return MoveTo(target, end, duration, ease);
    }
    TweenHandle Tween::ScaleTo(Duality::Entity target, const glm::vec3& destination, float duration, Ease ease) {
        return target && target.HasComponent<Duality::TransformComponent>() ? AddTransformTween(target, Property::Scale, target.GetComponent<Duality::TransformComponent>().Scale, destination, duration, ease) : InvalidTween;
    }
    TweenHandle Tween::RotateTo(Duality::Entity target, const glm::vec3& destination, float duration, Ease ease) {
        return target && target.HasComponent<Duality::TransformComponent>() ? AddTransformTween(target, Property::Rotation, target.GetComponent<Duality::TransformComponent>().Rotation, destination, duration, ease) : InvalidTween;
    }
    TweenHandle Tween::Value(float from, float to, float duration, std::function<void(float)> setter, Ease ease) {
        if (!setter) return InvalidTween;
        ActiveTween tween;
        tween.Handle = NextHandle(); tween.TargetProperty = Property::Value; tween.Start.x = from; tween.End.x = to;
        tween.Duration = std::max(0.0001f, duration); tween.Easing = ease; tween.ValueSetter = std::move(setter);
        s_Tweens.push_back(std::move(tween)); return s_Tweens.back().Handle;
    }
    bool Tween::SetDelay(TweenHandle handle, float seconds) { if (auto* tween = Find(handle)) { tween->Delay = std::max(0.0f, seconds); return true; } return false; }
    bool Tween::SetLoops(TweenHandle handle, int loops, bool yoyo) { if (auto* tween = Find(handle)) { tween->RemainingLoops = loops < 0 ? -1 : loops; tween->Yoyo = yoyo; return true; } return false; }
    bool Tween::OnComplete(TweenHandle handle, std::function<void()> callback) { if (auto* tween = Find(handle)) { tween->Completion = std::move(callback); return true; } return false; }
    bool Tween::IsPlaying(TweenHandle handle) { return Find(handle) != nullptr; }
    void Tween::Kill(TweenHandle handle, bool complete) { for (size_t i = 0; i < s_Tweens.size(); ++i) if (s_Tweens[i].Handle == handle) { RemoveAt(i, complete); return; } }
    void Tween::KillTarget(Duality::Entity target, bool complete) { for (size_t i = 0; i < s_Tweens.size();) if (s_Tweens[i].Target == target) RemoveAt(i, complete); else ++i; }
    void Tween::Clear() { s_Tweens.clear(); }
    void Tween::Update(float deltaTime) {
        deltaTime = std::max(0.0f, deltaTime);
        for (size_t i = 0; i < s_Tweens.size();) {
            ActiveTween& tween = s_Tweens[i]; float tweenDelta = deltaTime;
            if (tween.TargetProperty != Property::Value && (!tween.Target || !tween.Target.HasComponent<Duality::TransformComponent>())) { RemoveAt(i, false); continue; }
            if (tween.Delay > 0.0f) { tween.Delay -= tweenDelta; if (tween.Delay > 0.0f) { ++i; continue; } tweenDelta = -tween.Delay; tween.Delay = 0.0f; }
            tween.Elapsed += tweenDelta; Apply(tween, tween.Elapsed / tween.Duration);
            if (tween.Elapsed < tween.Duration) { ++i; continue; }
            if (tween.RemainingLoops == 0) { RemoveAt(i, false); continue; }
            if (tween.RemainingLoops > 0) --tween.RemainingLoops;
            tween.Elapsed = 0.0f;
            if (tween.Yoyo) std::swap(tween.Start, tween.End); else Apply(tween, 0.0f);
            ++i;
        }
    }
}
