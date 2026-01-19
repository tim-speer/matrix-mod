module MatrixMod where

import IntMod hiding (modulus)

data MatrixMod = MatrixMod { dim :: Int, modulus :: Int, entries :: [IntMod] }
  deriving (Show, Eq)

createMatrixMod :: Int -> Int -> [Int] -> MatrixMod
createMatrixMod dim modulus entries
  | dim >= 1 && 
    modulus >= 2 &&
    length entries == dim^2 = MatrixMod dim modulus (map convert entries) 
  where convert = (\v -> createIntMod v modulus)

addMatrixMod :: MatrixMod -> MatrixMod -> MatrixMod
addMatrixMod left right
  | dim m1 == dim m2 &&
    modulus m1 == modulus m2 = MatrixMod (dim m1) (modulus m1) (zipWith (addIntMod) (entries m1) (entries m2)) 
  where m1 = ensureValidMatrix left 
        m2 = ensureValidMatrix right

mulMatrixMod :: MatrixMod -> MatrixMod -> MatrixMod
mulMatrixMod left right
  | dim m1 == dim m2 &&
    modulus m1 == modulus m2 = 
  createMatrixMod (dim m1) 
                  (modulus m1) 
                  [innerProduct (row i m1) (column j m2) | i <- [0..dim m1 - 1], j <- [0..dim m1 - 1]]
  where m1 = ensureValidMatrix left 
        m2 = ensureValidMatrix right
        xs = map modToInt (entries m1)
        ys = map modToInt (entries m2)

row :: Int -> MatrixMod -> [Int]
row i (MatrixMod dim _ entries) =
  take dim (drop (i*dim) (map modToInt entries)) 
  
column :: Int -> MatrixMod -> [Int]
column i (MatrixMod dim _ entries) =
 [es !! k | k <- [i, i + dim..(i + dim)*(dim-1)]]
 where es = map modToInt entries 

modToInt :: IntMod -> Int
modToInt (IntMod v _) = v

ensureValidMatrix :: MatrixMod -> MatrixMod
ensureValidMatrix matrix = 
  createMatrixMod (dim matrix) (modulus matrix) (map modToInt (entries matrix))

innerProduct :: [Int] -> [Int] -> Int
innerProduct xs ys 
  | length xs == length ys = sum (zipWith (*) xs ys)

squareMatrixMod :: MatrixMod -> MatrixMod
squareMatrixMod matrix = mulMatrixMod matrix matrix

isIdempotent :: MatrixMod -> Bool
isIdempotent matrix = squareMatrixMod matrix == matrix

subMatrix :: MatrixMod -> Int -> Int -> MatrixMod
subMatrix (MatrixMod dim modulus entries) i j = MatrixMod (dim-1) modulus (subMatrix' 0 dim entries i j)
  
subMatrix' :: Int -> Int -> [IntMod] -> Int -> Int -> [IntMod]
subMatrix' _ _ [] _ _  = []
subMatrix' index dim (e:es) i j =
  if row == i || column == j then
    subMatrix' (index+1) dim es i j 
  else
    e : subMatrix' (index+1) dim es i j
  where row = div index dim 
        column = mod index dim  

determinant :: MatrixMod -> IntMod
determinant matrix 
  | d == 1 = es !! 0
  | d > 1 = foldr addIntMod (createIntMod 0 m) summands 
  where d = dim matrix
        es = entries matrix
        m = modulus matrix  
        subMatrices = map (subMatrix matrix 0) [0..d-1]  
        minors = map determinant subMatrices
        signs = map ((-1)^) [0..d-1]
        signsMod = [createIntMod v m | v <- signs]
        cofactors = zipWith mulIntMod signsMod minors
        summands = zipWith mulIntMod [IntMod v m | v <- (row 0 matrix)] cofactors
