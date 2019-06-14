project('libtulipindicators', 'c')

inc = include_directories('include')
libtulipindicators = static_library('tulipindicators',
    'src/tiamalgamation.c', include_directories: inc)

libtulipindicators_dep = declare_dependency(include_directories: inc, link_with: libtulipindicators)