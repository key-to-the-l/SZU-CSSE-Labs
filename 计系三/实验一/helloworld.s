.data
string: .asciiz "Hello World"
CONTROL: .word32 0x10000
DATA: .word32 0x10008

.text
main:
    lwu r30, DATA(r0)  # r30 <- M[0x10000]
	daddi r31, r0, string  # r31 <- string
	sd r31, (r30)  # M[r30] <- r31, store the string
	
	lwu r30, CONTROL(r0)  # r30 <- M[0x10000]
	daddi r31, r0, 4  # r31 <- 4
	sd r31, (r30)  # M[r30] <- 4, CONTROL = 4
	
	halt