"""Some utilities to filter outputs from tools
used to generate documentation (sphinx and doxygen)

Siconos is a program dedicated to modeling, simulation and control
 of non smooth dynamical systems.

 Copyright 2018 INRIA.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
"""
from pathlib import Path


def filter_sphinx_warnings(warnfile):
    """Remove 'expected' (and so without interest) warnings from sphinx logfile
    to keep only useful outputs.

    Supposed to be called by a target created by cmake
    (post-command of make html)
    """
    expected_warnings = [
        'WARNING: Duplicate declaration',  # Known breathe warning
        'WARNING: Citation',
        'WARNING: image file not readable: ../inherit_graph',
    ]
    with open(warnfile) as ff:
        keep_msg = ff.readlines()

    for msg in expected_warnings:
        with open(warnfile) as ff:
            # remove useless lines
            current = [n for n in ff.readlines() if not n.find(msg) > -1]
        keep_msg = [msg for msg in current if msg in keep_msg]

    with open(warnfile, 'w') as ff:
        for msg in keep_msg:
            ff.write(msg)


def filter_doxygen_warnings_files(warnings_path, outputfile):
    """Post process outputs from doxygen warnings :
      * remove all empty files
      * concat all warnings files into one

     Parameters
     ----------
     warnings_path : string
         full path to warnings files
     outputfile : string
         name of resulting file (concat.). Saved in warnings_path

    This function is supposed to be called by a target created
    with cmake (make filter_warnings)
    """
    # Get all warnings files generated by doxygen in
    # <warning_path>
    warnings_path = Path(warnings_path)
    warnfiles = [f for f in warnings_path.glob('*.warnings')]
    real_warnings = []
    for f in warnfiles:
        if f.stat().st_size == 0:
            # If file is empy, remove it.
            f.unlink()
        else:
            real_warnings.append(f)
    outputfile = Path(warnings_path, outputfile)
    # Create (concatenation) one file for all warnings
    with open(outputfile, 'w') as outfile:
        for fname in real_warnings:
            with open(fname) as infile:
                for line in infile:
                    outfile.write(line)