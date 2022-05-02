IF (NOT SAMPLE)
	message(FATAL_ERROR "SAMPLE is not defined!")
ENDIF ()

IF(NOT SAMPLE_SRCFILES)
	SET(SAMPLE_SRCFILES main.cpp)
ENDIF()

add_executable(${SAMPLE} ${SAMPLE_SRCFILES})

TARGET_LINK_LIBRARIES(${SAMPLE} PRIVATE json-dto::json-dto)

IF (JSON_DTO_INSTALL_SAMPLES)
	install(TARGETS ${SAMPLE} DESTINATION bin)
endif ()
