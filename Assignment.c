#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

int main (int argc, char* argv[])
{
	// Create the universe..
	bdd_manager bddm = bdd_init();	

	// make 3 variables x0,x1,x2 (in that order)
	bdd x0 = bdd_new_var_last(bddm);
	bdd x1 = bdd_new_var_last(bddm);
	bdd x2 = bdd_new_var_last(bddm);
	bdd x3 = bdd_new_var_last(bddm);
	bdd x4 = bdd_new_var_last(bddm);
	bdd x5 = bdd_new_var_last(bddm);

	// compute a = (x0.x1) b = (x2.x3) c = (x4.x5)
	bdd a  = bdd_and (bddm,x0,x1);
	bdd b  = bdd_and (bddm,x2,x3);
	bdd c  = bdd_and (bddm,x4,x5);	
		

	// compute d = !a.!b e = d.!c 
	bdd x = bdd_not (bddm, a);
	bdd y = bdd_not (bddm, b);
	bdd z = bdd_not (bddm, c);
	bdd d = bdd_and (bddm,x,y);
	bdd e = bdd_and (bddm,d,z);

	printf("----------------------------------------------------\n");

	// print e
	bdd_print_bdd(bddm,e,NULL, NULL,NULL, stdout);

	
	return(0);
}

