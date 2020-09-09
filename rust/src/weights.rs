//! Weight parameters associated to a collection, e.g. nodes or edges.
//!
//! There are different kinds of weights:
//! 0. [`Ones`] provide weight `1.0` for every element.
//!
//! 1. [`Const`] provides the same, i.e. constant weight for every element.
//!
//! 2. [`Array`] provides access to a weight stored in a vector.
//!
//! Both classes provide access by index notation.
//!
//! [`Const`]: struct.Const.html
//! [`Array`]: struct.Array.html
use std::ops::Index;
// use num_traits::identities::{One, one};

#[allow(clippy::len_without_is_empty)]
pub trait Weighted<T>: Index<usize, Output = T> {
    fn len(&self) -> usize;
    fn is_const() -> bool;
}

/// Weight 1.0 for every element
#[derive(PartialEq, Debug)]
pub struct Ones<T> {
    _c: std::marker::PhantomData<T>,
}

impl Weighted<f64> for Ones<f64> {
    fn len(&self) -> usize {
        std::usize::MAX
    }

    fn is_const() -> bool {
        true
    }
}

impl Index<usize> for Ones<f64> {
    type Output = f64;
    fn index(&self, _i: usize) -> &Self::Output {
        &1f64
    }
}

impl Weighted<f32> for Ones<f32> {
    fn len(&self) -> usize {
        std::usize::MAX
    }

    fn is_const() -> bool {
        true
    }
}

impl Index<usize> for Ones<f32> {
    type Output = f32;
    fn index(&self, _i: usize) -> &Self::Output {
        &1f32
    }
}

impl<T> Default for Ones<T> {
    fn default() -> Ones<T> {
        Ones {
            _c: Default::default(),
        }
    }
}

impl<T> Ones<T> {
    pub fn new() -> Self {
        Self::default()
    }
}

/// Same weight for every element.
#[derive(PartialEq, Debug)]
pub struct Const<T> {
    c: T,
}

impl<T> Index<usize> for Const<T> {
    type Output = T;
    fn index(&self, _i: usize) -> &Self::Output {
        &self.c
    }
}

impl<T> Weighted<T> for Const<T> {
    fn len(&self) -> usize {
        std::usize::MAX
    }

    fn is_const() -> bool {
        true
    }
}

impl<T> Const<T> {
    pub fn new(c: T) -> Self {
        Const { c }
    }
}

impl<T> From<T> for Const<T> {
    fn from(c: T) -> Const<T> {
        Const::new(c)
    }
}

impl<T: Clone> From<&T> for Const<T> {
    fn from(c: &T) -> Const<T> {
        Const::new(c.clone())
    }
}

/// Weights stored in a `Vec`tor.
#[derive(PartialEq, Debug)]
pub struct Array<T> {
    a: Vec<T>,
}

impl<T> Index<usize> for Array<T> {
    type Output = T;
    fn index(&self, i: usize) -> &Self::Output {
        &self.a[i]
    }
}

impl<T> Weighted<T> for Array<T> {
    fn len(&self) -> usize {
        self.a.len()
    }

    fn is_const() -> bool {
        false
    }
}

impl<T> Array<T> {
    pub fn new(a: Vec<T>) -> Self {
        Array { a }
    }
}

impl<T> From<Vec<T>> for Array<T> {
    fn from(c: Vec<T>) -> Self {
        Self::new(c)
    }
}

/// Weights stored in a referenced `Vec`tor.
#[derive(PartialEq, Debug)]
pub struct ArrayRef<'a, T> {
    a: &'a [T],
}

impl<'a, T> Index<usize> for ArrayRef<'a, T> {
    type Output = T;
    fn index(&self, i: usize) -> &Self::Output {
        &self.a[i]
    }
}

impl<'a, T> Weighted<T> for ArrayRef<'a, T> {
    fn len(&self) -> usize {
        self.a.len()
    }

    fn is_const() -> bool {
        false
    }
}

impl<'a, T> ArrayRef<'a, T> {
    pub fn new(a: &'a [T]) -> Self {
        ArrayRef { a }
    }
}

impl<'a, T> From<&'a [T]> for ArrayRef<'a, T> {
    fn from(c: &'a [T]) -> Self {
        Self::new(c)
    }
}

impl<'a, T> From<&'a Vec<T>> for ArrayRef<'a, T> {
    fn from(c: &'a Vec<T>) -> Self {
        c[..].into()
    }
}

#[cfg(test)]
mod tests {
    use super::{Array, ArrayRef, Const, Ones};

    #[test]
    fn constant_weights_13() {
        let w = Const::new(13.5);
        assert_eq!(w[5], 13.5);
        assert_eq!(w[0], 13.5);
        assert_eq!(w[13], 13.5);
    }

    #[test]
    fn const_from() {
        assert_eq!(Const::new(42), 42.into());
        assert_eq!(Const::new(42.1), 42.1.into());
    }

    #[test]
    fn array_from() {
        let vals = vec![1, 2, 5];
        let weights: Array<_> = vals.clone().into();
        assert_eq!(weights, Array::new(vals));
    }

    #[test]
    fn arrayref_from() {
        let vals: [u8; 3] = [1, 2, 5];
        let weights: ArrayRef<_> = vals[..].into();
        assert_eq!(weights, ArrayRef::new(&vals));
    }

    #[test]
    fn unit_weights_13() {
        let w = Ones::<f64>::new();
        assert_eq!(w[5], 1.0);
        assert_eq!(w[0], 1.0);
        assert_eq!(w[13], 1.0);
    }

    #[test]
    fn array_weights_123() {
        let w = Array::new(vec![1, 2, 5]);
        assert_eq!(w[2], 5);
        assert_eq!(w[0], 1);
        assert_eq!(w[1], 2);
        let result = std::panic::catch_unwind(|| w[3]);
        assert!(result.is_err());
    }

    #[test]
    fn arrayref_weights_123() {
        let v = vec![1, 2, 5];
        let w = ArrayRef::new(&v);
        assert_eq!(w[2], 5);
        assert_eq!(w[0], 1);
        assert_eq!(w[1], 2);
        let result = std::panic::catch_unwind(|| w[3]);
        assert!(result.is_err());
    }
}
