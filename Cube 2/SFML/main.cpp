#include "stdafx.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

bool computePixelCoordinates(
	const sf::Vector3f &pWorld,
	const float cameraToWorld[4][4],
	const float &canvasWidth,
	const float &canvasHeight,
	const int &imageWidth,
	const int &imageHeight,
	sf::Vector2i &pRaster)
{
	// First transform the 3D point from world space to camera space. 
	// It is of course inefficient to compute the inverse of the cameraToWorld
	// matrix in this function. It should be done outside the function, only once
	// and the worldToCamera should be passed to the function instead. 
	// We are only compute the inverse of this matrix in this function ...
	sf::Vector3f pCamera;
	float worldToCamera[4][4] = cameraToWorld.inverse();
	worldToCamera.multVecMatrix(pWorld, pCamera);
	// Coordinates of the point on the canvas. Use perspective projection.
	sf::Vector2f pScreen;
	pScreen.x = pCamera.x / -pCamera.z;
	pScreen.y = pCamera.y / -pCamera.z;
	// If the x- or y-coordinate absolute value is greater than the canvas width 
	// or height respectively, the point is not visible
	if (std::abs(pScreen.x) > canvasWidth || std::abs(pScreen.y) > canvasHeight)
		return false;
	// Normalize. Coordinates will be in the range [0,1]
	sf::Vector2f pNDC;
	pNDC.x = (pScreen.x + canvasWidth / 2) / canvasWidth;
	pNDC.y = (pScreen.y + canvasHeight / 2) / canvasHeight;
	// Finally convert to pixel coordinates. Don't forget to invert the y coordinate
	pRaster.x = std::floor(pNDC.x * imageWidth);
	pRaster.y = std::floor((1 - pNDC.y) * imageHeight);

	return true;
}

int main()
{
	float cameraToWorld[4][4];
	sf::Vector3f pWorld;
	float canvasWidth = 2, canvasHeight = 2;
	uint32_t imageWidth = 512, imageHeight = 512;
	// The 2D pixel coordinates of pWorld in the image if the point is visible
	sf::Vector2i pRaster;
	if (computePixelCoordinates(pWorld, cameraToWorld, canvasWidth, canvasHeight, imageWidth, imageHeight, pRaster)) {
		cout << "Pixel coordinates " << pRaster.x << "," << pRaster.y << endl;
	}
	else {
		cout << pWorld.x << "," << pWorld.y << "," << pWorld.z << " is not visible" << std::endl;
	}
	return 0;
}