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

