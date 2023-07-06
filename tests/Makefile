CXX = g++
SRCDIR = src/cpp/
TESTDIR = tests
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TEST_SRCS = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))

TARGET = tests

all: $(TARGET)

$(TARGET): $(OBJS) $(TEST_OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -I$(SRCDIR) -c $< -o $@

# Очистка сборки
clean:
	$(RM) -r $(BINDIR) $(OBJDIR)
