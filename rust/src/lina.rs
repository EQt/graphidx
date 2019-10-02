//! Some linear algebra helpers.

/// Compute the ℓ₁-norm of the difference of two vectors `x` and `y`
/// ```
/// use graphidx::lina::l1_diff;
/// assert!(l1_diff(&[1.0], &[1.0, 2.0]).is_nan());  // different lengths
/// assert_eq!(l1_diff(&[1.0, -2.1], &[1.0, -2.1]), 0.0);
/// assert_eq!(l1_diff(&[1.0, -2.1], &[1.0, 1.0]), (-2.1 - 1.0_f64).abs());
/// ```
pub fn l1_diff(x: &[f64], y: &[f64]) -> f64 {
    if x.len() != y.len() {
        std::f64::NAN
    } else {
        x.iter()
            .zip(y)
            .map(|(x, y)| (x - y).abs())
            .fold(std::f64::NEG_INFINITY, |acc, a| acc.max(a))
    }
}
