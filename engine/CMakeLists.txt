set(ENGINE_SOURCES
    src/Core/Application.cpp
    src/Core/Logger.cpp
    src/Platform/Window.cpp
    src/Input/InputSystem.cpp
    src/Math/MathTypes.cpp
    src/Render/VulkanRenderer.cpp
    src/Scene/DebugCamera.cpp
)

add_library(CustomEngine STATIC ${ENGINE_SOURCES})

add_library(FullGame::Engine ALIAS CustomEngine)

target_include_directories(CustomEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(CustomEngine
    PUBLIC
        glfw
        Vulkan::Vulkan
)

target_compile_definitions(CustomEngine
    PRIVATE
        GLFW_INCLUDE_NONE
)

if (MSVC)
    target_compile_options(CustomEngine PRIVATE /W4 /permissive-)
else()
    target_compile_options(CustomEngine PRIVATE -Wall -Wextra -Wpedantic)
endif()
