#debut du mega truc qu'il est trop dur a faire

.name "Jumper !"
.comment "en fait C forker !"

gobepc:	st r1,:buff
	st r6,-4
	ld :buff,r1
debut:	ld %0,r7
	zjmp %:gobepc
buff:	st r1,r1
