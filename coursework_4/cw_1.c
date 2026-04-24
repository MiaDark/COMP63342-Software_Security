#include <z3.h>
#include <stdio.h>

int main() {
    Z3_config cfg = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(cfg);
    Z3_del_config(cfg);

    Z3_sort s = Z3_mk_fpa_sort_64(ctx); 
    Z3_ast rm = Z3_mk_fpa_rne(ctx);

    Z3_ast x = Z3_mk_fpa_numeral_double(ctx, 0.1, s); // constraints
    Z3_ast y = Z3_mk_fpa_numeral_double(ctx, 0.2, s); // constraints
    Z3_ast w = Z3_mk_fpa_numeral_double(ctx, 0.3, s); // constraints
    Z3_ast one = Z3_mk_fpa_numeral_double(ctx, 1.0, s); // constraints

    Z3_ast z = Z3_mk_fpa_add(ctx, rm, x, y); // constraints
    Z3_ast a = Z3_mk_fpa_sub(ctx, rm, x, y); // constraints
    Z3_ast b = Z3_mk_fpa_mul(ctx, rm, x, y); // constraints
    Z3_ast c = Z3_mk_fpa_div(ctx, rm, x, y); // constraints

    Z3_ast p1 = Z3_mk_fpa_eq(ctx, w, z); // properties

    Z3_ast a_plus_b = Z3_mk_fpa_add(ctx, rm, a, b); // properties
    Z3_ast sum_abc = Z3_mk_fpa_add(ctx, rm, a_plus_b, c); // properties
    Z3_ast p2 = Z3_mk_fpa_leq(ctx, sum_abc, one); // properties

    Z3_ast args[2] = {p1, p2};
    Z3_ast p = Z3_mk_and(ctx, 2, args);
    Z3_ast not_p = Z3_mk_not(ctx, p); // the three lines represent the encoding of C AND notP

    Z3_solver sol = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, sol);
    Z3_solver_assert(ctx, sol, not_p); // solve

    if (Z3_solver_check(ctx, sol) == Z3_L_TRUE) {
        printf("Result: SAT\n");
    } else {
        printf("Result: UNSAT\n");
    }

    Z3_solver_dec_ref(ctx, sol);
    Z3_del_context(ctx);
    return 0;
}