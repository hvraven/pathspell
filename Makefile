# regex in gcc is broken (at least till 4.7.1)
CXX        = clang++
CXXFLAGS   = -std=c++11 -stdlib=libc++

spells : spells.o csv.o
	${CXX} ${CXXFLAGS} spells.o csv.o -o spells

