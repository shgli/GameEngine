#!/usr/bin/env python
import os
import sys
import subprocess

def RunAll(runList):
    for item in runList:
	if isinstance(item,str):
            subprocess.Popen(item,shell=True).wait()
	elif isinstance(item,collections.Callable):
	    item()
	elif isinstance(item,list):
	    subprocess.Popen(item).wait()
	else:
	    raise TypeError(item + ' not callable')

runList = ['cmake -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=DEBUG ../'
	,'make install']
RunAll(runList)
