INCLUDE C:\Irvine\Irvine32.inc
INCLUDELIB C:\Irvine\Irvine32.lib
INCLUDELIB C:\Irvine\kernel32.lib
INCLUDELIB C:\Irvine\user32.lib

.data
playagain byte " If you want to play again press 1 or enter any key to end the game ",0
strtingmsg byte "              TIC TAC TOE            ",0
ticmsg0 byte "  ________________________________________________________________________________  ", 0  
ticmsg1 byte " |  ______         _____     _____            ____     ________  ______    ____   | ", 0
ticmsg2 byte " |    |      |    /            |     //\\    /             |     | __ |   |       | ", 0
ticmsg3 byte " |    |      |   |             |    //--\\  |              |     ||__||   |----   | ", 0
ticmsg4 byte " |    |      |    \___         |   //    \\  \___          |     |____|   |____   | ", 0
ticmsg5 byte " |________________________________________________________________________________| ", 0
brdmsg byte "Enter the value between 1-9 according to the above table",0
horizontalLine BYTE '-----------',0
row1 BYTE ' 1 ', '|', ' 2 ', '|', ' 3 ' ,0
row2 BYTE ' 4 ', '|', ' 5 ', '|', ' 6 ' ,0
row3 BYTE ' 7 ', '|', ' 8 ', '|', ' 9 ' ,0
player1 byte 'X'
player2 byte 'O'
currentPlayer byte 'X'
value byte ?
moveFrom byte ?
againmsg byte " The place is already filled please select another place ",0
againmsg2 byte " wrong input!!! Enter the correct number ",0
movemsg byte " (MOVE MODE) Select your piece to MOVE FROM (1-9): ",0
invalidmove byte " That is not your piece! Choose your own mark: ",0
winmsg byte " Player Win ",0
plmsg byte " PLAYER'S TURN: ",0
turnCount dword 0

.code
; --- Reset the board values to original numbers ---
reset PROC
    mov esi, offset row1
    mov byte ptr [esi+1], '1'
    mov byte ptr [esi+5], '2'
    mov byte ptr [esi+9], '3'
    mov esi, offset row2
    mov byte ptr [esi+1], '4'
    mov byte ptr [esi+5], '5'
    mov byte ptr [esi+9], '6'
    mov esi, offset row3
    mov byte ptr [esi+1], '7'
    mov byte ptr [esi+5], '8'
    mov byte ptr [esi+9], '9'
    mov al, 'X'
    mov currentPlayer, al
    mov turnCount, 0
    ret
reset endp

boxprinter PROC
    call crlf
    mov edx, OFFSET row1
    call WriteString
    call crlf
    mov edx, OFFSET horizontalLine
    call WriteString
    call crlf
    mov edx, OFFSET row2
    call WriteString
    call crlf
    mov edx, OFFSET horizontalLine
    call WriteString
    call crlf
    mov edx, OFFSET row3
    call WriteString
    call crlf
    mov edx, OFFSET horizontalLine
    call WriteString
    call crlf
    mov edx, offset brdmsg
    call WriteString
    call crlf
    ret
boxprinter ENDP

; --- Logic to remove a piece when a player has more than 3 moves ---
removeOldPiece PROC
    mov al, moveFrom
    mov ah, currentPlayer
    
    cmp al, '1'
    je r1
    cmp al, '2'
    je r2
    cmp al, '3'
    je r3
    cmp al, '4'
    je r4
    cmp al, '5'
    je r5
    cmp al, '6'
    je r6
    cmp al, '7'
    je r7
    cmp al, '8'
    je r8
    cmp al, '9'
    je r9
    jmp wrong_input

r1: mov esi, offset row1
    cmp byte ptr [esi+1], ah
    jne wrong_owner
    mov byte ptr [esi+1], '1'
    ret
r2: mov esi, offset row1
    cmp byte ptr [esi+5], ah
    jne wrong_owner
    mov byte ptr [esi+5], '2'
    ret
r3: mov esi, offset row1
    cmp byte ptr [esi+9], ah
    jne wrong_owner
    mov byte ptr [esi+9], '3'
    ret
r4: mov esi, offset row2
    cmp byte ptr [esi+1], ah
    jne wrong_owner
    mov byte ptr [esi+1], '4'
    ret
r5: mov esi, offset row2
    cmp byte ptr [esi+5], ah
    jne wrong_owner
    mov byte ptr [esi+5], '5'
    ret
r6: mov esi, offset row2
    cmp byte ptr [esi+9], ah
    jne wrong_owner
    mov byte ptr [esi+9], '6'
    ret
r7: mov esi, offset row3
    cmp byte ptr [esi+1], ah
    jne wrong_owner
    mov byte ptr [esi+1], '7'
    ret
r8: mov esi, offset row3
    cmp byte ptr [esi+5], ah
    jne wrong_owner
    mov byte ptr [esi+5], '8'
    ret
r9: mov esi, offset row3
    cmp byte ptr [esi+9], ah
    jne wrong_owner
    mov byte ptr [esi+9], '9'
    ret

wrong_owner:
    mov edx, offset invalidmove
    call WriteString
    call readchar
    mov moveFrom, al
    jmp removeOldPiece
wrong_input:
    mov edx, offset againmsg2
    call WriteString
    call readchar
    mov moveFrom, al
    jmp removeOldPiece
removeOldPiece ENDP

