# Copyright (C) 2019 Hook System Authors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import unittest
from standardize import *
from hookFile import HookFile
from hookFileType import HookFileType
import os


class TestStandardize(unittest.TestCase):

    def setUp(self):
        self.java_files = []
        self.c_files = []
        for root, dirs, files in os.walk("fake-data/Current\ Year"):
            for f in files:
                hook_file = HookFile(f, "TestStudent", HookFileType.CURRENT_YEAR, open(f, encoding="utf-8"))
                if f.endswith('.java'):
                    self.java_files.append(hook_file)
                else:
                    self.c_files.append(hook_file)

    def test_replace(self):
        '''
        Test that the replaceIfContiains function replaces strings as specified
        '''
        result = replaceIfContains("test", "this is just a test", "unittest")
        self.assertEqual(result, "this is just a unittest")

    def test_standardizeJava(self):
        '''
        Test that java files are standardized according to spec
        '''
        java_result = standardizeJava(self.java_files)
        self.assertCountEqual(java_result,self.java_files)
        for result in java_result:
            self.assertNotIn('\t',result)

    def test_standardizeC(self):
        '''
        Test that c/cpp files are standardized according to spec
        '''
        c_result = standardizeC(self.c_files)
        self.assertCountEqual(c_result, self.c_files)
        for result in c_result:
            self.assertNotIn('\t',result)

