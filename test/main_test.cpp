//
// Created by hlx on 2023-04-12.
//
#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES

#include <doctest/doctest.h>

int main(int argc, const char *argv[]) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int result = context.run();
    return result;
}