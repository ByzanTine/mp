cc_library(
    name = "exercise",
    hdrs = ["exercise.h"],
)

cc_test(
    name = "exercise_test",
    srcs = ["exercise_test.cc"],
    copts = [
        "-Iexternal/gtest/include", 
    ],
    deps = [
        "@gtest//:main",
        ":exercise",
    ],
)
