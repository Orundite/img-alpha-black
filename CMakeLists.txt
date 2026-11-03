cmake_minimum_required(VERSION 3.30)

project(img-alpha-black LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Объявляем зависимость stb с официального GitHub автора
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG        master # Или укажите конкретный хэш коммита для стабильности
)
# Скачиваем файлы (происходит на этапе конфигурирования CMake)
FetchContent_MakeAvailable(stb)

add_executable(img-alpha-black img-alpha-black.c)

if(UNIX)
    target_link_libraries(img-alpha-black PRIVATE m)
endif()

if(WIN32)
    if(MSVC)
        target_compile_options(img-alpha-black PRIVATE /utf-8)
    endif()
    if(MINGW)
    target_compile_options(img-alpha-black PRIVATE -municode)
    target_link_options(img-alpha-black PRIVATE -municode -mconsole)
endif()
endif()
target_include_directories(img-alpha-black PRIVATE ${stb_SOURCE_DIR})

add_custom_command(
    TARGET img-alpha-black POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
            "$<TARGET_FILE_DIR:img-alpha-black>/LICENSE"
    COMMENT "Copying LICENSE to the build directory..."
    VERBATIM
)

include(GNUInstallDirs)
install(TARGETS img-alpha-black
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES LICENSE 
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)