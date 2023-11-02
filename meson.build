project(
    'rat',
    'cpp',
    version : '0.0.1',
    default_options : [
        'buildtype=debug',
        'optimization=0',
        'cpp_std=c++17'
    ],
    meson_version: '>= 0.60.0',
)

src = [
    'source/main.cpp',
    'source/basic_functions.cpp'
]

executable('rat',
           sources: src,
           dependencies: [dependency('docopt')]  # docopt - cli args parser
)
