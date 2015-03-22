
mymode = ARGUMENTS.get('mode', 'debug')

if not (mymode in ['debug', 'release']):
    print "Error expected 'debug' or 'release' found:"+mymode
    Exit(1)



env = Environment()

dir = 'debug'

if mymode == 'debug':
    env.Append(CCFLAGS=['-g'])
    dir = 'debug'
else:
    env.Append(CCFLAGS=['-O2'])
    dir='release'

Export('env')

#####################################################################################
#####################################################################################
# define libaries
#####################################################################################
SConscript('nt/SConscript', variant_dir='nt/'+dir, duplicate=0)
SConscript('data/SConscript', variant_dir='data/'+dir, duplicate=0)
SConscript('calc/SConscript', variant_dir='calc/'+dir, duplicate=0)
SConscript('driver/SConscript', variant_dir='driver/'+dir, duplicate=0)
SConscript('filler/SConscript', variant_dir='filler/'+dir, duplicate=0)
SConscript('match/SConscript', variant_dir='match/'+dir, duplicate=0)


#####################################################################################
#####################################################################################
# define app/test dirs
#####################################################################################
SConscript('apps/SConscript', variant_dir='apps/'+dir, duplicate=0)
SConscript('tests/SConscript', variant_dir='tests/'+dir, duplicate=0)

#####################################################################################
#####################################################################################

