import unittest
import glob
#import flask_testing


def hook_suite():
    suite = unittest.TestSuite()
    test_file_strings = glob.glob('test_*.py')
    module_strings = [str[:len(str)-3] for str in test_file_strings]

    for t in module_strings:
        try:
            mod = __import__(t, globals(), locals(), ['suite'])
            suitefn = getattr(mod, 'suite')
            suite.addTest(suitefn())
        except (ImportError, AttributeError):
            suite.addTest(unittest.defaultTestLoader.loadTestsFromName(t))
   # suite.addTest(unittest.makeSuite(TestStandardize))
    return suite

if __name__ == '__main__':
    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(hook_suite())

