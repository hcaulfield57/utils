module Main where

import Data.List (isPrefixOf)
import Data.Maybe (fromMaybe)
import System.Directory
import System.Environment
import System.Exit
import System.IO
import System.IO.Error

countMsg :: String -> Int
countMsg input
    | "From " `isPrefixOf` input = 1
    | otherwise                  = 0

main :: IO ()
main = do
    argv <- getArgs
    mail <- lookupEnv "MAIL"
    let mail' = fromMaybe "" mail
        spool = case argv of
            ("-s":sf:_) -> sf
            _           -> mail'
    results <- tryIOError $ readFile spool
    case results of
        Left err       -> print 0
        Right contents -> print $ 
            sum $ map countMsg (lines contents)

usage :: IO ()
usage =
    putStrLn "usage: newmail [-s spool]" >>
    exitWith (ExitFailure 1)
