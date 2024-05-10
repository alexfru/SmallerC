# Test suite for 8086
# Usage: make FILE.com
# Prereqs: Installed SmallerC and DOSBOX
# Example: make c99.com

%.com: %.c .AWAYS
	smlrcc -8086 -dost -o $@ $<
	dosbox -C "mount c: ./" -C "c:" -C "$@"

%.exe: %.c .AWAYS
	smlrcc -8086 -doss -o $@ $<
	dosbox -C "mount c: ./" -C "c:" -C "$@"

%.s: %.c .AWAYS
	smlrcc -S -8086 -o $@ $<


%.o: %.c .AWAYS
	smlrcc -S -8086 -o $(patsubst %.o,%.s,$@) $<
	nasm -f elf -o $@ $(patsubst %.o,%.s,$@)

clean:
	rm -f *.com *.exe *.s *.o

.AWAYS: