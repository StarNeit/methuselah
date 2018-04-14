from distutils.core import setup
setup(name='btcspendfrom',
      version='1.0',
      description='Command-line utility for methuselah "coin control"',
      author='Gavin Andresen',
      author_email='gavin@methuselahfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
