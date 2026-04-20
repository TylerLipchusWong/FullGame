add_executable(ThirdPersonSandbox
    src/main.cpp
)

target_link_libraries(ThirdPersonSandbox
    PRIVATE
        FullGame::Engine
)
