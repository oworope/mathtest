sources = [
  'mathtest.cpp'
]

mathtest = static_library('mathtest', sources)
mathtest_inc = include_directories('.')

mathtest_dep = declare_dependency(
  link_with : mathtest,
  include_directories: mathtest_inc,
  cpp_args: ['-fno-exceptions']
)

executable('mathtest',
  'main.cpp',
  'mathtest.cpp',
)