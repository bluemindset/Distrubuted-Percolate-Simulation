#######################################################
# @Author: B159973
# @Date:   19/11/2019
# @Course: Programming Skills - 2019
# @University of Edinburgh
#######################################################

#########################Libraries#####################
import unittest
from regression import Reg_Lib
from test import support
import sys
#######################################################

# Regression test class
#	Test Regression:
#	1. Call compile, run and clean functions from regression library
#	3. Assert for equality the outputs of each instance of Version 1 & 2


class TestRegression(unittest.TestCase):


    _TESTS = 32
    _map= "map"
    _pgm= ".pgm"
    _out ="test/output/"
    _orig= "test/serial_version/map.pgm"

    """
	Assert for equality the pgm file
	"""
    def test_pgm_file(self):

        for i in range(1,TestRegression._TESTS ):
            regression = Reg_Lib()
            new = TestRegression._map+str(i)+TestRegression._pgm
            print new
            self.assertEqual(regression.get_output(TestRegression._out+new),
                             regression.get_output(TestRegression._orig), msg="Parallel and Serial version do not have the same outputs!")
    """
	Assert for equality the dat file
	"""


if __name__ == '__main__':
    unittest.main()
