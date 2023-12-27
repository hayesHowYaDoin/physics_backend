function(build_simulations)
    message("Building simulation...")

    add_executable(physics_simulation)

    add_subdirectory(apps)
    
    find_package(SFML 2.5 REQUIRED COMPONENTS network audio graphics window system)

    target_link_libraries(physics_simulation
    PRIVATE
        physics_backend
        sfml-system
        sfml-window
        sfml-graphics
    )

endfunction()