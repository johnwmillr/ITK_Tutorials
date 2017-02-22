// ReadImage.cxx
//
// If you're looking to read in an image, this code has you covered.
//
#include <iostream>

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{
  if (argc < 2 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];    
    return EXIT_FAILURE;
    }
  
  
  // Do some type declarations (these are templates)
  typedef itk::RGBPixel< unsigned char >  RGBPixelType;
  typedef itk::Image< RGBPixelType, 2  >  RGBImageType;    
  typedef itk::ImageFileReader< RGBImageType > FileReaderType;  
  typedef itk::ImageFileWriter< RGBImageType > FileWriterType;

  // Create an instance of the file reader class (?) and set the filename
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName(argv[1]);

  // Set up the file writer and specify file save name
  FileWriterType::Pointer writer = FileWriterType::New();
  writer->SetFileName(argv[2]);  
  
  // Not sure what's happening here  
  writer->SetInput(reader->GetOutput());

  try
    {
    writer->Update();
    }
  catch (itk::ExceptionObject &e)
    {
    std::cerr << e << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
