module MatrixMod where

tuples :: Int -> Int -> [[Int]]
tuples _ 0 = []
tuples items 1 = [[x] | x <- [0..items-1]]
tuples items len = [x : y | x <- [0..items-1], y <- tuples items (len-1)]

matrixRing :: Int -> Int -> [[Int]]
matrixRing modulus dim = tuples modulus (dim^2)
