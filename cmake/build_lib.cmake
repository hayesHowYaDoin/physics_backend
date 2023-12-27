function(build_physics_backend)
    message("Building physics_backend...")

    add_library(physics_backend INTERFACE)

    add_subdirectory(${CMAKE_SOURCE_DIR}/src)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs)

    target_include_directories(physics_backend 
        INTERFACE
            ${CMAKE_SOURCE_DIR}/src
    )

    find_package(SFML 2.5 REQUIRED COMPONENTS network audio graphics window system)

    # Silence warnings from libraries
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(units INTERFACE -w)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(units INTERFACE /w)
    endif()

    target_link_libraries(physics_backend
        INTERFACE
            units::units
            sfml-system
            sfml-window
            sfml-graphics
    )
            
endfunction()
