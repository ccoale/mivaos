#!/bin/sh
rm deploy/mivaos_x86.iso
cp bin/kernel.bin deploy/boot/kernel.bin
genisoimage -q -R -b deploy/boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ./deploy/mivaos_x86.iso deploy/ 
1>/dev/null
