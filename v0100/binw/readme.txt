Precompiled Smaller C binaries for Windows.
These can be used for cross-compiling for DOS, Linux and MacOS as well.

System requirements:
- Client OS: Windows XP or better
- Server OS: Windows Server 2003 or better

Run the following DOS/Windows commands to make Windows binaries out of
the parts contained in this directory (anti-virus software may not let
you download precompiled .EXE's if it mistakenly thinks they contain
malware; unfortunately, false positives are pervasive):
copy /b m.dat + z.dat + n2f.dat    n2f.exe
copy /b m.dat + z.dat + smlrc.dat  smlrc.exe
copy /b m.dat + z.dat + smlrcc.dat smlrcc.exe
copy /b m.dat + z.dat + smlrl.dat  smlrl.exe
copy /b m.dat + z.dat + smlrpp.dat smlrpp.exe
