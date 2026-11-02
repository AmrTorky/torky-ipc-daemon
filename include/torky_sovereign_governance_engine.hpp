#ifndef TORKY_SOVEREIGN_GOVERNANCE_ENGINE_HPP
#define TORKY_SOVEREIGN_GOVERNANCE_ENGINE_HPP

#include <cmath>
#include <cstdint>
#include <algorithm>

namespace torky::sovereign::engine {

    inline constexpr double L_A_NM            = 0.36787944117144233;
    inline constexpr double EPSILON_NM2       = 0.016;
    inline constexpr double V_FINITE_ZERO_EV  = 11.384;
    inline constexpr double FIM_LAMBDA_MIN    = 7.38905609893065;
    inline constexpr double HESSIAN_KAPPA_MAX = 18.50;

    #pragma pack(push, 1)
    struct TorkyCellDtype {
        uint8_t  gov_gate;     // TSG Register (0x01 - 0x04)
        int16_t  phase_q16;    // Phase Q16 Fixed-Point
        int16_t  field_q16;    // Field Q16 Fixed-Point
        uint32_t syndrome_u32; // SHA-256 Merkle Syndrome
    };
    #pragma pack(pop)

    static_assert(sizeof(TorkyCellDtype) == 9, "CRITICAL: TorkyCellDtype must be precisely 9 bytes!");

    class NonSingularSimdKernel {
    public:
        static inline double evaluate_v_finite(double r_nm) {
            return 1.0 / std::sqrt((r_nm * r_nm) + EPSILON_NM2);
        }
    };

    class CardanoVieteSolver {
    public:
        static inline double solve_depressed_cubic(double p, double q) {
            double p_safe = std::min(-0.0001, p);
            double arg = (3.0 * q / (2.0 * p_safe)) * std::sqrt(-3.0 / p_safe);
            arg = std::max(-1.0, std::min(1.0, arg));
            return 2.0 * std::sqrt(-p_safe / 3.0) * std::cos(std::acos(arg) / 3.0);
        }
    };

} // namespace torky::sovereign::engine

#endif // TORKY_SOVEREIGN_GOVERNANCE_ENGINE_HPP
