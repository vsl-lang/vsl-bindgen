# Reccomended to use the Makefile normally but this is tested to work anyways so
# yeah

project(vsl-bindgen)
cmake_minimum_required(VERSION 3.5.2)

# Set C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# To avoid major borks
add_definitions(-Wall)

# Locate llvm-config because of course building C++ can never be easy
set(llvm_config_names llvm-config-5.0 llvm-config50
                      llvm-config-4.0 llvm-config40
                      llvm-config-3.9 llvm-config39
                      llvm-config-3.8 llvm-config38
                      llvm-config-3.7 llvm-config37
                      llvm-config-3.6 llvm-config36
                      llvm-config-3.5 llvm-config35
                      llvm-config)
find_program(LLVM_CONFIG NAMES ${llvm_config_names})

execute_process(
    COMMAND "${LLVM_CONFIG}" --cxxflags
    OUTPUT_VARIABLE LLVMCXX_FLAGS
)
message("Loaded with: ${LLVMCXX_FLAGS}")
add_definitions("${LLVMCXX_FLAGS}")

# Linking clang
# this does not actually specify the library to the linker that is done at the
# end
execute_process(
    COMMAND "${LLVM_CONFIG}" --libdir
    OUTPUT_VARIABLE LLVM_LIBRARY_DIR
)
find_library(LIBCLANG
    NAMES clang libclang
    PATHS "${LLVM_LIBRARY_DIR}"
)


# Get all files
file(GLOB CXX_FILES "src/*.cpp" "src/*.hpp")

add_executable(vsl-bindgen "${CXX_FILES}")
target_link_libraries(vsl-bindgen ${LIBCLANG})

# Installation for bindgen
install (TARGETS vsl-bindgen DESTINATION bin)
