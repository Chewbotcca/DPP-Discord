cmake_minimum_required(VERSION 3.21)
# Project name, version and description
project(discord-bot VERSION 1.0 DESCRIPTION "A discord bot")

set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl")
set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
set(OPENSSL_CRYPTO_LIBRARY /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib)
set(OPENSSL_SSL_LIBRARY /opt/homebrew/opt/openssl@3/lib/libssl.dylib)

# Add DPP as dependency
add_subdirectory(libs/DPP)
#add_subdirectory(libs/spdlog) # if you need a logger. Don't forget to clone sources
# in the `libs/` directory

file(GLOB MY_FILES "src/*.txt")
file(COPY ${MY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Create an executable
add_executable(${PROJECT_NAME}
        src/main.cpp
        # your others files...
)

# Linking libraries
target_link_libraries(${PROJECT_NAME}
        dpp
#        spdlog # Like before, if you need spdlog
)

# Specify includes
target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
#        libs/spdlog/include # Like before, if you need spdlog
)

# Set C++ version
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17 # or 20 if you want something more recent
        CXX_STANDARD_REQUIRED ON
)