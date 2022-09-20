#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import re
import sys

#
#
#

EMPTY_MATCHER = re.compile(r'^\s*$')
C_COMMENT_MATCHER = re.compile(r'^/\*.*\*/', re.S)

USER_INCLUDE_MATCHER = re.compile(r'#\s*include\s*\"(.*)\"')
SYSTEM_INCLUDE_MATCHER = re.compile(r'#\s*include\s*<(.*)>')
PRAGMA_ONCE_MATCHER = re.compile(r'#\s*pragma\s+once')

#
#
#

def CollectLicenseComment(headerPath):
    with open(headerPath, "r") as headerStream:
        headerContent = headerStream.read().strip()
        if result := re.match(C_COMMENT_MATCHER, headerContent):
            return result.group()
        else:
            return ""

def CollectSystemIncludes(headerPath, parsedHeaders = set()):
    with open(headerPath, "r") as headerStream:
        headerContent = headerStream.read().strip()

        if PRAGMA_ONCE_MATCHER.search(headerContent) and headerPath in parsedHeaders:
            return set()

        headerIncludes = set()
        
        parsedHeaders.add(headerPath)
        headerLines = headerContent.split('\n')

        for headerLine in headerLines:
            if result := USER_INCLUDE_MATCHER.findall(headerLine):
                internalHeaderPath = os.path.abspath(os.path.join(os.path.dirname(headerPath), result[0]))
                headerIncludes = headerIncludes.union(CollectSystemIncludes(internalHeaderPath, parsedHeaders))
            if result := SYSTEM_INCLUDE_MATCHER.findall(headerLine):
                headerIncludes.add(result[0])

        return headerIncludes

def ParseHeader(headerPath, parsedHeaders = set()):
    with open(headerPath, "r") as headerStream:
        headerContent = headerStream.read().strip()
        headerContent = re.sub(C_COMMENT_MATCHER, '', headerContent)

        if PRAGMA_ONCE_MATCHER.search(headerContent) and headerPath in parsedHeaders:
            return ""
        
        parsedHeaders.add(headerPath)
        headerLines = headerContent.split('\n')

        outputContent = ""
        shouldSkipNextEmptyLines = True

        for headerLine in headerLines:
            if EMPTY_MATCHER.match(headerLine) and shouldSkipNextEmptyLines:
                continue

            if PRAGMA_ONCE_MATCHER.match(headerLine):
                shouldSkipNextEmptyLines = True
                continue
        
            if result := USER_INCLUDE_MATCHER.findall(headerLine):
                internalHeaderPath = os.path.abspath(os.path.join(os.path.dirname(headerPath), result[0]))
                internalHeaderContent = ParseHeader(internalHeaderPath, parsedHeaders)

                outputContent += internalHeaderContent
                shouldSkipNextEmptyLines = True
                continue
            
            if result := SYSTEM_INCLUDE_MATCHER.findall(headerLine):
                shouldSkipNextEmptyLines = True
                continue

            shouldSkipNextEmptyLines = False
            outputContent += "{}\n".format(headerLine)

        return "{}\n".format(outputContent)

#
#
#

inputHeaderPath = os.path.abspath(sys.argv[1])
outputHeaderPath = os.path.abspath(sys.argv[2])

os.makedirs(os.path.dirname(outputHeaderPath), exist_ok=True)

with open(outputHeaderPath, "w") as outputHeaderStream:
    licenseComment = CollectLicenseComment(inputHeaderPath)
    systemIncludes = CollectSystemIncludes(inputHeaderPath)

    outputHeaderStream.write("{}\n".format(licenseComment))
    outputHeaderStream.write("\n")
    
    for systemInclude in sorted(systemIncludes):
        outputHeaderStream.write("#include <{}>\n".format(systemInclude))
    outputHeaderStream.write("\n")

    outputHeaderStream.write(ParseHeader(inputHeaderPath).strip())
    outputHeaderStream.write("\n")
