includes('rules.lua', 'compiler.lua')

set_compiler_flags()

add_requires('gtest')

target('s21_containers_test')
  set_kind('binary')
  add_files('test/*.cpp')
  add_includedirs('include')

  add_rules('valgrind', 'report', 'coverage')
  add_packages('gtest')

  set_group('test')
