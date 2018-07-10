src_dir = src/
src = $(notdir $(wildcard $(src_dir)*))
obj_dir = obj/
obj = $(src:.cpp=.o)
inc_dir = include/

LDFLAGS = -std=c++11 -pthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -ljsoncpp -g
CC = g++

game: $(addprefix $(obj_dir),$(obj))
	$(CC) $^ -I $(inc_dir) -o $@ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.cpp
	$(CC) $^ -o $@ -I $(inc_dir) -c $(LDFLAGS)

clean:
	rm $(obj_dir)/*