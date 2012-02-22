env = Environment(CCFLAGS = '-lpython2.7 -I/usr/include/python2.7')
Export('env')

env.SConscript('build.scons')
Import('vpi_target')
Return('vpi_target')

# vim:ft=python:
