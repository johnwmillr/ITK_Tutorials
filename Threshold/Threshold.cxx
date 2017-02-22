// Threshold
//
// If you're looking to threshold an image, this code has you covered.

#include <iostream>

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argc[] )
{
	if (argc < 3)
	{
		std::cerr << "Not enough parameters " << std::endl;
		std::cerr << "Usage: " argv[0];
		return EXIT_FAILURE;
	}

	// typedef (these use templates)
	// e.g., RGPixel is a template and we're creating an instance of
	// that template w/ an unsigned char data type
	typedef itk::RGBPixel< unsigned char > RGBPixelType; // Declare our type of pixel
	typedef itk::Image< RGBPixelType, 2  > RGBImageType; // Declare our image, based on those pixels
	typedef itk::itkImageFileReader< RGBImageType > FileReaderType; // File reader
	typedef itk::itkImageFileWriter< RGBImageType > FileWriterType; // File writer

	// We need to be able to read a file in
	// I forget how this Pointer, New() syntax works
	FileReaderType::Pointer reader = FileReaderType::New();
	reader->SetFileName(argv[1]); // reader will use the first command line input

	// We need to be able to write a file out
	FileWriterType::Pointer writer = FileWriterType::New();
	writer->SetFileName(argv[2]); // output filename

	// Do the thresholding
	double threshold = argv[3];

	// Write the file
	// (not really sure how this code works)
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
} // End main
