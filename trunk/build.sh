genisoimage -q -R -b bin/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o ./deploy/mivaos_x86.iso ./ 
1>/dev/null
