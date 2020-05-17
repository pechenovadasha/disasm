.name "zork"
.comment "just a basic living prog"
		
l2:	sti	r1,%150,%0
	and	r1,%-170,r1
live:	live	%1
	zjmp	%:live
toto:	st r15,-480
