add_library(CExample SHARED examples/blank.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExample raylib)

add_library(CExampleSine SHARED examples/cube_sine.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExampleSine raylib)

add_library(CExampleBattary SHARED examples/battary.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExampleBattary raylib)

add_library(CExampleArray SHARED examples/array.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExampleArray raylib)