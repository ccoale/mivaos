echo off
echo Building Boot-loader...
nasm -f bin source/boot/boot.asm -o bin/boot/boot.bin
echo Done.
@pause