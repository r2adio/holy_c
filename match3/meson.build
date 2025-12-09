project(
  'ascii_match',
  'c',
  default_options: ['c_std=c23', 'warning_level=3', 'werror=true', 'buildtype=debugoptimized'],
)

# Find Raylib dependency
raylib_dep = dependency('raylib', required: true)

inc_dir = include_directories('include')

# Define the source dir and include dir
subdir('src')

# Define the executable
executable(
  'ascii_match',
  src_dir,
  include_directories: inc_dir,
  dependencies: [raylib_dep],
  install: false,
)