inputPlayer PROC
    ; If turn count is 6 or more, it means X and O both have 3 pieces
    cmp turnCount, 6
    jl just_input

    mov edx, offset movemsg
    call WriteString
    call readchar
    mov moveFrom, al
    call removeOldPiece
    call clrscr
    call title1
    call boxprinter

just_input:
    mov al, currentPlayer
    call writechar
    mov edx, offset plmsg
    call WriteString
    call readchar
    mov value, al
    call crlf
    ret
inputPlayer ENDP

updatetable PROC 
    mov al, currentPlayer
    cmp value, '1'
    je replace1
    cmp value, '2'
    je replace2
    cmp value, '3'
    je replace3
    cmp value, '4'
    je replace4
    cmp value, '5'
    je replace5
    cmp value, '6'
    je replace6
    cmp value, '7'
    je replace7
    cmp value, '8'
    je replace8
    cmp value, '9'
    je replace9
    jmp again2

replace1:
    mov esi, offset row1
    mov bl, [esi+1]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+1], al 
    jmp rr
replace2:
    mov esi, offset row1
    mov bl, [esi+5]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+5], al 
    jmp rr
replace3:
    mov esi, offset row1
    mov bl, [esi+9]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+9], al 
    jmp rr
replace4:
    mov esi, offset row2
    mov bl, [esi+1]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+1], al 
    jmp rr
replace5:
    mov esi, offset row2
    mov bl, [esi+5]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+5], al 
    jmp rr
replace6:
    mov esi, offset row2
    mov bl, [esi+9]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+9], al 
    jmp rr
replace7:
    mov esi, offset row3
    mov bl, [esi+1]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+1], al 
    jmp rr
replace8:
    mov esi, offset row3
    mov bl, [esi+5]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+5], al 
    jmp rr
replace9:
    mov esi, offset row3
    mov bl, [esi+9]
    cmp bl, 'X'
    je again
    cmp bl, 'O'
    je again
    mov [esi+9], al 
   
rr:
    inc turnCount
    ret

again2:
    mov edx, offset againmsg2
    call WriteString
    call crlf
    call inputPlayer
    jmp updatetable

again:
    mov edx, offset againmsg
    call WriteString
    call crlf
    call inputPlayer
    jmp updatetable
updatetable endp

changeturn PROC
    mov al, currentPlayer
    cmp al, player1
    je chng
    mov al, player1
    mov currentPlayer, al
    jmp e
chng:
    mov al, player2
    mov currentPlayer, al
e:
    ret
changeturn ENDP

win PROC
    ; Row 1
    mov esi, offset row1
    mov bl, [esi+1]
    cmp bl, [esi+5]
    jne check_row2
    cmp bl, [esi+9]
    je w
check_row2:
    mov esi, offset row2
    mov bl, [esi+1]
    cmp bl, [esi+5]
    jne check_row3
    cmp bl, [esi+9]
    je w
check_row3:
    mov esi, offset row3
    mov bl, [esi+1]
    cmp bl, [esi+5]
    jne check_col1
    cmp bl, [esi+9]
    je w
check_col1:
    mov esi, offset row1
    mov bl, [esi+1]
    mov esi, offset row2
    cmp bl, [esi+1]
    jne check_col2
    mov esi, offset row3
    cmp bl, [esi+1]
    je w
check_col2:
    mov esi, offset row1
    mov bl, [esi+5]
    mov esi, offset row2
    cmp bl, [esi+5]
    jne check_col3
    mov esi, offset row3
    cmp bl, [esi+5]
    je w
check_col3:
    mov esi, offset row1
    mov bl, [esi+9]
    mov esi, offset row2
    cmp bl, [esi+9]
    jne check_diag1
    mov esi, offset row3
    cmp bl, [esi+9]
    je w
check_diag1:
    mov esi, offset row1
    mov bl, [esi+1]
    mov esi, offset row2
    cmp bl, [esi+5]
    jne check_diag2
    mov esi, offset row3
    cmp bl, [esi+9]
    je w
check_diag2:
    mov esi, offset row1
    mov bl, [esi+9]
    mov esi, offset row2
    cmp bl, [esi+5]
    jne no_win
    mov esi, offset row3
    cmp bl, [esi+1]
    je w
no_win:
    ret
w:
    call clrscr
    call boxprinter
    mov al, currentPlayer
    call writechar
    mov edx, offset winmsg
    call WriteString
    call crlf
    mov edx, offset playagain
    call WriteString
    call readint
    cmp eax, 1
    je restart_game
    invoke ExitProcess, 0
restart_game:
    call reset
    jmp start_main  ; Now using the global label jump
win ENDP

title1 PROC
    mov edx, offset ticmsg0
    call WriteString
    call crlf
    mov edx, offset ticmsg1
    call WriteString
    call crlf
    mov edx, offset ticmsg2
    call WriteString
    call crlf
    mov edx, offset ticmsg3
    call WriteString
    call crlf
    mov edx, offset ticmsg4
    call WriteString
    call crlf
    mov edx, offset ticmsg5
    call WriteString
    ret 
title1 endp

main PROC
start_main::  ; Double-colon makes this label global/accessible from 'win'
    
game_loop:
    call clrscr
    call title1
    call crlf
    call boxprinter
    call inputPlayer
    call updatetable
    
    call win
    call changeturn
    jmp game_loop
main ENDP
end main