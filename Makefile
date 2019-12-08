.PHONY: docker-build docker-run
all: docker-build docker-run

DOCKER_IMAGE=gnuplotscriptingbuild

docker-build:
	docker build . -t ${DOCKER_IMAGE}

docker-run:
	docker run --rm \
	    -u $(shell id -u):$(shell id -g) \
	    -v $(shell pwd):/opt/share \
	    -w /opt/share $(DOCKER_IMAGE) \
	    /bin/bash -c \
            "meson build && \
	         cd build && \
	         ninja test"