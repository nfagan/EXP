import sqlite3
import sys
from os import path

def __main__():

	filename = 'test1.db'
	table = 'table1'

	if len(sys.argv) > 1:
		filename = sys.argv[1]

	full_filename = path.join('bin', filename)

	if not path.isfile(full_filename):
		print('File {0} does not exist.'.format(full_filename))
		return

	conn = sqlite3.connect(full_filename)
	cur = conn.cursor()
	cur.execute('SELECT * FROM {0}'.format(table))
	rows = cur.fetchall()
	for row in rows:
		print(row)

__main__()