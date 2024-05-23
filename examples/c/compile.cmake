add_library(CExample SHARED examples/c/blank.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExample raylib ${PYTHON_LIBRARY})
target_include_directories(CExample PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CExampleSine SHARED examples/c/cube_sine.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExampleSine raylib ${PYTHON_LIBRARY})
target_include_directories(CExampleSine PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CExampleBattary SHARED examples/c/battary.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExampleBattary raylib ${PYTHON_LIBRARY})
target_include_directories(CExampleBattary PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CExampleArray SHARED examples/c/array.c api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CExampleArray raylib ${PYTHON_LIBRARY})
target_include_directories(CExampleArray PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CExampleKeyfames SHARED examples/c/keyframes.c api/raylib_ref.h api/api.h api/api.cpp api/animation.cpp)
target_link_libraries(CExampleKeyfames raylib ${PYTHON_LIBRARY})
target_include_directories(CExampleKeyfames PRIVATE ${PYTHON_INCLUDE_DIRS})