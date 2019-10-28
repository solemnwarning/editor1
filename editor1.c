#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <poll.h>

#define T tcsetattr(1, TCSANOW, &t);
#define S(d,s) memmove(b + d, b + s, m - s)
#define A(x) if(m + (x) > X && !(b = realloc(b, X += x))) abort();
#define D(v,a,d) v = ac > a ? atoi(av[a]) : d;
#define f t.c_lflag
#define N(x, v) (!y && (y = j[2] == x) && (o = v))
#define E sprintf(u, "ERR: %s", strerror(errno)) & 0
#define P printf

char *b = NULL, *p, j[16] = { 0 } , u[256] = "OK", *pp;
unsigned X = 0, m = 0, o = 0, s, w, h, n, i, z, y;

unsigned Y() {
	for(; z; y += p[--z] == '\t');
	return y * 7;
}

int r() {
	P("\x1B[2J\x1B[%u;1f\x1B[7m", h);
	
	for(i = z = s = 0; (s < w && putchar(u[z] ? u[z++] : ' ')) || !P("\x1B[0m"); s++);
	
	do {
		for(n = s = 0, p = b; (s < o && ((
			b[s] == '\n' && ++n + 2 >= h && (
			p = strchr(p, '\n') + 1)) || p)) || (
			P("\x1B[H") && 0);
			
			s++
		);
		
		for(n = s = y = 0; (s + 1 < h && ((!i && p - b < m) || p - b < o)) && (
			(n == 0 && p - b <= o && (p + strcspn(p, "\n")) - b >= o && (
				z = o - (p - b)) + 2 + Y() > w && p++
			) ||
			
			(((!(y = 0) && (((n += *p == '\t' ? 8 : 1) > w && (
				p += strcspn(p, "\n")) &&
				(p -= *p != '\n') &&
				
				P("\x1B[%u;1f", ++s + 1) &&
				!(n = 0)
			) ||
			
			(!(*p == '\n' && (n = 0)) && (
				(*p != '\n' || ++s < h) && putchar(*p))))) && 0) || p++));
		);
	} while(!(i++));
	
	return s = 1;
}

int M() {
	for(i = z = 0, p = b, pp = 0; !(y = (
		N(67, o + (m > o)) ||
		N(68, o - (o > 0)))) &&
		
		z < o && ((b[z] == '\n' && (pp = p) && (
			p = b + z + 1) &&
			!(i = 0)
		) ||
		
		(++i));
		
		z++
	);
	
	do {
		for(z = 0; (z < i && pp && pp[z] != '\n' && pp[z] && ++z) || ((
			(pp > p && (N(66, (pp - b) + z) || 1)) ||
			(pp && N(65, (pp - b) + z))) && 0);
		);
	} while(pp < p && (pp = memchr(p, '\n', m - (p - b))) && pp++);
	
	return y && r();
}

int main(int ac, char **av) {
	if(ac < 2 || ac > 4) {
		P("Usage: %s <file> [widh] [height]\n", *av);
		return 1;
	}
	
	D(w, 2, 80);
	D(h, 3, 24);
	
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	
	FILE *fh = fopen(av[1], "r");
	if(!fh && !(E)) { }
	else{
		do {
			A(512);
		}
		
		while(((m += fread(b + m, 1, 512, fh)) != s && (
			s = m)) || (
			
			ferror(fh) && (
				E || (m = 0))
			)
		);
		
		fclose(fh);
	}
	
	struct termios t;
	tcgetattr(1, &t);
	f &= ~(s = f & (ICANON | ECHO));
	T f |= s;
	
	for(; *j != 5; ) {
		r();
		
		if((*j = getchar()) == 127 && o) {
			S(o - 1, o);
			o--;
			m--;
		} else if(*j == 27) {
			struct pollfd p = { 1, POLLIN, 0 } ;
			
			for(s = 1; s < 16 && poll(&p, 1, 100) > 0 && (
				(!((j[s++] = getchar()) == 27 && (
					s = 1
				) && 0) && j[1] == 91 && !(s == 3 && M()) && (
					s == 4 && j[2] == 51 && o < m && S(o, o + 1) &&
						m-- &&
						r())
					) ||
				1); 
			);
		} else if(*j == 23) {
			strcpy(u, "OK");
			
			for(fh = fopen(av[1], "w"), s = y = 0; (fh || E) && ((((
				s += fwrite(b + s, 1, m - s, fh)) != y &&
				(y = s)) ||
				
				(ferror(fh) && E)) || (
					fclose(fh) && 0));
			);
		} else{
			A(1) S(o + 1, o);
			m++;
			b[o++] = *j;
		}
	}
	
	T P("\x1B[%u;1f\n", h);
	
	return 0;
}
