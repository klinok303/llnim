add_library(CPPExample SHARED examples/cpp/blank.cpp api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CPPExample raylib ${PYTHON_LIBRARY})
target_include_directories(CPPExample PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CPPExampleSine SHARED examples/cpp/cube_sine.cpp api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CPPExampleSine raylib ${PYTHON_LIBRARY})
target_include_directories(CPPExampleSine PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CPPExampleBattary SHARED examples/cpp/battary.cpp api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CPPExampleBattary raylib ${PYTHON_LIBRARY})
target_include_directories(CPPExampleBattary PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CPPExampleArray SHARED examples/cpp/array.cpp api/raylib_ref.h api/api.h api/api.cpp)
target_link_libraries(CPPExampleArray raylib ${PYTHON_LIBRARY})
target_include_directories(CPPExampleArray PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(CPPExampleKeyfames SHARED examples/cpp/keyframes.cpp api/raylib_ref.h api/api.h api/api.cpp api/animation.cpp)
target_link_libraries(CPPExampleKeyfames raylib ${PYTHON_LIBRARY})
target_include_directories(CPPExampleKeyfames PRIVATE ${PYTHON_INCLUDE_DIRS})