
CXX = c++
SRCS = inputProtection.h text.h menuItems.h file.h Tape.h menu.h file.cpp Tape.cpp main.cpp text.cpp menu.cpp 
OBJS = $(SRCS:.cpp=.o)
TARGET = yadro_test 

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Правило для компиляции каждого исходного файла
%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

