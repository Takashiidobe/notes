class Vehicle a where
  name :: a -> String
  destination :: a -> String
  speed :: a -> Int

data Ship = Ship {shipName :: String, shipDestination :: String, shipSpeed :: Int } deriving (Show)
data Car = Car {carName :: String, carDestination :: String, carSpeed :: Int } deriving (Show)

instance Vehicle Ship where
  name (Ship a _ _) = a
  destination (Ship _ b _) = b
  speed (Ship _ _ c) = c

instance Vehicle Car where
  name (Car a _ _) = a
  destination (Car _ b _) = b
  speed (Car _ _ c) = c

printName :: Vehicle a => a -> IO()
printName v = putStrLn("My name is: " ++ show (name v) ++ "\n")

printSpeed :: Vehicle a => a -> IO()
printSpeed s = putStrLn("My speed is: " ++ show (speed s) ++ "\n")

printLocation :: Vehicle a => a -> IO()
printLocation s = putStrLn("My final destination is: " ++ show (destination s) ++ "\n")

main = do
  let ship = Ship "SS Shipy" "London" 10
  let car = Car "Model S" "Iowa" 55
  printSpeed car
  printSpeed ship
  printLocation car
  printLocation ship
  printName car
  printName ship
