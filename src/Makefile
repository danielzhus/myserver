TARGET= server
CPP_SOURCE=$(wildcard *.cpp)
OBJS 	= $(patsubst %.cpp,%.o, $(CPP_SOURCE)) 
INCLUDE_PATH=-I ../include/
LIBRARY=-lboost_system -llog4cxx

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@ $(INCLUDE_PATH)

$(TARGET):$(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_OUT_DIR)/$(TARGET) $(LIBRARY)

.PHONY:clean

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)