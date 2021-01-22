//! Some linear algebra helpers.

/// Compute the ℓ₁-norm of the difference of two vectors `x` and `y`
/// ```
/// use graphidx::lina::l1_diff;
/// assert_eq!(l1_diff(&[1.0, -2.1], &[1.0, -2.1]), 0.0);
/// assert_eq!(l1_diff(&[1.0, -2.1], &[1.0, 1.0]), (-2.1 - 1.0_f64).abs());
/// ```
///
/// In case of different lengths, the function panics:
/// ```rust,should_panic
/// graphidx::lina::l1_diff(&[1.0], &[1.0, 2.0]);  // panic!(...)
/// ```
pub fn l1_diff<F>(x: &[F], y: &[F]) -> F
where
    F: std::ops::Sub<Output = F>
        + From<u8>
        + std::cmp::PartialOrd
        + std::ops::Neg<Output = F>
        + Copy,
{
    assert_eq!(x.len(), y.len());
    x.iter()
        .zip(y)
        .map(|(&x, &y)| {
            let d = x - y;
            if d < 0.into() {
                -d
            } else {
                d
            }
        })
        .fold(0.into(), |acc, a| if a < acc { acc } else { a })
}
