cmake_minimum_required(VERSION 3.14)
project(ArtemisExercise)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCE_FILES
        src/Game.cpp
        src/CLI.cpp
        src/Interface.cpp
        src/HardGame.cpp
        src/EasyGame.cpp
        src/NormalGame.cpp
        src/Checker.cpp
        src/Utils.cpp
        src/Wordle.cpp
        include/IGameData.h
        src/GameFactory.cpp
        src/GameManager.cpp
        src/GameStatistics.cpp
        src/WordleSolver.cpp
)
# Library
add_library(assignment ${SOURCE_FILES})
target_include_directories(assignment PUBLIC include data)

include_directories(include)

# Main executable
add_executable(assignment_main src/Main.cpp)
target_link_libraries(assignment_main assignment)



##########################################################
### Um die Tests lokal auszuführen, Kommentare vor den folgenden Zeilen entfernen
##########################################################
#[[

include(FetchContent)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.11.0
        GIT_CONFIG http.sslVerify=false
)
FetchContent_MakeAvailable(catch2)


add_executable(assignment_tests ${SOURCE_FILES}
        tests/CheckerTest.cpp
        tests/NormalGameTest.cpp
        tests/HardGameTest.cpp
        tests/EasyGameTest.cpp
        tests/WordleTest.cpp
        tests/InterfaceTests.cpp
        tests/GameStatisticsTest.cpp
        tests/WordleSolverTests.cpp
)
target_link_libraries(assignment_tests Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(assignment_tests)
enable_testing()
include(CTest)
]]#