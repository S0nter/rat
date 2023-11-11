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
    'source/basic_functions.cpp',
    'source/test.cpp',
]

docopt = library('docopt', 'lib/docopt/docopt.cpp')

rat = executable('rat',
           sources: src,
           link_with: docopt,
)

test('All tests', rat, args : ['--tests'])