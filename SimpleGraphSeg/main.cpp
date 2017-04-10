// Main file for the SimpleGraphSeg project, meant to test out the graph segmentation library

//#include "stdafx.h"
#include <iostream>
#include "itkCastImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h" // For saving a copy of the image
#include <vector>

template <class ImageType>
int writeOutputImage2D(typename ImageType::Pointer inputImage)
{	
	typedef unsigned char WritePixelType;
	typedef itk::Image<WritePixelType, 2> WriteImageType;

	typedef itk::RescaleIntensityImageFilter<ImageType, WriteImageType> RescaleFilterType;

	typename RescaleFilterType::Pointer rescaler = RescaleFilterType::New();

	const unsigned char min(0);
	const unsigned char max(255);
	
	rescaler->SetOutputMinimum(min);
	rescaler->SetOutputMaximum(max);	
	typedef itk::ImageFileWriter<WriteImageType> WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName("output.png");
	
	rescaler->SetInput(inputImage);
	writer->SetInput(rescaler->GetOutput());		
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

int main(int argc, char** argv)
{
	// Must supply the name of the image we're going to segment
	if(argc != 2){
		std::cout << "Executable takes one input.\nUSAGE: <File to segment>" << std::endl;
		return EXIT_FAILURE;
	}

	// Read the image
	typedef itk::Image<double, 2> ImageType; // 2D image
	typedef itk::ImageFileReader<ImageType> ReaderType;
	std::cout << "Attempting to read the image..." << std::endl;
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);
	reader->Update();	
	ImageType::Pointer image = reader->GetOutput();
	std::cout << "WE READ THE IMAGE!!!!" << std::endl;		
	
	// Save a copy of the image
	std::cout << "Attempting to write image..." << std::endl;	
	writeOutputImage2D<ImageType>(image);

	return EXIT_SUCCESS;
} // End main