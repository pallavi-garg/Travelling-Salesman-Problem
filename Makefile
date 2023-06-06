#CXXFLAGS=-ggdb -std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant
CXXFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant -O3

INC = -I include -I include/BnBDFS -I include/SLS -I include/DP

SRCS = $(wildcard src/*.cpp)
BNB_SRCS = $(wildcard src/BnBDFS/*.cpp)
SLS_SRCS = $(wildcard src/SimulatedAnnealingSLS/*.cpp)
DP_SRCS = $(wildcard src/DP/*.cpp)

all: $(SRCS) $(BNB_SRCS) $(SLS_SRCS) $(DP_SRCS)
	@echo ----------------compiling executable program agent--------------------
	g++ $(CXXFLAGS) $(SRCS) $(BNB_SRCS) $(SLS_SRCS) $(DP_SRCS) $(INC) -o agent 

clean:
	@echo ----------------removing executable program agent--------------------
	rm agent