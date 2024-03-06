# nlohmann::json
project(json VERSION 3.11.3 LANGUAGES CXX)
set(PROJECT_HOMEPAGE_URL https://github.com/nlohmann/json.git)
set(PROJECT_VERSION_PREFIX v)

if (NOT TARGET ${PROJECT_NAME})
    include(FetchContent)

    FetchContent_Declare(
            ${PROJECT_NAME}
            GIT_REPOSITORY ${PROJECT_HOMEPAGE_URL}
            GIT_TAG ${PROJECT_VERSION_PREFIX}${PROJECT_VERSION}
    )

    FetchContent_GetProperties(${PROJECT_NAME})
    if(NOT ${PROJECT_NAME}_POPULATED)
        FetchContent_Populate(${PROJECT_NAME})
        add_subdirectory(${${PROJECT_NAME}_SOURCE_DIR} ${${PROJECT_NAME}_BINARY_DIR})
    endif()
endif (NOT TARGET ${PROJECT_NAME})