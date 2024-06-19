all: kernel.elf

kernel.elf: main.o
	ld.lld $(LDFLAGS) --entry KernelMain -z norelro --image-base 0x100000 --static -o $@ $^

main.o: main.cpp
	clang++ $(CPPFLAGS) -O2 --target=x86_64-elf -fno-exceptions -ffreestanding -c $<

clean:
	rm *.o kernel.elf
