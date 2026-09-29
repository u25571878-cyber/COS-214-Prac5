# CampusGuard Dockerfile
# Builds the whole application inside the image using the project's own
# Makefile, so `make` behaves identically here and on your own machine.

FROM ubuntu:24.04

# g++/make build the app; valgrind/gdb are kept in the image so a tutor
# can ask for that evidence live, inside the same container that ran the demo.
RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    make \
    valgrind \
    gdb \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN make clean && make

# docker compose up --build runs the scripted demo by default so the
# tutor sees full output with no keyboard needed. The interactive menu
# is still reachable -- see docker-compose.yml / README for how.
CMD ["./campusguard", "--demo"]
