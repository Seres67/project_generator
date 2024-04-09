project('project_generator', 'cpp', default_options: ['warning_level=2'])
subdir('src')
include_dir = include_directories('include')
executable('project_generator', sources, include_directories: include_dir, install: true, install_dir: '/usr/local/bin')
