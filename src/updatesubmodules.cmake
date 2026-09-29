set(GITMODULES_FILE "${CMAKE_CURRENT_LIST_DIR}/../.gitmodules")

if(NOT EXISTS "${GITMODULES_FILE}")
message(STATUS "No .gitmodules file found; skipping submodule update.")
return()
endif()

file(STRINGS "${GITMODULES_FILE}" GITMODULES_LINES)

set(SUBMODULE_PATH "")
set(SUBMODULE_URL "")

foreach(LINE IN LISTS GITMODULES_LINES)
if(LINE MATCHES "^\[submodule "([^"]+)"\]")
set(SUBMODULE_PATH "")
set(SUBMODULE_URL "")
elseif(LINE MATCHES "^[ \t]+path = (.+)")
set(SUBMODULE_PATH "${CMAKE_MATCH_1}")
elseif(LINE MATCHES "^[ \t]+url = (.+)")
set(SUBMODULE_URL "${CMAKE_MATCH_1}")
endif()

if(NOT "${SUBMODULE_PATH}" STREQUAL "" AND
   NOT "${SUBMODULE_URL}" STREQUAL "")

    set(SUBMODULE_DIRECTORY
        "${CMAKE_CURRENT_LIST_DIR}/../${SUBMODULE_PATH}"
    )

    if(EXISTS "${SUBMODULE_DIRECTORY}/.git")
        message(STATUS "Updating submodule: ${SUBMODULE_PATH}")

        execute_process(
            COMMAND git -C "${SUBMODULE_DIRECTORY}" pull
            RESULT_VARIABLE GIT_RESULT
        )
    else()
        message(STATUS "Cloning submodule: ${SUBMODULE_PATH}")

        execute_process(
            COMMAND git clone "${SUBMODULE_URL}" "${SUBMODULE_DIRECTORY}"
            RESULT_VARIABLE GIT_RESULT
        )
    endif()

    if(NOT GIT_RESULT EQUAL 0)
        message(FATAL_ERROR
            "Failed to update submodule: ${SUBMODULE_PATH}"
        )
    endif()

    set(SUBMODULE_PATH "")
    set(SUBMODULE_URL "")
endif()

endforeach()
