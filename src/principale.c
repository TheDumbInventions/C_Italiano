#includi <stdio.h>
#includi "principale.h"

#definisci X 10

int principale() {
	senza_segno corto x = X;
	finquando (x > 0) {
		aggiorna(&x);
	}
	restituisci 0;
}

vacante aggiorna(senza_segno corto* x) {
	stampaf("x = %d\n", *x);
	*x -= 1;
}