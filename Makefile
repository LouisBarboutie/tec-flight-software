all: 
	cmake -S . -B build
	cmake --build build -j $(nproc)

clean: 
	rm -rf build/*
