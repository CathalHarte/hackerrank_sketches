
#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 12

static int printi(char **out, int i, int width, int pad)
{
    char print_buf[PRINT_BUF_LEN];
    register char *s;
    register int t, neg = 0, pc = 0;
    register unsigned int u = i;

    if (i == 0) 
    {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return prints (out, print_buf, width, pad);
    }


    s = print_buf + PRINT_BUF_LEN-1;
    *s = '\0';

    while (u) 
    {
        t = u % 10;
        *--s = t + '0';
        u /= 10;
    }

    if (neg) {
        if( width && (pad & PAD_ZERO) ) 
        {
            printchar (out, '-');
            ++pc;
            --width;
        }
        else {
            *--s = '-';
        }
    }

    return pc + prints (out, s, width, pad);
}


// brainwave
// I can know the lowest decimal place a number can have an effect
// Ah shit, wait no.


unsigned cafMod(unsigned A, unsigned B) 
{
    assert(B);
    unsigned X = B;
    
    while (X <= A / 2) 
    {
        X <<= 1;
    }
    while (A >= B) 
    {
        if (A >= X) A -= X;
        X >>= 1;
    }
    return A;
}

