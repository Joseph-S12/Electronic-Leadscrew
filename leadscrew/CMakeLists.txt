add_executable(main main.c)
target_link_libraries(main pico_stdlib)
target_link_libraries(main pico_multicore)
target_link_libraries(main pico_time)

pico_add_extra_outputs(main)
