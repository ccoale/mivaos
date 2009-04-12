#!/bin/sh
rm deploy/mivaos_x86.iso
cp bin/kernel.bin deploy/boot/kernel.bin
genisoimage -q -no-emul-boot -boot-load-size 4 -boot-info-table -R -b boot/grub/stage2_eltorito  -o ./deploy/mivaos_x86.iso ./deploy/
rm deploy/boot/kernel.bin
1>/dev/null
