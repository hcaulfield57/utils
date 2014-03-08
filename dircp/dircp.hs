module Main (main) where

import Control.Monad (when)
import Control.Monad.Reader
import System.Console.GetOpt
import System.Directory
import System.Environment
import System.Exit
import System.IO

data Flag = Parents | Verbose
    deriving Eq

flags :: [OptDescr Flag]
flags = [Option "p" [] (NoArg Parents) [],
         Option "v" [] (NoArg Verbose) []]

dircp :: (String,String) -> ReaderT [Flag] IO ()
dircp (src,dst) = do
    flg <- ask
    srcExists <- lift $ doesDirectoryExist src
    dstExists <- lift $ doesDirectoryExist dst
    let parents = elem Parents flg
        verbose = elem Verbose flg
    if not srcExists 
        then lift usage
        else if not dstExists && parents
             then lift (createDirectory dst)
                >> lift (cp verbose src dst)
             else if dstExists
                  then lift $ cp verbose src dst
                  else lift usage

cp :: Bool -> FilePath -> FilePath -> IO ()
cp v src dst = do
    contents <- getDirectoryContents src
    let dot = filter (`notElem`[".",".."]) contents
    mapM_ cp' dot
    where cp' fp = do
            let src' = src ++ "/" ++ fp
                dst' = dst ++ "/" ++ fp
            copyFile src' dst'
            when v $ putStrLn $ "dircp: " ++ src' ++ " --> " ++ dst'

main :: IO ()
main = do
    argv <- getArgs
    let (opts,files,_) = getOpt RequireOrder flags argv
    case files of
        (src:dst:[]) -> runReaderT (dircp (src,dst)) opts
        _ -> usage

usage :: IO ()
usage = hPutStrLn stderr "usage dircp [-pv] src dst"
    >> exitWith (ExitFailure 1)
