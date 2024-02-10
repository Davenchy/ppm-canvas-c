command := main
image_file := image.ppm
open_with := feh

.PHONY: build open exec

build: ${command}

${command}: main.c
	gcc main.c -o $@ -Wall -Werror

exec: ${command}
	./${command} ${image_file}

open: exec
	${open_with} ${image_file}
