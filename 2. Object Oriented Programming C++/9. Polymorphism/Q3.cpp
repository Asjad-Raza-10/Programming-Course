#include <iostream>

using namespace std;

class MediaFile
{
public:
	virtual void play() = 0;
};

class AudioFile :public MediaFile
{
private:
	static int count;
public:

	void play() override
	{
		cout << "Playing Audio Track" << endl;
		count++;
	}

	static int getCount()
	{
		return count;
	}
};

class VideoFile :public MediaFile
{
private:
	static int count;
public:

	void play() override
	{
		cout << "Playing Video Track" << endl;
		count++;
	}

	static int getCount()
	{
		return count;
	}
};

class TextFile :public MediaFile
{
private:
	static int count;
public:

	void play() override
	{
		cout << "Displaying Text Document" << endl;
		count++;
	}

	static int getCount()
	{
		return count;
	}

};

int AudioFile::count = 0;
int VideoFile::count = 0;
int TextFile::count = 0;

int main()
{
	MediaFile* pointer[5];
	pointer[0] = new AudioFile();
	pointer[1] = new AudioFile();
	pointer[2] = new VideoFile();
	pointer[3] = new TextFile();
	pointer[4] = new TextFile();

	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		pointer[i]->play();
	}

	cout << endl << "--- Play Count Summary ---" << endl;
	cout << "Audio Files Played: " << AudioFile::getCount() << endl;
	cout << "Video Files Played: " << VideoFile::getCount() << endl;
	cout << "Text Files Played: " << TextFile::getCount() << endl;

	for (int i = 0; i < 3; i++)
	{
		delete[]pointer[i];
	}


	return 0;
}