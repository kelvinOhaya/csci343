

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "*.cpp")

add_executable(
        main_app
        ${SRC_FILES}
)

# If you have libraries, use add_library() here.