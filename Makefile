name := main
image_name := image.ppm
command := feh

.PHONY: build open exec

build: ${name}

${name}: main.c
	gcc main.c -o $@ -Wall -Werror

exec: ${name}
	./${name}

open: exec
	${command} ${image_name}
