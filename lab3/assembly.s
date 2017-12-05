	.file	"lab3.c"
	.text
	.global changeScore

	.extern p1Score
	.extern p2Score
	.extern p1Stats
	.extern p2Stats
	.extern printScore
	.extern scoreAt

	.data

changeScore:
	cmp #0,r12
	jz player1Score
	add.b #1,&p2Score
	mov &p2Stats,r12
	mov.b &p2Score,3[r12]
	mov #104,r13
	call #printScore
	jmp end

player1Score:
	add.b #1,&p1Score
	mov &p1Stats,r12
	mov.b &p1Score,3[r12]
	mov #1,r13
	call #printScore
	jmp end

end:
	ret
