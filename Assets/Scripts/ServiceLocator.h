#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>

class ServiceLocator
{
public:
    template<typename T>
    static void Register(std::shared_ptr<T> service)
    {
        services[typeid(T)] = service;
    }

    template<typename T>
    static T& Get()
    {
        auto it = services.find(typeid(T));

        if (it == services.end())
            throw std::runtime_error("Service not registered");

        return *std::static_pointer_cast<T>(it->second);
    }

    template<typename T>
    static bool Has()
    {
        return services.contains(typeid(T));
    }

    template<typename T>
    static void Remove()
    {
        services.erase(typeid(T));
    }

    static void Clear()
    {
        services.clear();
    }

private:
    inline static std::unordered_map<
        std::type_index,
        std::shared_ptr<void>
    > services;
};