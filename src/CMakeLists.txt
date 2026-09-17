add_executable(gep
	main.cpp
	game.cpp
)

target_compile_features(gep PRIVATE cxx_std_23)
target_link_libraries(gep PRIVATE
	SDL3::SDL3
)