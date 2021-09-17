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
ldi temp,(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(0<<COM00)|(1<<CS00)|(0<<CS01)|(0<<CS02) ;FAST PWM wthout prescalling and clear on compare
out tccr0,temp ;Timer/Counter Control

ldi temp,255	
out ocr0,temp ;Output Compare Register   (выставляет прерывания в 12 адрес) 

ldi temp,85 
out OCR1AH,temp ;Output Compare Register 1 A –1/3 period
ldi temp,0
out OCR1AL,temp ;Output Compare Register 1 A –

ldi temp, (1<<WGM12)|(1<<CS10) ;no prescaling 
out tccr1b,temp ;control registr

ldi temp,(1<<OCIE1A)
out TIMSK,temp ;Interrupt Enable


Enable_interrupt:
sei	 ; Разрешить прерывания
rjmp Enable_interrupt


Ignition:
out OCR0,value
inc value
rjmp return_interrupt



return_interrupt:
reti ;возвращение из прерывания