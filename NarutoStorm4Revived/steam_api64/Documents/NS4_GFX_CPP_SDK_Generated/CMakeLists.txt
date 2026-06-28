cmake_minimum_required(VERSION 3.10)
project(NS4GFXCppSDK LANGUAGES CXX)
add_library(NS4GFXCppSDK STATIC
    src/ASSymbolRegistry.cpp
    src/GfxBridge.cpp
    src/GeneratedCategories.cpp
    src/CustomUI.cpp
)
target_include_directories(NS4GFXCppSDK PUBLIC include)
target_compile_features(NS4GFXCppSDK PUBLIC cxx_std_11)
