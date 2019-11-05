//! Weight parameters associated to a collection, e.g. nodes or edges.
//!
//! There are mainly to different kinds of weights:
//!
//! 1. [`ConstantWeights`] provides the same weight for every element.
//!
//! 2. [`ArrayWeights`] provides access to a weight stored in a vector.
//!
//! Both classes provide access by index notation.
//!
//! [`ConstantWeights`]: struct.ConstantWeights.html
//! [`ArrayWeights`]: struct.ConstantWeights.html
use std::ops::Index;
// use num_traits::identities::{One, one};

pub trait Weighted<T>: Index<usize, Output = T> {
    fn len(&self) -> usize;
}

/// Weight 1.0 for every element
#[derive(PartialEq, Debug)]
pub struct UnitWeights<T> {
    _c: std::marker::PhantomData<T>,
}

impl Weighted<f64> for UnitWeights<f64> {
    fn len(&self) -> usize {
        std::usize::MAX
    }
}

impl Index<usize> for UnitWeights<f64> {
    type Output = f64;
    fn index(&self, _i: usize) -> &Self::Output {
        &1f64
    }
}

impl Weighted<f32> for UnitWeights<f32> {
    fn len(&self) -> usize {
        std::usize::MAX
    }
}

impl Index<usize> for UnitWeights<f32> {
    type Output = f32;
    fn index(&self, _i: usize) -> &Self::Output {
        &1f32
    }
}

impl<T> UnitWeights<T> {
    pub fn new() -> Self {
        UnitWeights {
            _c: Default::default(),
        }
    }
}

/// Same weight for every element.
#[derive(PartialEq, Debug)]
pub struct ConstantWeights<T> {
    c: T,
}

impl<T> Index<usize> for ConstantWeights<T> {
    type Output = T;
    fn index(&self, _i: usize) -> &Self::Output {
        &self.c
    }
}

impl<T> Weighted<T> for ConstantWeights<T> {
    fn len(&self) -> usize {
        std::usize::MAX
    }
}

impl<T> ConstantWeights<T> {
    pub fn new(c: T) -> Self {
        ConstantWeights { c: c }
    }
}

/// Weights stored in an array.
#[derive(PartialEq, Debug)]
pub struct ArrayWeights<T> {
    a: Vec<T>,
}

impl<T> Index<usize> for ArrayWeights<T> {
    type Output = T;
    fn index(&self, i: usize) -> &Self::Output {
        &self.a[i]
    }
}

impl<T> Weighted<T> for ArrayWeights<T> {
    fn len(&self) -> usize {
        self.a.len()
    }
}

impl<T> ArrayWeights<T> {
    pub fn new(a: Vec<T>) -> Self {
        ArrayWeights { a: a }
    }
}

#[cfg(test)]
mod tests {
    use super::{ArrayWeights, ConstantWeights, UnitWeights};

    #[test]
    fn constant_weights_13() {
        let w = ConstantWeights::new(13.5);
        assert_eq!(w[5], 13.5);
        assert_eq!(w[0], 13.5);
        assert_eq!(w[13], 13.5);
    }

    #[test]
    fn unit_weights_13() {
        let w = UnitWeights::<f64>::new();
        assert_eq!(w[5], 1.0);
        assert_eq!(w[0], 1.0);
        assert_eq!(w[13], 1.0);
    }

    #[test]
    fn array_weights_123() {
        let w = ArrayWeights::new(vec![1, 2, 5]);
        assert_eq!(w[2], 5);
        assert_eq!(w[0], 1);
        assert_eq!(w[1], 2);
        let result = std::panic::catch_unwind(|| w[3]);
        assert!(result.is_err());
    }
}
