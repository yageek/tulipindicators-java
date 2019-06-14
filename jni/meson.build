project('tulip-jni', 'cpp', version: '1.0.0',  default_options : ['cpp_std=c++11'])

# Declare the library
jni_include = get_option('jni_include')

# Use libindicators
libtulipindicators_dep = dependency('libtulipindicators', fallback : ['libtulipindicators', 'libtulipindicators_dep'])

# Format the jni_home
inc = include_directories(['include', jni_include])
sources = ['src/tulip-jni.cpp', 'src/tulip-wrapping.cpp']
libtulip_jni = shared_library('tulipjni', sources, include_directories: inc, dependencies: libtulipindicators_dep)