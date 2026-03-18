#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

const uint32_t MOD_POLY = 1033; 
int get_degree(uint32_t poly) {
    if (poly == 0) return -1;
    int deg = 0;
    while (poly >>= 1) deg++;
    return deg;
}

uint32_t poly_mult(uint32_t A, uint32_t B) {
    uint32_t res = 0;
    while (B > 0) {
        if (B & 1) res ^= A;
        A <<= 1;
        B >>= 1;
    }
    return res;
}

void poly_div(uint32_t A, uint32_t B, uint32_t &Q, uint32_t &R) {
    Q = 0;
    R = A;
    if (B == 0) return; 
    int degB = get_degree(B);
    while (R != 0 && get_degree(R) >= degB) {
        int shift = get_degree(R) - degB;
        Q ^= (1 << shift);
        R ^= (B << shift);
    }
}

uint32_t gf_inverse(uint32_t a) {
    if (a == 0) return 0;
    uint32_t r1 = MOD_POLY, r2 = a;
    uint32_t t1 = 0, t2 = 1;
    cout << "--- Bat dau tim nghich dao cua " << a << " ---\n";
    int step = 1;
    while (r2 != 0) {
        uint32_t q = 0, r = 0;
        poly_div(r1, r2, q, r); 
        uint32_t mult_res = poly_mult(q, t2);
        uint32_t q_dummy = 0, mult_res_mod = 0;
        poly_div(mult_res, MOD_POLY, q_dummy, mult_res_mod);
        uint32_t t_new = t1 ^ mult_res_mod;
        poly_div(t_new, MOD_POLY, q_dummy, t_new); 
        cout << "Buoc " << step << ":\n";
        cout << "  Chia: r1 = " << r1 << ", r2 = " << r2 << " -> Thuong q = " << q << ", Du r = " << r << "\n";
        cout << "  Nhan: q * t2 = " << q << " * " << t2 << " = " << mult_res << " -> mod m(x) = " << mult_res_mod << "\n";
        cout << "  Cap nhat t: t_new = " << t1 << " ^ " << mult_res_mod << " = " << t_new << "\n";
        r1 = r2;
        r2 = r;
        t1 = t2;
        t2 = t_new;
        step++;
    }

    cout << "=> Nghich dao cua " << a << " la " << t1 << "\n\n";
    return t1;
}

int main() {
    uint32_t a = 523;
    uint32_t b = 1015;
    
    uint32_t inv_a = gf_inverse(a);
    uint32_t inv_b = gf_inverse(b);
    
    uint32_t q = 0, check_a = 0, check_b = 0;
    poly_div(poly_mult(a, inv_a), MOD_POLY, q, check_a);
    poly_div(poly_mult(b, inv_b), MOD_POLY, q, check_b);
    
    cout << "Kiem tra a * a^-1 = " << check_a << std::endl;
    cout << "Kiem tra b * b^-1 = " << check_b << std::endl;

    return 0;
}