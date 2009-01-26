{-# LANGUAGE ForeignFunctionInterface #-}
module Test where

import Data.ByteString.Char8
import Foreign
import Foreign.Ptr
import Foreign.StablePtr
import Foreign.ForeignPtr
import Foreign.C.Types
import Foreign.C.String

newtype FImage = FImage (Ptr FImage)
type Image = (ForeignPtr FImage)

data Window = Window {
      name :: String
}

-- ADD SAFETY
loadImage :: String -> IO Image
loadImage filename =
    useAsCString (pack filename) $ \cfname -> do
      imgPtr <- c_cvLoadImage cfname
      image  <- newForeignPtr (unsafePerformIO $ mkRelease releaseImage) imgPtr
      return image

foreign import ccall "wrapper"
        mkRelease :: ((Ptr FImage) -> IO ()) -> 
                     IO (FunPtr ((Ptr FImage) -> IO ()))

releaseImage :: (Ptr FImage) -> IO ()
releaseImage imgPtr = do
    imgPtrPtr <- newStablePtr imgPtr
    c_cvReleaseImage $ castPtr $ castStablePtrToPtr imgPtrPtr

foreign import ccall "cv.h cvLoadImage"
        c_cvLoadImage :: CString -> IO (Ptr FImage)
foreign import ccall "cv.h cvReleaseImage"
        c_cvReleaseImage :: (Ptr (Ptr FImage)) -> IO ()
foreign import ccall "cv.h cvNamedWindow"
        c_cvNamedWindow :: CString -> IO CInt
foreign import ccall "cv.h cvShowImage"
        c_cvShowImage :: CString -> (Ptr FImage) -> IO ()
foreign import ccall "cv.h cvWaitKey"
        c_cvWaitKey :: CInt -> IO CInt

-- test code
testDisplayImage image = 
    useAsCString (pack "display") $ \cname -> 
        withForeignPtr image $ \imgPtr -> do
            c_cvNamedWindow cname
            c_cvShowImage cname imgPtr
            c_cvWaitKey 0