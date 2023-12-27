function(build_simulations)
    message("Building simulation...")

    add_executable(physics_simulation)

    add_subdirectory(apps)

    target_link_libraries(physics_simulation
    PRIVATE
        physics_backend
    )

endfunction()