# create by afterloe
# version is 1.0
# modify time: 2022-04-13
# MIT License

.PHONY: build, clean

FILE_NAME = linked_stack

.ONESHELL:
build: ${FILE_NAME}.h ${FILE_NAME}.c
	clang -c ${FILE_NAME}.c -I ./$<
	clang ${FILE_NAME}.o test_${FILE_NAME}.c -o ${FILE_NAME}.app -I ./$<
	@echo "build success"
	@make clean

.ONESHELL:
clean: ${FILE_NAME}.o ${FILE_NAME}.app
	rm -rf ${FILE_NAME}.o
	mv ${FILE_NAME}.app ../out/
