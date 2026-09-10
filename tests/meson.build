gtest_dep = dependency('gtest', main: true, fallback: ['gtest', 'gtest_main_dep'])

dependencies = [
  gtest_dep,
  mathtest_dep,
]

test_exe = executable(
  'test-all',
  sources: [
    'mathtest_tests.cpp',
  ],
  dependencies : dependencies,
  install : true,
)

test('test-all', test_exe, protocol: 'gtest')
