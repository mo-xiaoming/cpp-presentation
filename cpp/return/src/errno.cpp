// Not a pure function, disables lots of optimizations

#include <fcntl.h>
#include <unistd.h>

#include <spdlog/spdlog.h>

static int foo() {
    auto const fd = open("does_not_exist", O_RDONLY); // NOLINT
    if (fd == -1) {
        return errno;
    }
    close(fd);
    return 0;
}

int main() {
    if (foo() != 0) {
        spdlog::error("some thing went wrong"); // DONT DO THIS
        spdlog::error(strerror(errno));
    }
}
