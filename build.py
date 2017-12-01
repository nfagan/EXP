import subprocess
import os

is_windows = os.name == "nt"
exp_dir = os.path.dirname(os.path.realpath(__file__))

def require_dir(directory):
	if not os.path.exists(directory):
		os.makedirs(directory)

def get_generator_commands(directory):
	generator_commands = ["cmake", "-G"]
	if is_windows:
		generator_commands.append("Visual Studio 15 2017 Win64")
	else:
		generator_commands.append("Xcode")

	generator_commands.append(directory)
	return generator_commands

def get_install_commands():
	return ['cmake', '--build', '.', '--target', 'install']

def build_subdirectory(name):
	print("\n\nBuilding {0} ...".format(name))
	cmake_dir = os.path.join(exp_dir, name)
	build_dir = os.path.join(cmake_dir, "build")
	require_dir(build_dir)
	os.chdir(build_dir)
	generator_commands = get_generator_commands(cmake_dir)
	install_commands = get_install_commands()
	result = subprocess.call(generator_commands)
	print("\n\nDone. Installing ...\n\n")
	if (result == 0):
		result = subprocess.call(install_commands)
		print("Done.\n\n")
	return result

def check_errors(err):
	if err == 1:
		print('\n\nFailed to build with the above message.\n\n')
		return True

def build():
	modules = ['EXPUtil', 'EXPGL', 'EXPTask', 'EXPSQL']
	for i in xrange(len(modules)):
		if check_errors(build_subdirectory(modules[i])):
			return

build()
