FIND_PACKAGE(SiconosMechanics REQUIRED)
INCLUDE_DIRECTORIES(${SiconosMechanics_INCLUDE_DIRS})
LINK_DIRECTORIES(${SiconosMechanics_LIBRARY_DIRS})
LIST(APPEND PROJECT_LINK_LIBRARIES ${SiconosMechanics_LIBRARIES})
