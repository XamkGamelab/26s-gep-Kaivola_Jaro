# CMakeList.txt : CMake project for GameEngineTeht, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GameEngineTeht "GameEngineTeht.cpp" "GameEngineTeht.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameEngineTeht PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
