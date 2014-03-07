import Control.Monad.Writer
import Data.List
import System.Directory
import System.Environment
import System.Exit
import System.IO

count :: Handle -> WriterT (Sum Int) IO ()
count h = do
    line <- lift $ hGetLine h
    eof <- lift $ hIsEOF h
    if eof then return ()
        else if isPrefixOf "From " line 
            then tell (Sum 1) >> count h
            else count h

main :: IO ()
main = do
    argv <- getArgs
    m <- lookupEnv "MAIL"
    let mail = case m of
            Just str -> str
            Nothing -> ""
    let spool = case argv of
            ("-s":sf:_) -> sf
            _ -> mail
    isFile <- doesFileExist spool
    if isFile then do
        handle <- openFile spool ReadMode
        num <- execWriterT (count handle)
        print $ getSum num
        else usage

usage :: IO ()
usage = putStrLn "usage: newmail [-s spool]"
    >> exitWith (ExitFailure 1)
