function set_compiler_flags()
  add_rules('mode.release', 'mode.debug', 'mode.tsan', 'mode.asan')
  add_cxxflags('-Wall', '-Werror', '-Wextra', '-pedantic')
  add_toolchains('gcc')
  set_languages('c++17')
end
