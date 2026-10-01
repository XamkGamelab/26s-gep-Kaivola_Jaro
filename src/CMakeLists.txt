add_executable(gep
	main.cpp
	game.cpp
	input/InputManager.cpp
	time/TimeManager.cpp
)

target_compile_features(gep PRIVATE cxx_std_23)
target_link_libraries(gep PRIVATE
	SDL3::SDL3
	SDL3_image::SDL3_image
	GLAD
)

set(ASSETS_INPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/assets"
	CACHE STRING "Input directory of in-game assets" 
)

add_custom_target(CopyAssets
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${ASSETS_INPUT_DIRECTORY} $<TARGET_FILE_DIR:gep>/assets
)

add_dependencies(gep CopyAssets)