TARGET= server
CPP_SOURCE=$(wildcard *.cpp */*.cpp)
OBJS = $(patsubst %.cpp,%.o, $(CPP_SOURCE)) 
INCLUDE_PATH=-I ../include/ -I ../libs/ -I /usr/local/include/
LIBRARY_PATH=-L ../libs/libs/
LIBRARY=-lboost_thread -lboost_system -llog4cxx -lCJsonObject -lfmt

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)$@ $(INCLUDE_PATH)

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJ_PATH)/*.o $(OBJ_PATH)/*/*.o -o $(BUILD_OUT_DIR)/$(TARGET) $(LIBRARY_PATH) $(LIBRARY)

.PHONY:clean

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
