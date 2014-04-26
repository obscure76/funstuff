#include <header.h>

int count2sI(int num) {
        
int countof2s = 0, digit = 0;
        
int j = num, seendigits=0, position=0, pow10_pos = 1;
int pow10_posMinus1;
        
/* maintaining this value instead of calling pow() is an 6x perf
        
* gain (48s -> 8s) pow10_posMinus1. maintaining this value
        
* instead of calling Numof2s is an 2x perf gain (8s -> 4s).
        
* overall > 10x speedup */
        
while (j > 0) {
                
digit = j % 10;
                
pow10_posMinus1 = pow10_pos / 10;
                
countof2s += digit * position * pow10_posMinus1;
                
/* we do this if digit <, >, or = 2
                
* Digit < 2 implies there are no 2s contributed by this         
                
* digit.
                
* Digit == 2 implies there are 2 * numof2s contributed by
                
* the previous position + num of 2s contributed by the
                
* presence of this 2 */
                
if (digit == 2) {
                        
countof2s += seendigits + 1;
                
}
                
/* Digit > 2 implies there are digit * num of 2s by the prev.
                
* position + 10^position */
                
else if(digit > 2) {
                        
countof2s += pow10_pos;
                
}
                
seendigits = seendigits + pow10_pos * digit;
                
pow10_pos *= 10;
                
position++;     
                
j = j / 10;
        
}
        
return(countof2s);
}

int main()
{
    printf("The num of twos in %d are %d",278, count2sI(278));
    return 0;
}

