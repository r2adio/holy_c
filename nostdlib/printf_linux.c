// writing a char* to stdout, w/o any library.
// os: arch linux
// binary size: 9128B (~9KB)
//
// command: cc -static -nostdlib -fno-stack-protector printf.c
// -fno-stack-protector: required for arch, to disable __stack_chk_fail

int _start(void) {
  const char hello[] = "Hello, world!\n";
  // write(STDOUT_FILENO, hello, sizeof(hello) - 1);
  asm volatile("mov $1, %%rax\n\t" // put syscall number for write -> 1,
                                   // in register `rax`

               "mov $1, %%rdi\n\t" // set register `rdi` with file descriptor
                                   // stdout (fd=1)

               "lea %0, %%rsi\n\t" // loads memory addr of str in register `rsi`
                                   // lea -> load effective address instruction

               "mov $14, %%rdx\n\t" // writing no. of char in register `rdx`

               "syscall\n\t" // calls the syscall instruction
               :             // output to capture, here none
               : "m"(hello)  // sends arguments into the assembly code

               : "%rax", "%rdi", "%rsi",
                 "%rdx"); // notifying compiler which registers being used

  // exit system call
  asm volatile(
      "mov $60, %%rax\n\t" // set sys call numebr: 60 ->(call number for exit)
      "mov $0, %%rdi\n\t"  // set exit code: 0 ->(terminated successfully)
      "syscall\n\t" ::
          : "%rax", "%rdi");

  return 0;
}
