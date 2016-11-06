#ifdef __UNREAL__
// Default IRQ5 ISR that causes the existing/old IRQ5 ISR to run.
// It will be linked if there's no other implementation of __Irq5Isr() in the program.
//
// If a custom IRQ5 ISR is needed, define your own __Irq5Isr() in the program
// and it will be linked instead of this default IRQ5 ISR.
int __Irq5Isr(void)
{
  // If we handle IRQ5 here:
  //   1. Do I/O.
  //   2. Send EOI to PIC.
  //   3. return 0.
  // If we don't handle IRQ5 here and want the existing/old IRQ5 ISR to run:
  //   1. return 1.
  return 1;
}
#endif
