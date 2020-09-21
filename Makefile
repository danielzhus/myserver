# 指定源码路径和输出路径
export BUILD_HOME_DIR = $(shell pwd)
export SOURCE_PATH=$(BUILD_HOME_DIR)/src
export BUILD_OUT_DIR=$(BUILD_HOME_DIR)/bin

# 指定编译器参数
export CXX=g++
export CXXFLAGS=-Wall -g -std=c++11

all:
	make -C $(SOURCE_PATH)
all:libs

LIBS = CJsonObject
libs:$(LIBS)
$(LIBS):
	$(MAKE) -C libs/$@

clean:
	make -C $(SOURCE_PATH) clean
	for project in $(LIBS);   do $(MAKE) clean -C libs/$$project; done
