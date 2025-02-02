#include "Example.hpp"
#include <spdlog/spdlog.h>

int Example::value() {
    spdlog::info("Hello World!");
    constexpr auto returned_value{5};
    return returned_value;
}