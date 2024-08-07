
PROJECT(govee LANGUAGES CXX)
add_library(${PROJECT_NAME} STATIC
        govee.cpp
        govee.h
        goveeDevice.cpp
        goveeDevice.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt6::Core
        Qt6::Network
        nlohmann_json::nlohmann_json
)