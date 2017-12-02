import subprocess
import os
import sys
import shutil

command_options = ['--rebuild', '--module']
modules = ['EXPUtil', 'EXPGL', 'EXPTask', 'EXPSQL', 'examples']
is_windows = os.name == 'nt'
exp_dir = os.path.dirname(os.path.realpath(__file__))
remove_build_dir = False;

def get_help_text():
	help_string = '\n\nValid options are:'
	for i in xrange(len(command_options)):
		help_string += ('\n\t"{0}"'.format(command_options[i]))
	return help_string

def throw_invalid_command():
	raise Exception('\n\nUnrecognized command {0}\n'.format(get_help_text()))

def handle_command_line_input():
	global modules
	global remove_build_dir
	if len(sys.argv) == 1:
		return
	i = 1
	proceed = True
	while proceed:
		is_last = i == len(sys.argv)-1
		opt = sys.argv[i]
		if opt == '--rebuild':
			remove_build_dir = True
			i += 1
		elif opt == '--module' and not is_last and sys.argv[i+1] in modules:
			modules = [sys.argv[i+1]]
			i += 2
		else:
			throw_invalid_command()

		proceed = i < len(sys.argv)

def require_dir(directory):
	if not os.path.exists(directory):
		os.makedirs(directory)

def conditional_remove_dir(directory, condition):
	if os.path.exists(directory) and condition:
		shutil.rmtree(directory)

def get_generator_commands(directory):
	generator_commands = ['cmake', '-G']
	if is_windows:
		generator_commands.append('Visual Studio 15 2017 Win64')
	else:
		generator_commands.append('Xcode')
	generator_commands.append(directory)
	return generator_commands

def get_install_commands():
	return ['cmake', '--build', '.', '--target', 'install']

def build_subdirectory(name):
	print('\n\nBuilding {0} ...'.format(name))
	cmake_dir = os.path.join(exp_dir, name)
	build_dir = os.path.join(cmake_dir, 'build')
	conditional_remove_dir(build_dir, remove_build_dir)
	require_dir(build_dir)
	os.chdir(build_dir)
	generator_commands = get_generator_commands(cmake_dir)
	install_commands = get_install_commands()
	result = subprocess.call(generator_commands)
	print('\n\nDone. Installing ...\n\n')
	if (result == 0):
		result = subprocess.call(install_commands)
		print('Done.\n\n')
	return result

def check_errors(err):
	if err != 0:
		print('\n\nFailed to build with the above message.\n\n')
		return True
	return False

def build():
	for i in xrange(len(modules)):
		if check_errors(build_subdirectory(modules[i])):
			return
	print('\n\nAll succeeded.\n\n')

handle_command_line_input()
build()