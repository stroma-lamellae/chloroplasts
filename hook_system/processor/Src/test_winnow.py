import unittest
from winnow import *
from hookFile import HookFile
from hookFileType import HookFileType
import os


class TestWinnow(unittest.TestCase):

    def setUp(self):
        self.hashA = []
        self.hashB = []
        bhash = AnHash()
        bhash.hashVal = 100
        self.hashB.append(bhash)

    def test_winnow(self):
        '''
        Test that the winnow function returns appropriate List[AnHash]
        '''
        resultA = winnow(self.hashA, 1)
        self.assertEqual(len(resultA), 0)
        resultB = winnow(self.hashB, 2)
        self.assertEqual(resultB[0].hashVal, 100)
