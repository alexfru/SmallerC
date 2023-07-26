#!/bin/sh
echo -= Smaller-C Build Distros =-

if ! type "smlrcc" > /dev/null; then
    echo -= Build and install local version =-
    chmod +x configure
    ./configure
    make clean
    make
    sudo make install
fi

cd v0100


echo -= DOS - Small - Target 8088 =-
smlrc -nobss -seg16 -no-externs lb.c lb.asm
smlrc -nobss -seg16 -no-externs -label 1001 -D ONLY8086 -D NO_ANNOTATIONS -D NO_EXTRAS smlrc.c smlrc.asm
nasm -f bin smlrc16.asm -o bind/smlrc.exe

echo -= DOS - Huge =-
smlrcc -dosh -Wall smlrc.c -o bindh/smlrc.exe
smlrcc -dosh -D ONLY8086 -D NO_ANNOTATIONS -D NO_EXTRAS  -Wall smlrc.c -o bindh/smlrc86.exe
smlrcc -dosh -Wall n2f.c -o bindh/n2f.exe
smlrcc -dosh -Wall -DHOST_DOS smlrcc.c -o bindh/smlrcc.exe
smlrcc -dosh -Wall smlrl.c -o bindh/smlrl.exe
cd ucpp
smlrcc -dosh -Wall -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c -o ../bindh/smlrpp.exe
cd ..

echo -= DOS - DPMI =-
smlrcc -dosp -Wall smlrc.c -o bindp/smlrc.exe
smlrcc -dosp -Wall -DONLY8086 smlrc.c -o bindp/smlrc86.exe
smlrcc -dosh -Wall n2f.c -o bindp/n2f.exe
smlrcc -dosp -Wall -DHOST_DOS smlrcc.c -o bindp/smlrcc.exe
smlrcc -dosp -Wall smlrl.c -o bindp/smlrl.exe
cd ucpp
smlrcc -dosp -Wall -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c -o ../bindp/smlrpp.exe
cd ..

echo -= Windows =-
smlrcc -win -Wall smlrc.c -o binw/smlrc.exe
smlrcc -win -Wall -DONLY8086 smlrc.c -o binw/smlrc86.exe
smlrcc -win -Wall n2f.c -o binw/n2f.exe
smlrcc -win -Wall -DHOST_WINDOWS smlrcc.c -o binw/smlrcc.exe
smlrcc -win -Wall smlrl.c -o binw/smlrl.exe
cd ucpp
smlrcc -win -Wall -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c -o ../binw/smlrpp.exe
cd ..

echo -= Linux =-
smlrcc -linux -Wall smlrc.c -o binl/smlrc
smlrcc -linux -Wall -DONLY8086 smlrc.c -o binl/smlrc86
smlrcc -linux -Wall n2f.c -o binl/n2f
smlrcc -linux -Wall -DHOST_LINUX smlrcc.c -o binl/smlrcc
smlrcc -linux -Wall smlrl.c -o binl/smlrl
cd ucpp
smlrcc -linux -Wall -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c -o ../binl/smlrpp
cd ..

echo -= macOS 32 Bits =-
smlrcc -macos -Wall smlrc.c -o binm/smlrc
smlrcc -macos -Wall -DONLY8086 smlrc.c -o binm/smlrc86
smlrcc -macos -Wall n2f.c -o binm/n2f
smlrcc -macos -Wall -DHOST_MACOS smlrcc.c -o binm/smlrcc
smlrcc -macos -Wall smlrl.c -o binm/smlrm
cd ucpp
smlrcc -macos -Wall -DSTAND_ALONE -DUCPP_CONFIG arith.c assert.c cpp.c eval.c lexer.c macro.c mem.c nhash.c -o ../binm/smlrpp
cd ..

cd ..