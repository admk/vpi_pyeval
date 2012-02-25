env = Environment()
env['CCFLAGS'] = ['-std=gnu99', '-fPIC', '-Wall', '-g', '-O3']
env['CPPPATH'] = ['/usr/include/python2.7', '/usr/local/include/iverilog']
env['LINKFLAGS'] = ['-bundle', '-undefined suppress', '-flat_namespace']
env['LINKFLAGS'] = ' '.join(env['LINKFLAGS'])
env['LIBPATH'] = ['/usr/local/lib']
env['LIBS'] = ['python2.7', 'veriuser', 'vpi']
Export('env')

env.SConscript('build.scons', variant_dir='build', src_dir='#')
Import('vpi_target')
Return('vpi_target')

# vim:ft=python:
