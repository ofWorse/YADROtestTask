
CXX = c++                  #io, lim.        io,vec. vec,<.  
SRCS =  ../headers/text.h ../headers/menuItems.h ../headers/inputProtection.h ../headers/file.h ../headers/Tape.h text.cpp file.cpp Tape.cpp menu.cpp main.cpp 
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

