.include "m16def.inc"

.def temp=r16
.def value=r17


.org 12
jmp Ignition


;;;;; stack initialization ;;;;;;;

ldi temp, Low(RAMEND) 
out SPL, temp
ldi temp, High(RAMEND)
out SPH, temp
sbi DDRB,3  ;on out
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

start:
sbi PORTB,3  ;Port B Data Register
ldi temp,(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(0<<COM00)|(1<<CS00)|(0<<CS01)|(0<<CS02) 
out tccr0,temp 

ldi temp,255	
out ocr0,temp 

ldi temp,85 
out OCR1AH,temp 
ldi temp,0
out OCR1AL,temp 

ldi temp, (1<<WGM12)|(1<<CS10) 
out tccr1b,temp

ldi temp,(1<<OCIE1A)
out TIMSK,temp 


Enable_interrupt:
sei	 ; Разрешить прерывания
rjmp Enable_interrupt


Ignition:
out OCR0,value
inc value
rjmp return_interrupt



return_interrupt:
reti ;возвращение из прерывания
