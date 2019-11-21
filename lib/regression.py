#######################################################
# @Author: B159973
# @Date:   19/11/2019
# @Course: Programming Skills - 2019
# @University of Edinburgh
#######################################################

#########################Libraries#####################
import re
import string
import subprocess
import os
import sys
#######################################################


class Reg_Lib:

    """
	Gather the output from the specific file and modify it to only numbers
	@param  file: The filename with path for extracting the output
	"""

    def get_output(self, file):
        out = open(file, "r")
        data = out.read()
        data = re.sub('[^0-9]', '', data)
        return data

    """
	Print the nessesary outputs and errors of each finished command 
	@param  cmd: Executed command
	@param shell_out: The output (stdout) of the executed command.
	@param shell_err: The error log of the executed command. 
	"""

    def print_cmd(self, cmd, shell_out, shell_err):
        print("========================================================\n")
        print('\nOUTPUT of command: ' + str(cmd) +
              "\n" + shell_out.decode('ascii'))
        print('\nERRORS of command: ' + str(cmd) +
              "\n" + shell_err.decode('ascii'))
