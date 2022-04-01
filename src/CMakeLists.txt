project(structures)

set(HEADER_FILES
        Array.h
        Iterator.h
        String.h
        Vector.h
        VectorHelpers.h
        )
set(SOURCE_FILES
        main.cpp
        ${HEADER_FILES}
        )

add_executable(structures_executable ${SOURCE_FILES})
target_precompile_headers(structures_executable PRIVATE pch.h)
