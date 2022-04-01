# create by afterloe
# version is 1.0
# modify time: 2022-03-18
# MIT License

.PHONY: build,clean

.ONESHELL:
clean: line_impl.o
	rm -rf $^
	@echo "clean success"

.ONESHELL:
build:
	c++ -c line_impl.cpp -I ./
	c++ line_impl.o main.cpp -I ./
	@echo "build success"
	@make clean