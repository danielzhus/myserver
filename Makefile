# 指定源码路径和输出路径
export BUILD_HOME_DIR = $(shell pwd)
export SOURCE_PATH=$(BUILD_HOME_DIR)/src
export BUILD_OUT_DIR=$(BUILD_HOME_DIR)/bin

# 指定编译器参数
export CXX=g++
export CXXFLAGS=-Wall -g

all:
	make -C $(SOURCE_PATH)

clean:
	make -C $(SOURCE_PATH) clean