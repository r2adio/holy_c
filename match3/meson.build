project('ascii_match', 'c', default_options: ['c_std=c2x'])

# Find Raylib dependency
raylib_dep = dependency('raylib', required: true)

# Define the source dir and include dir
subdir('src')
inc_dir = include_directories('include')

# Define the executable
executable(
  'ascii_match',
  src_dir,
  include_directories: inc_dir,
  dependencies: [raylib_dep],
  install: false,
)
