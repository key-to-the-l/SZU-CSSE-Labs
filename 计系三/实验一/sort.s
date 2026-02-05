.data
arr: .word 8, 6, 3, 7, 1, 0, 9, 4, 5, 2
before: .asciiz "Before sort the array is:\n"
after: .asciiz "After sort the array is:\n"
CONTROL: .word 0x10000
DATA: .word 0x10008
SP: .word 0x300  # stack pointer

.text
main:
    # print before
    ld r16, CONTROL(r0)  # r16 <- M[CONTROL]
    ld r17, DATA(r0)  # r17 <- M[DATA]
    daddi r8, r0, 4  # r8 <- 4, CONTROL = 4
    daddi r9, r0, before  # r9 <- before
	sd r9, (r17)  # M[r17] <- r9
    sd r8, (r16)  # M[r16] <- r8, print before

    # print the array
    daddi r8, r0, 2  # r8 <- 2, CONTROL = 2
    daddi r2, r0, 10  # r2 <- 10, n = 10
    daddi r1, r0, 0  # r1 <- 0, i = 0
print1:
    dsll r3, r1, 3  # r3 <- (r1 << 3, logically), r3 = i * 8
    ld r9, arr(r3)  # r9 <- M[arr + r3], r9 = arr[i]
    sd r9, (r17)  # M[r17] <- r9, M[r17] = arr[i]
    sd r8, (r16)  # print arr[i]
	
    daddi r1, r1, 1  # r1 <- r1 + 1, i++
    bne r1, r2, print1  # goto print1 if r1 != r2, i != n

    # bubbleSort()
    ld r29, SP(r0)  # r29 <- M[SP], use r29 to maintain the stack pointer
    daddi r4, r0, arr  # para1: a[]
    daddi r5, r0, 10  # para2: n
    jal bubbleSort  # goto bubbleSort

    # print after
    daddi r8, r0, 4  # r8 <- 4, CONTROL = 4
    daddi r9, r0, after  # r9 <- after
    sd r9, (r17)  # M[r17] <- r9
	sd r8, (r16)  # M[r16] <- r8, print after
	
    # print the array
    daddi r8, r0, 2  # r8 <- 2, CONTROL = 2
    daddi r2, r0, 10  # r2 <- 10, n = 10
    daddi r1, r0, 0  # r1 <- 0, i = 0
print2:
    dsll r3, r1, 3  # r3 <- (r1 << 3), r3 = i * 8
    ld r9, arr(r3)  # r9 <- M[arr + i * 8]
    sd r9, (r17)  # M[r17] <- r9
    sd r8, (r16)  # M[r16] <- r8, print arr[i]
	
    daddi r1, r1, 1  # r1 <- r1 + 1, i++
    bne r1, r2, print2  # goto print2 if r2 != r1, loop if i != 10
    halt

# ----------------------------------------

bubbleSort:
    # backup
    daddi r29, r29, -24  # r29 <- r29 - 24, allocate stack frames for 3 ints
    sd $ra, 16(r29)  # store PC
    sd r16, 8(r29)  # store r16
    sd r17,0(r29)  # store r17

    dadd r22, r4, r0  # r22 <- r4, r2 = a[]
    daddi r23, r5, 0  # r23 <- r5, r23 = n

    and r18, r18, r0  # r18 <- r18 & r0, i = 0
loop1:
    # for (int i = 0; i < n; i++) 
    slt r10, r18, r23  # set r10 = 1 if r18 < r23, loop1 if i < n
    beq r10, r0, end1   # goto end1 if r10 == r0, break if i >= n
	
    daddi r19, r18, -1  # r19 <- r18 - 1, j = i - 1
loop2:
    # for (int j = i - 1; j >= 0; j--)
    slti r10, r19, 0  # set r10 = 1 if r19 < 0, not loop2 if j < 0
    bne r10, r0, end2  # goto end2 if r10 != r0, break if j < 0
	
    dsll r11, r19, 3  # r11 <- (r19 << 3), r11 = j * 8
    dadd r12, r22, r11  # r12 = r22 + r11, r12 = a + j * 8
    ld r13, 0(r12)  # r13 <- M[r12], r13 = a[j]
    ld r14, 8(r12)  # r14 <- M[r12 + 8], r14 = a[j + 1]
	
    # if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
    slt r10, r14, r13  # set r10 = 1 if r14 < r13, swap if a[j + 1] < a[j]
    beq r10, r0, end2  # goot end2 if r10 == r0, continue if a[j + 1] >= a[j]
	
    #swap(a[j], a[j + 1])
    dadd r4, r0, r12  # r4 <- r12, para1: a + j * 8
    daddi r5, r12, 8  # r5 <- r12 + 8, para2: a + (j + 1) * 8
    jal swap  # goto swap
	
    daddi r19, r19, -1  # r19 <- r19 - 1, j--
    j loop2  # goto loop2
	
end2:
    daddi r18,r18,1  # r18 <- r18 - 1, i--
    j loop1  # goto loop1

end1:
    # restore
    ld r17, 0(r29)  # restore r17
    ld r16, 8(r29)  # restore r16
    ld $ra, 16(r29)  # restore PC
    daddi r29, r29, 24  # recover the stack frames
    jr $ra  # return to M[PC]

# ----------------------------------------

swap:  
    # swap(a[i], a[j])
    ld r9, 0(r4)  # r9 <- M[r4], r9 = a[i]
    ld r10, 0(r5)  # r10 <- M[r5], r10 = a[j]
    sd r10, 0(r4)  # M[r4] <- r10, a[i] = r10
    sd r9, 0(r5)  # M[r5] <- r9, a[j] = r9
    jr $ra  # return to M[PC]
	
	