#pragma once

#include <vector>

enum class RuntimeFeatureState
{
    Active,
    Ready,
    Managed,
    Planned,
    NeedsPatch
};

struct RuntimeFeatureInfo
{
    const char* Category;
    const char* Name;
    RuntimeFeatureState State;
    const char* Detail;
};

namespace RuntimeFeatureRegistry
{
    const std::vector<RuntimeFeatureInfo>& Snapshot();
    const char* StateName(RuntimeFeatureState state);
    int CountByState(RuntimeFeatureState state);
    int CountAll();
}
