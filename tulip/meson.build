# Declare the library
jni_include = get_option('jni_include')

# Format the jni_home
inc = include_directories(['include', jni_include])
sources = ['src/tulip-wrapping.c', 'src/tiamalgamation.c']
libtulip_jni = shared_library('tulipjni', sources, include_directories: inc)