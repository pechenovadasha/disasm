.name "zork"
.comment "just a basic living prog"

sti r1,%150,%0
and r1,%-170,r1
live %1
zjmp %-5
st r15,-480
