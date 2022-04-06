TARGET= server
CPP_SOURCE=$(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o, $(CPP_SOURCE)) 
INCLUDE_PATH=-I ../include/ -I ../libs/
LIBRARY_PATH=-L ../libs/libs/
LIBRARY=-lboost_thread -lboost_system -llog4cxx -lCJsonObject

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)$@ $(INCLUDE_PATH)

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJ_PATH)/*.o -o $(BUILD_OUT_DIR)/$(TARGET) $(LIBRARY_PATH) $(LIBRARY)

.PHONY:clean

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
