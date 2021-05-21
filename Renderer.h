#pragma once
#include "SFML/Graphics.hpp"
#include <cassert>
#include <string>
#include <iostream>
#include "Buns.h"


class StorageImagesForOneAnimation
{
	std::string nameAnimation;
	sf::Image* images;
	int numberOfImages;

public:

	StorageImagesForOneAnimation()
	{
		images = new sf::Image[1];
		nameAnimation = "NULL";
		numberOfImages = 0;
	}

	StorageImagesForOneAnimation(std::string nameAnimation, int numberOfImages, std::string* namesOfFiles)
	{
		this->numberOfImages = numberOfImages;
		this->nameAnimation = nameAnimation;
		images = new sf::Image[numberOfImages];
		sf::Image image;
		for (int i = 0; i < numberOfImages; i++)
		{
			image.loadFromFile(namesOfFiles[i].c_str());                                     
			sf::Vector2u size = image.getSize();
			int x = size.x;
			int y = size.y;
			images[i].create(x, y);
			images[i].copy(image, 0, 0);                                                                        
		}
	}

	StorageImagesForOneAnimation(const StorageImagesForOneAnimation& stImages)
	{
		nameAnimation = stImages.nameAnimation;
		delete[] images;
		numberOfImages = stImages.numberOfImages;
		images = new sf::Image[stImages.numberOfImages];
		for (int i = 0; i < stImages.numberOfImages; i++)
		{
			images[i] = stImages.images[i];
		}
	}

	~StorageImagesForOneAnimation()
	{
		delete[] images;
	}

	StorageImagesForOneAnimation& operator = (const StorageImagesForOneAnimation& stImages)
	{
		nameAnimation = stImages.nameAnimation;
		delete[] images;
		numberOfImages = stImages.numberOfImages;
		images = new sf::Image[stImages.numberOfImages];
		for (int i = 0; i < stImages.numberOfImages; i++)
		{
			images[i] = stImages.images[i];
		}

		return *this;
	}

	std::string getName()
	{
		return nameAnimation;
	}

	sf::Image* getImage(const int index)
	{
		assert(index < numberOfImages);
		return &images[index];
	}

	int getNumberOfImages()
	{
		return numberOfImages;
	}
};


class StorageImages          // What do we should to name it?
{
	int numberOfStorages;
	StorageImagesForOneAnimation* images;

public:

	sf::Image* getImage(std::string nameStorage, const int index)
	{
		for (int i = 0; i < numberOfStorages; i++)
		{
			if (images[i].getName() == nameStorage)
			{
				return images[i].getImage(index);
			}
		}
		std::cout << "There is no image with name : " << nameStorage << std::endl;
		assert(false);
	}

	StorageImages(StorageImagesForOneAnimation* images, int numberOfStorage)
	{
		this->images = new StorageImagesForOneAnimation[numberOfStorage];
		this->numberOfStorages = numberOfStorage;
		for (int i = 0; i < numberOfStorage; i++)
		{
			this->images[i] = images[i];
		}
	}

	StorageImages(std::string imagesName, std::string nameOfFile)
	{
		images = new StorageImagesForOneAnimation[1];
		numberOfStorages = 1;
		StorageImagesForOneAnimation image(imagesName, 1, &nameOfFile);
		images[0] = image;
	}

	~StorageImages()
	{
		delete[] images;
	}

	int getSizeStorage(std::string nameStorage)
	{
		for (int i = 0; i < numberOfStorages; i++)
		{
			if (images[i].getName() == nameStorage)
			{
				return images[i].getNumberOfImages();
			}
		}
		std::cout << "There is no image with name : " << nameStorage << std::endl;
		assert(false);
	}
};


class Renderer : public Component 
{
	StorageImages* storageImages;
	std::string nameCurrentImage;
	int indexCurrentImage;
	float timeFromLastChangeImage;
	float timeBeetweenImages;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f size;
	float characteristicSize;

	void changeTexture()
	{
		texture.loadFromImage(*(StorageImages->getImage(nameCurrentImage, indexCurrentImage)));
	}

	void setSize(sf::Vector2f size)
	{
		this->size = size;
		characteristicSize = max(size.x, size.y);
	}

	void setCurrentImageIndex(int index)
	{
		indexCurrentImage = index;
		sf::Image im = *(storageImages->getImage(nameCurrentImage, index));
	}

public:

	Renderer(StorageImages* storageImages, std::string nameFistStImages, sf::Vector2f size)
	{
		this->storageImages = storageImages;
		nameCurrentImage = nameFistStImages;
		indexCurrentImage = 0;

		texture.create(size.x, size.y);
		texture.update(*(storageImages->getImage(nameFistStImages, 0)));
		sprite.setTexture(texture);                                         //???? may no change texture sprite, then change it

		this->setSize(size);
	}

	void changeTexture(std::string nameStorage, const int index)
	{
		nameCurrentImage = nameStorage;
		indexCurrentImage = index;
		texture.loadFromImage(*(storageImages->getImage(nameStorage, index)));
	}

	void animation(float timeBeetweenFrame)
	{
		timeFromLastChangeImage += timeBeetweenFrame;
		if (timeFromLastChangeImage > timeBeetweenImages)
		{
			timeFromLastChangeImage = 0;
			if (storageImages->getSizeStorage(nameCurrentImage) - 1 <= indexCurrentImage)
				indexCurrentImage = -1;
			setCurrentImageIndex(indexCurrentImage + 1);
			this->changeTexture();
			return;
		}
	}

	sf::Sprite getSprite()
	{
		return sprite;
	}
};

/*
class Renderer : public Component {
public:
	Renderer()
	{
		//std::cout << "Renderer" << '\n';
		sprite = 9;
	}

	Renderer(Renderer& r)
	{
		//std::cout << "copyRenderer" << '\n';
		sprite = r.sprite;
	}

	Renderer& operator = (Renderer& r)
	{
		//std::cout << "=Renderer" << '\n';
		sprite = r.sprite;
		return *this;
	}

	int sprite;
};
*/