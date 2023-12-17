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
    'source/functions.cpp',
]

docopt = library('docopt', 'lib/docopt/docopt.cpp')

rat = executable('rat',
           sources: src,
           link_with: docopt,
)

tests = [
    'AddToken test 1',
    'Tokenize test 1',
    'Tokenize test 2',
    'Divide test 1',
    'Parse test 1',
    'Convert test 1',
]

foreach i : range(tests.length())
  test(tests[i], rat, args : ['--test', i.to_string()])
endforeach

