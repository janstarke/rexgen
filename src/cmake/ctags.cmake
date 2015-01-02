# inspired by http://stackoverflow.com/questions/9827208/run-a-shell-command-ctags-in-cmake-and-make
set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(tags
    COMMAND ctags -e -R --c++-kinds=+p --fields=+iaS --extra=+q .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_dependencies(rexgen tags)
