module MatrixRingMod where

import MatrixMod

data MatrixRingMod = MatrixRingMod { dim :: Int, modulus :: Int, matrices :: [MatrixMod] } 
  deriving (Show)

tuples :: Int -> Int -> [[Int]]
tuples 0 _ = []
tuples 1 items = [[x] | x <- [0..items-1]]
tuples len items = [x : y | x <- [0..items-1], y <- tuples (len-1) items]
  
entriesList :: Int -> Int -> [[Int]]
entriesList dim modulus = tuples (dim^2) modulus

createMatrixRingMod :: Int -> Int -> MatrixRingMod
createMatrixRingMod dim modulus = MatrixRingMod dim modulus matrices
  where matrices = map (createMatrixMod dim modulus) (entriesList dim modulus)

idempotents :: MatrixRingMod -> [MatrixMod]
idempotents ring = filter isIdempotent (matrices ring)

units :: MatrixRingMod -> [MatrixMod]
units ring = filter isUnit (matrices ring)
