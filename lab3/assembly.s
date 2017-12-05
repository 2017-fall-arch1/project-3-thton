	.text
	.global updateScore

	.extern p1Score
	.extern p2Score
	.extern p1Stats
	.extern p2Stats
	.extern printScore
	.extern scoreAt

	.data

updateScore:
	cmp #0,r12
	jz player1Score
	add.b #1,&p2Score
	mov.b &p2Score,3[p2Stats]
	mov &p2Stats,r12
	mov #1,r13
	call #printScore
	jmp end

player1Score:
	add.b #1,&p1Score
	mov.b &p1Score,3[p1Stats]
	mov &p1Stats,r12
	mov #1,r13
	call #printScore
	jmp end

end:
	ret
	
