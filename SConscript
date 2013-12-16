env = Environment(
    CC='clang++',
    CCFLAGS=[
        '-Weverything',
        '-Werror'
    ],
    CPPPATH=[
        '.'
    ]
)

env.Program(
    target='helloworld',
    source=["helloworld.c"]
)
