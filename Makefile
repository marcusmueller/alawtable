override CXXFLAGS := -std=c++20 -Wall -Wpedantic $(CXXFLAGS)

.PHONY: all clean

all: alawtable linear_to_alaw.csv linear_to_linear.csv lin_to_lin.py

clean:
	rm -f g711.o linear_to_alaw.csv linear_to_linear.csv lin_to_lin.py alawtable


alawtable: g711.o

linear_to_alaw.csv linear_to_linear.csv lin_to_lin.py: alawtable
	./alawtable > lin_to_lin.py
