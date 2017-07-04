SRC := ./src
EXE := vsl-bindgen

CXXFILES := $(wildcard $(SRC)/*.cpp)
CXXFLAGS := $(shell llvm-config --cxxflags) -Wall -std=c++14
LDFLAGS := $(shell llvm-config --ldflags) -lclang

INSTALL_PATH?=/usr/local

all: $(EXE)

install: $(EXE)
	cp $(EXE) $(INSTALL_PATH)/bin/$(EXE)

$(EXE): $(CXXFILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(EXE)

clean:
	rm -r $(BIN) $(EXE)
