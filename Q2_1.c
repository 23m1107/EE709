#include <stdlib.h>
#include <stdio.h>
#include <bdduser.h>

int main (int argc, char* argv[])
{
	// Create the universe..
	bdd_manager bddm = bdd_init();	

	// make 3 variables u0,u1,u2, u3 and their complements
	bdd u0 = bdd_new_var_last(bddm);
	bdd u1 = bdd_new_var_last(bddm);
	bdd u2 = bdd_new_var_last(bddm);
	bdd u3 = bdd_new_var_last(bddm);
	bdd not_u3 = bdd_not (bddm, u3);
	bdd not_u2 = bdd_not (bddm, u2);
	bdd not_u1 = bdd_not (bddm, u1);
	bdd not_u0 = bdd_not (bddm, u0);

  // a=(!u3).(!u2).(!u1).(u0)
	bdd a1 = bdd_and (bddm, not_u3, not_u2);
	bdd a2 = bdd_and (bddm, not_u1, u0);
	bdd a = bdd_and (bddm, a1, a2);

  // b=(!u3).(!u2).(u1).(!u0)
	bdd b1 = bdd_and (bddm, not_u3, not_u2);
	bdd b2 = bdd_and (bddm, not_u0, u1);
	bdd b = bdd_and (bddm, b1, b2);

  // c=(!u3).(u2).(!u1).(!u0)
	bdd c1 = bdd_and (bddm, not_u1, not_u0);
	bdd c2 = bdd_and (bddm, not_u3, u2);
	bdd c = bdd_and (bddm, c1, c2);

  // d=(u3).(!u2).(!u1).(!u0)
	bdd d1 = bdd_and (bddm, not_u1, not_u0);
	bdd d2 = bdd_and (bddm, not_u2, u3);
	bdd d = bdd_and (bddm, d1, d2);

  // e_spec = a+b+c+d
  // c1_spec = c+d
  // c0_spec = b+d
	bdd e1 = bdd_or (bddm, a, b);
	bdd e2 = bdd_or (bddm, c, d);
  
	bdd e_spec = bdd_or (bddm, e1, e2);
	bdd c1_spec = bdd_or (bddm, c,d);
	bdd c0_spec = bdd_or (bddm, b,d);


  // e_impl = u3+u2+u1+u0
  // c1_impl = u3+u2
  // c0_impl = u3+u1
	bdd e3 = bdd_or(bddm, u3, u2);
	bdd e4 = bdd_or(bddm, u1, u0);
  
	bdd e_impl = bdd_or(bddm, e3, e4);
	bdd c1_impl = bdd_or(bddm, u3, u2);
	bdd c0_impl = bdd_or(bddm, u3, u1);
	
	
  //xnor(x,y) = 1 means x=y
 bdd e_check =   bdd_xnor(bddm, e_spec, e_impl);
 bdd c1_check =   bdd_xnor(bddm, c1_spec, c1_impl);
 bdd c0_check =   bdd_xnor(bddm, c0_spec, c0_impl);
 
 
 bdd_print_bdd(bddm,e_check,NULL, NULL,NULL, stdout);
 printf("-----------e_check------\n");
 bdd_print_bdd(bddm,c1_check,NULL, NULL,NULL, stdout);
 printf("-------------c1_check----\n");
 bdd_print_bdd(bddm,c0_check,NULL, NULL,NULL, stdout);
 printf("---------c0_check--------\n");
 
//collecting all don't care condidtions
  bdd g1 = bdd_and(bddm, u3, u2);
  bdd g2 = bdd_and(bddm, u1, u0);
  bdd g3 = bdd_and(bddm, u2, u0);
  bdd g4 = bdd_and(bddm, u3, u0);
  bdd g5 = bdd_and(bddm, u2, u1);
  bdd g6 = bdd_and(bddm, u3, u1);
  
  bdd g7 = bdd_or(bddm, g1, g2);
  bdd g8 = bdd_or(bddm, g3, g4);
  bdd g9 = bdd_or(bddm, g5, g6);
  
  bdd g10 = bdd_or(bddm, g7, g8);
  bdd g = bdd_or(bddm, g9, g10); 
  
  bdd e_final = bdd_or(bddm, g, e_check);
  bdd c1_final = bdd_or(bddm, g, c1_check);
  bdd c0_final = bdd_or(bddm, g, c0_check);
    
  bdd h = bdd_and(bddm, e_final, c0_final);
  bdd result = bdd_and(bddm, h, c1_final);
  
  if(e_final == bdd_one(bddm))
  {
    printf("e_spec = e_impl\n");
  }
  else
  {
    printf("e_spec != e_impl\n");
  }
  
    if(c0_final == bdd_one(bddm))
  {
    printf("c0_spec = c0_impl\n");
  }
  else
  {
    printf("c0_spec != c0_impl\n");
  }
  
    if(c1_final == bdd_one(bddm))
  {
    printf("c1_spec = c1_impl\n");
  }
  else
  {
    printf("c1_spec != c1_impl\n");
  }
  
  if(result == bdd_one(bddm))
  {
    printf("done\n");
    bdd_print_bdd(bddm,result,NULL, NULL,NULL, stdout);
  }
  else 
  {
    printf("not done\n");
  }
	printf("----------------------------------------------------\n");
return (0);
}
