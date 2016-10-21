cmake_minimum_required(VERSION 2.8)

add_definitions(--std=c++11)

# Set up your project name.
project(Invaders_Reinc)

# Set up the main source folder.
set(SOURCE_ROOT src)
# To display subfolder and its content in QT Creator.
set(S_SOURCE_ROOT src/gameclasses)
aux_source_directory(${S_SOURCE_ROOT} SRC_LIST)
# Scan source folder to find all sources and put the result to SRC_LIST.
aux_source_directory(${SOURCE_ROOT} SRC_LIST)
# Create executable by SRC_LIST.
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Add subdirectory with Google Test Library.
add_subdirectory(3party/googletest)

# Enable unit testing.
enable_testing()
# Set up testing project name.
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
# Add include directories for testing project.
include_directories(3party/googletest/googletest/include ${SOURCE_ROOT})
# Set up testing project.
set(TESTS_SOURCE_ROOT tests)
# To display tests subfolder and its content in QT Creator.
set(T_S_SOURCE_ROOT tests/gameclasses_tests)
aux_source_directory(${T_S_SOURCE_ROOT} TEST_SRC_FILES)
# Scan folder to find all test sources and put the result to TEST_SRC_FILES.
aux_source_directory(${TESTS_SOURCE_ROOT} TEST_SRC_FILES)
set(TEST_SRC_FILES ${SRC_LIST} ${TEST_SRC_FILES})
list(REMOVE_ITEM TEST_SRC_FILES src/main.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
# Link gtest and gtest_main libraries.
target_link_libraries(${PROJECT_TEST_NAME} gtest gtest_main)
# Finish tests setting up.
add_test(test ${PROJECT_TEST_NAME})
