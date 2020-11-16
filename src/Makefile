TARGET= server
CPP_SOURCE=$(wildcard *.cpp)
OBJS 	= $(patsubst %.cpp,%.o, $(CPP_SOURCE)) 
INCLUDE_PATH=-I ../include/ -I ../libs/
LIBRARY_PATH=-L ../libs/libs/
LIBRARY=-lboost_thread -lboost_system -llog4cxx -lCJsonObject

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@ $(INCLUDE_PATH)

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_OUT_DIR)/$(TARGET) $(LIBRARY_PATH) $(LIBRARY)

.PHONY:clean

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
