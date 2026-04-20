add_executable(ThirdPersonSandbox
    src/main.cpp
)

target_link_libraries(ThirdPersonSandbox
    PRIVATE
        FullGame::Engine
)

if (WIN32)
    set_target_properties(ThirdPersonSandbox PROPERTIES WIN32_EXECUTABLE ON)
endif()
