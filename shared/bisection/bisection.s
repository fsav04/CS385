.text
.global _start
.extern printf

_start:
adr x4, b
adr x3, a
adr x5, tau
adr x6, two
adr x7, yint
adr x8, N
ldr x2, [x8] 
ldr x22, =coefficients
ldr d3, [x3, xzr]
ldr d2, [x4, xzr]
ldr d5, [x5, xzr]
ldr d8, [x6, xzr]
ldr d20, [x7, xzr]
mov x8, 0
mov x18, 8
mov x7, 0
    
    loop:
fsub d6, d2, d3
fcmp d6, d5
b.lt output 
fadd d7, d3, d2
fdiv d7, d7, d8    
fmov d9, d7    
fmov d18, d7       
mov x16, 0
b funcgety            
    
    checker:
fcmp d10, d20  
b.eq output
mov x16, 1     
fmov d15, d10 
fmov d9, d3 
b funcgety        

        
    coeff1:
fmov d3, d18
b loop

    coeff2: 
fmov d2, d18
b loop

    addf:
fmul d13, d12, d11   
fadd d10, d10, d13
sub x19, x19, 1
mul x10, x19, x18
mov x20, x19
b if1

    subf:
fmul d13, d12, d11   
fsub d10, d10, d13
sub x19, x19, 1
mul x10, x19, x18
mov x20, x19
b if1
       
    funcgety:
mov x19, x2
ldr d10, [x22, xzr]      
sub x19, x19, 1         
mul x10, x19, x18       
mov x20, x19          

    if1:
cmp x19, 1
b.lt flip
ldr d11, [x22, x10]  
cmp x20, 1
b.eq end
fmul d12, d9, d9      
sub x20, x20, 2      

    else:
cmp x20, xzr
b.le addf
b go

    go:
fmul d12, d12, d9   
sub x20, x20, 1    
b else

    flip:
cmp x16, xzr
b.eq checker
fmul d17, d10, d15 
fcmp d17, d20    
b.lt coeff2
b coeff1
    
    output:
adr x0, print_num
fmov d0, d9 
bl printf
bl exit

    end:
fmov d12, d9
b addf
    
    exit:
mov x0, 0
mov w8, #93
svc 0
    
.data
    coefficients: .double 0.2, 3.1, -0.3, 1.9, 0.2
    N: .dword 5
    yint: .double 0
    two: .double 2.0
    tau: .double .00001
    a: .double -1.0
    b: .double 1.0
    print_num: .ascii "The Y-intercept is 0 and the root is %lf\n"

.end

