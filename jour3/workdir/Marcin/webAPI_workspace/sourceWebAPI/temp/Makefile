# Quick and ok!

ARCH?=x86-64

BINNAME=retinio_test
CXXFLAGS=-std=c++14 -DRESTINIO_USE_BOOST_ASIO=shared
LDDFLAGS=

# Debug build? debug is default
ifdef DEBUG
CXXFLAGS+=-g 
DEST_DIR=${ARCH}/debug
MODE=debug
else
CXXFLAGS+=-O2
DEST_DIR=${ARCH}/release
MODE=release
endif
OBJ_DEST_DIR=build/${DEST_DIR}
BIN_DEST_DIR=bin/${DEST_DIR}
LIB_DEST_DIR=lib/${DEST_DIR}

COMMON=$(wildcard *.cpp)
SRC=${COMMON} 
OBJS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.o}))
DEPS=$(addprefix ${OBJ_DEST_DIR}/,$(notdir ${SRC:%.cpp=%.d}))

ifeq (${ARCH},x86-64)
# Include x86-64 specific stuff
include compiler_setup.x86-64
endif

ifeq (${ARCH},arm)
# Include arm specific stuff
include compiler_setup.arm
endif

FMT_PACKAGE=../../fmt
FMT_PACKAGE_INC=${FMT_PACKAGE}/include
FMT_PACKAGE_LIBPATH=${FMT_PACKAGE}/${LIB_DEST_DIR}

HTTP_PARSER_PACKAGE=../../http-parser
HTTP_PARSER_PACKAGE_INC=${HTTP_PARSER_PACKAGE}
HTTP_PARSER_PACKAGE_LIB=${HTTP_PARSER_PACKAGE}/${LIB_DEST_DIR}

JSON_DTO_PACKAGE=../../json_dto
JSON_DTO_PACKAGE_INC=${JSON_DTO_PACKAGE}/dev

RAPIDJSON_PACKAGE=../../rapidjson
RAPIDJSON_PACKAGE_INC=${RAPIDJSON_PACKAGE}/include

RESTINIO_PACKAGE=../../restinio
RESTINIO_PACKAGE_INC=${RESTINIO_PACKAGE}

LIBS=-lfmt -lhttp_parser -lpthread
LIBPATHS=-L${FMT_PACKAGE_LIBPATH} -L${HTTP_PARSER_PACKAGE_LIB}

# Setting compiler flags
CXXFLAGS+= -Wall -Iinclude  -D${OS} -I${RESTINIO_PACKAGE_INC} -I${FMT_PACKAGE_INC} -I${HTTP_PARSER_PACKAGE_INC} -I${JSON_DTO_PACKAGE_INC} -I${RAPIDJSON_PACKAGE_INC}
VPATH=src

all: info ${BIN_DEST_DIR}/${BINNAME}

info:
	@echo "Compiling for '${ARCH}' in '${MODE}' mode..."

${OBJ_DEST_DIR}/%.o: %.cpp
	@echo "Compiling "$<
	@${CXX} -c $< -o $@ ${CXXFLAGS}

${OBJ_DEST_DIR}/%.d: %.cpp
	@echo "Generating dependency for $<"
	@mkdir -p ${OBJ_DEST_DIR}
	@$(CXX) -MT${OBJ_DEST_DIR}/$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

${BIN_DEST_DIR}:
	@mkdir -p ${BIN_DEST_DIR}

${OBJ_DEST_DIR}:
	@mkdir -p ${OBJ_DEST_DIR}

${BIN_DEST_DIR}/${BINNAME}: ${OBJ_DEST_DIR} ${BIN_DEST_DIR} $(DEPS) ${OBJS} 
	@echo "Linking "${BINNAME}
	@${CXX} -o $@ ${OBJS} ${LIBS} ${LIBPATHS}


clean:
	@echo "Cleaning up..."
	@rm -f ${BIN_DEST_DIR}/${BINNAME} $(OBJS) $(DEPS)

-include $(DEPS)
