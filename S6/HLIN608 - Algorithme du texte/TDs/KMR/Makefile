CXX = g++
#CXX_FLAGS = -g -O0 -Wall -ansi -pedantic
CXX_FLAGS = -O3 -Wall -ansi -pedantic

PROGS = kmr_vectors_stacks kmr_vectors_lists kmr_maps_stacks kmr_maps_lists

SOURCES = kmr.cpp test_kmr.cpp

VECTORS_FLAGS = -D__USING_VECTORS__
STACKS_FLAGS = -D__USING_STACKS__
MAPS_FLAGS = -U__USING_VECTORS__
LISTS_FLAGS = -U__USING_STACKS__

kmr_vectors_stacks_FLAGS = $(VECTORS_FLAGS) $(STACKS_FLAGS)
kmr_vectors_lists_FLAGS = $(VECTORS_FLAGS) $(LISTS_FLAGS)
kmr_maps_stacks_FLAGS = $(MAPS_FLAGS) $(STACKS_FLAGS)
kmr_maps_lists_FLAGS = $(MAPS_FLAGS) $(LISTS_FLAGS)

kmr_vectors_stacks_OBJ = $(addprefix kmr_vectors_stacks_, $(OBJ))
kmr_vectors_lists_OBJ = $(addprefix kmr_vectors_lists_, $(OBJ))
kmr_maps_stacks_OBJ = $(addprefix kmr_maps_stacks_, $(OBJ))
kmr_maps_lists_OBJ = $(addprefix kmr_maps_lists_, $(OBJ))

HEADERS = kmr.h

OBJ = $(SOURCES:.cpp=.o)

all: $(PROGS)

.SUFFIXES: .cpp .h .o

.cpp.o:
	$(CXX) $(CXX_FLAGS) -c $<

$(kmr_vectors_stacks_OBJ): $(SOURCES)
	make mrproper
	make $(OBJ) CXX_FLAGS="$(CXX_FLAGS) $(kmr_vectors_stacks_FLAGS)"
	for i in $(OBJ); do mv "$$i" "kmr_vectors_stacks_$$i"; done

kmr_vectors_stacks: $(kmr_vectors_stacks_OBJ)
	$(CXX) $^ -o $@



$(kmr_vectors_lists_OBJ): $(SOURCES)
	make mrproper
	make $(OBJ) CXX_FLAGS="$(CXX_FLAGS) $(kmr_vectors_lists_FLAGS)"
	for i in $(OBJ); do mv "$$i" "kmr_vectors_lists_$$i"; done

kmr_vectors_lists: $(kmr_vectors_lists_OBJ)
	$(CXX) $^ -o $@



$(kmr_maps_stacks_OBJ): $(SOURCES)
	make mrproper
	make $(OBJ) CXX_FLAGS="$(CXX_FLAGS) $(kmr_maps_stacks_FLAGS)"
	for i in $(OBJ); do mv "$$i" "kmr_maps_stacks_$$i"; done

kmr_maps_stacks: $(kmr_maps_stacks_OBJ)
	$(CXX) $^ -o $@



$(kmr_maps_lists_OBJ): $(SOURCES)
	make mrproper
	make $(OBJ) CXX_FLAGS="$(CXX_FLAGS) $(kmr_maps_lists_FLAGS)"
	for i in $(OBJ); do mv "$$i" "kmr_maps_lists_$$i"; done

kmr_maps_lists: $(kmr_maps_lists_OBJ)
	$(CXX) $^ -o $@



clean: mrproper
	rm -f $(PROGS)
	rm -f $(kmr_vectors_stacks_OBJ)
	rm -f $(kmr_vectors_lists_OBJ)
	rm -f $(kmr_maps_stacks_OBJ)
	rm -f $(kmr_maps_lists_OBJ)

mrproper:
	rm -f $(OBJ) *~

