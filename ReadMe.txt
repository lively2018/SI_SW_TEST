1. Mytimer.c 설명

1. Timer를 초기화 한다.
2. Counter를 0으로 초기화한다.
3. Timer interrupt number와 interrupt handler를 등록한다. 
(interrupt handler에서 count를 1씩 증가시키고 count를 출력한다.)
4. Timer Interrupt를 enable한다.
	
2. 컴파일 방법
$ sparc-gaisler-elf-gcc -qbsp=leon3 -mcpu=leon3 -c mytimer.c -o mytimer.elf

3. 실행 방법
(monitor) s @script\myleon3.res 
