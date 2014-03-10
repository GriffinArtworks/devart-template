#pragma once

#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

/*
 * Google custom search parameters
 * https://developers.google.com/custom-search/json-api/v1/reference/cse/list#response
 */
class ImageSearchDefinition
{
public:
	string query; // keyword, eg. "abstract art"
	
};

/*
 * class responsible for loading images found using google custom search API
 * once loaded, caches them to local storage.
 */
class ColourMapManager{
public:
	ofxThreadedImageLoader loader;
	vector<ofImage> images;
	int total;

	void doImageSearch(ImageSearchDefinition &def)
	{

	}



	// load images based on a google custom search
	void loadImages(ImageSearchDefinition &def);
};
