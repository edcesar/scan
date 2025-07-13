CXX=g++
CXXFLAGS=-std=c++11 -I../src
LIBS=-lpthread -lm

SRC_OBJS=../src/bb_base.o ../src/bb_comp.o ../src/bb_index.o ../src/bit.o \
 ../src/board.o ../src/book.o ../src/dxp.o ../src/eval.o ../src/fen.o \
 ../src/game.o ../src/hash.o ../src/libmy.o ../src/list.o ../src/move.o \
 ../src/move_gen.o ../src/pos.o ../src/score.o ../src/search.o \
 ../src/socket.o ../src/sort.o ../src/thread.o ../src/trans.o \
 ../src/tuple.o ../src/util.o ../src/var.o

TEST_OBJS=test_main.o board8.o
TARGET=test_runner

all: $(TARGET)

$(TARGET): $(TEST_OBJS) $(SRC_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TEST_OBJS) $(TARGET)


test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test
