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

pub trait Weighted<T>: Index<usize, Output = T> {
    fn len(&self) -> usize;
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
}

impl Index<usize> for Ones<f32> {
    type Output = f32;
    fn index(&self, _i: usize) -> &Self::Output {
        &1f32
    }
}

impl<T> Ones<T> {
    pub fn new() -> Self {
        Ones {
            _c: Default::default(),
        }
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
}

impl<T> Const<T> {
    pub fn new(c: T) -> Self {
        Const { c: c }
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
}

impl<T> Array<T> {
    pub fn new(a: Vec<T>) -> Self {
        Array { a: a }
    }
}


/// Weights stored in a referenced `Vec`tor.
#[derive(PartialEq, Debug)]
pub struct ArrayRef<'a, T> {
    a: &'a Vec<T>,
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
}

impl<'a, T> ArrayRef<'a, T> {
    pub fn new(a: &'a Vec<T>) -> Self {
        ArrayRef { a: a }
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
