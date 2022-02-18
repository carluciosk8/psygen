################################################################################
##
##   PSYGEN - Procedural Synthesis Graphics Engine
##   http://psygen.sourceforge.net
##
##   Copyright (c) 2008 by Carlucio Santos Cordeiro
##   email:      carlucio@gmail.com
##
##   This file is part of PSYGEN
##
##   PSYGEN is free software: you can redistribute it and/or modify it under
##   the terms of the GNU Lesser General Public License as published by the
##   Free Software Foundation, either version 3 of the License, or (at your
##   option) any later version.
##
##   PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY
##   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
##   FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
##   more details.
##
##   You should have received a copy of the GNU Lesser General Public License
##   along with PSYGEN. If not, see <http://www.gnu.org/licenses/>
##
################################################################################
import os
import sys


## Emulate clean target.
if 'clean' in COMMAND_LINE_TARGETS:
    os.system( 'scons -Q -c' )
    Exit(0)

else:
    print("Building PSYGEN ...")
    print()

    PSYmath = SConscript(['src/PSYmath/SConscript'])
    PSYengine = SConscript(['src/PSYengine/SConscript'])
    AntTweakBar = SConscript(['src/AntTweakBar/SConscript'])

    PSYtests = SConscript(['tests/SConscript'])
    PSYsamples = SConscript(['samples/SConscript'])

    Depends(PSYengine, PSYmath)
    Depends(PSYtests, PSYengine)
    Depends(PSYsamples, AntTweakBar)
    Depends(PSYsamples, PSYengine)
