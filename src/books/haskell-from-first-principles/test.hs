sayHello :: String -> IO ()
sayHello x = putStrLn ("Hello, " ++ x ++ "!")

triple :: Integer -> Integer
triple x = x * 3

half :: (Floating a) => a -> a
half x = x / 2

area :: (Floating a) => a -> a
area x = pi * (x * x)
