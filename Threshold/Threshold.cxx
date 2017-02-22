// Threshold
//
// If you're looking to threshold an image, this code has you covered.

#include <iostream>

#include "itkBinaryThresholdImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{
  if (argc < 5 )
    {
	    std::cerr << "Not enough parameters " << std::endl;
	    std::cerr << "Usage: " << argv[0];    
	    return EXIT_FAILURE;
    }

	// typedef (these use templates)
	// e.g., RGPixel is a template and we're creating an instance of
	// that template w/ an unsigned char data type
	typedef unsigned char PixelType;
	// typedef itk::RGBPixel< unsigned char > PixelType; // Declare our type of pixel
	typedef itk::Image< PixelType, 2  > ImageType; // Declare our image, based on those pixels	
	

	// We need to be able to read a file in
	// I forget how this Pointer, New() syntax works
	typedef itk::ImageFileReader< ImageType > FileReaderType; // File reader	
	FileReaderType::Pointer reader = FileReaderType::New();
	reader->SetFileName(argv[1]); // reader will use the first command line input

	// -----------------------------------------------------------------
	// Create the thresholding filter
	// Declare the filter
	typedef itk::BinaryThresholdImageFilter< ImageType, ImageType> FilterType;

	// We need to convert the command line arguments to numbers first
	const PixelType lowerThreshold = static_cast<PixelType>(atoi( argv[3]));
	const PixelType upperThreshold = static_cast<PixelType>(atoi( argv[4]));
	const PixelType minVal = 0;
	const PixelType maxVal = 1;

	// Send the lower/upper threshold values into the filter
	filter->SetLowerThreshold(lowerThreshold);
	filter->SetUpperThreshold(upperThreshold);

	// These min/max values determine the resulting pixel values of
	// the thresholded image
	filter->SetOutsideValue(minVal);
	filter->SetInsideValue( maxVal);

	// Update the filter
	filter->Update();
	
	// Apply the filter
	filter->SetInput(reader->GetOutput()));
	
	// -----------------------------------------------------------------
	// Write the file
	// (not really sure how this code works)
	// We need to be able to write a file out
	typedef itk::ImageFileWriter< ImageType > FileWriterType; // File writer	    	 
	FileWriterType::Pointer writer = FileWriterType::New();
	writer->SetFileName(argv[2]); // output filename

	// I guess the arrow is "member selection"
	// http://www.learncpp.com/cpp-tutorial/612-member-selection-with-pointers-and-references/
	// So, we need to use the -> syntax b/c "reader" is a pointer.

	// Send the output of the filter into the writer	
	writer->SetInput(filter->GetOutput());	

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
