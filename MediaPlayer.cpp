/*
 *Title: MediaPlayer.cpp
 *Author: Hamza Qureshi
 *Email: hamz1@umbc.edu
 *Description: Member function implementation for the MediaPlayer.h file for project 5 CMSC 202
 */

#include "MediaPlayer.h"

//Name: MediaPlayer - Default Constructor
//Precondition: None
//Postcondition: Creates a new MediaPlayer
MediaPlayer::MediaPlayer()
{
  
}

//Name: MediaPlayer - Overloaded Constructor
//Precondition: None
//Postcondition: Creates a new MediaPlayer and passes the media filename
MediaPlayer::MediaPlayer(string filename)
{
  LoadCatalog(filename);
}

//Name: ~MediaPlayer - Destructor
//Precondition: None
//Postcondition: Creates a new MediaPlayer
MediaPlayer::~MediaPlayer()
{
  //iterating through vector and deleting every dynamically allocated item
  for(unsigned int i = 0; i < m_mediaCatalog.size(); i++)
    {
      delete m_mediaCatalog.at(i);
    }
}

//Name: LoadCatalog(string filename)
//Precondition: Requires filename
//Postcondition: Loads the file into the m_mediaCatalog (as media)
void MediaPlayer::LoadCatalog(string filename)
{
  
  string line;
  int count = 0;
  ifstream myFile;
  //counting amount of items in the file
  myFile.open(filename);
  if(myFile.is_open())
    {
      while(getline(myFile, line))
	{
	  count += 1;
	}
    }
  myFile.close();
  //making vectors based on the amount of items loaded
  vector <string> title(count);
  vector <string> artist(count);
  vector <string> type(count);
  vector <string> str_year(count);
  vector <string> str_rank(count);

  vector <int> year(count);
  vector <int> rank(count);
  //inputing lines into respective vectors
  myFile.open(filename);
  if(myFile.is_open())
    {
      for(int i = 0; i < count; i++)
	{
	  getline(myFile, title.at(i), ';');
	  getline(myFile, artist.at(i), ';');
	  getline(myFile, type.at(i), ';');
	  getline(myFile, str_year.at(i), ';');
	  getline(myFile, str_rank.at(i));
	  //converting from string to int and adding to int vector 
	  year[i] = stoi(str_year.at(i));
	  rank[i] = stoi(str_rank.at(i));
	}
    }
  myFile.close();
 
  for(int i = 0; i < count; i++)
    {
      Media* newMedia = new Media(title.at(i), artist.at(i), type.at(i), year.at(i), rank.at(i));
      m_mediaCatalog.push_back(newMedia);
    }
  
  cout << count << " media files loaded" << endl;
}

//Name: MainMenu
//Precondition: None
//Postcondition: Manages the application and the menu
void MediaPlayer::MainMenu()
{
  int choice = 0;
  while (choice != 5) {
    do {
      cout << "What would you like to do?" << endl;
      cout << "1. Display Media by Type and Year" << endl;
      cout << "2. Add Media to Playlist" << endl;
      cout << "3. Display Playlist" << endl;
      cout << "4. Sort Playlist by Year" << endl;
      cout << "5. Quit" << endl; 
      cin >> choice;
      if(cin.fail()){
	cout << "Please enter 1 to 5" << endl;
	cin.clear();
	cin.ignore(256,'\n');
      }
    }while (choice < 1 && choice > 5) ;

    switch (choice) {
    case 1:
      cout << DisplayMedia() << " Media found." << endl;
      break;
    case 2:
      AddMedia();
      break;
    case 3:
      DisplayPlaylist();
      break;
    case 4:
      SortPlaylist();
      break;
    case 5:
      cout << "Thank you for using UMBC Media Player" << endl;
      //delete
    default:
      break;
    }
  }
}

//Name: DisplayMedia
//Precondition: User enters year (1958-2020)
//              (shows all years even if no media of that type exists for a particular year)
//Postcondition: Lists all media (numbered) for that year and returns int
//               of number found with that criteria
int MediaPlayer::DisplayMedia()
{
  string mchoice = "";
  int year_choice = 0;
  while(mchoice!="Music" and mchoice!="music" and mchoice!="Podcast" and mchoice!="podcast"){
    do {
      cout << "Which media type do you want to display?" << endl;
      cout << "music" << endl;
      cout << "podcast" << endl;
      cin >> mchoice;
      if(cin.fail()){
	cout << "Please enter music or podcast" << endl;
	cin.clear();
	cin.ignore(256,'\n');
      }
    }while(mchoice!="Music" and mchoice!="music" and mchoice!="Podcast" and mchoice!="podcast");
  }

    while(year_choice == 0){
      do {
	cout << "Which year would you like to display (1958-2020)?" << endl;
	cin >> year_choice;
	if(cin.fail()){
	  cout << "Please enter number between 1958-2020" << endl;
	  cin.clear();
	  cin.ignore(256,'\n');
	}	
      }while(year_choice < MIN_YEAR or year_choice > MAX_YEAR) ;
    }

    cout << "****** " << year_choice << " ******" << endl;
    cout << endl;

    int count = 0;
    //iterating through catalog and returning amount of media
    for(unsigned int i = 0; i < m_mediaCatalog.size(); i++)
      {
	if(m_mediaCatalog.at(i)->GetType() == mchoice)
	  {
	  if(m_mediaCatalog.at(i)->GetYear() == year_choice)
	      {
		cout << i+1  << ".  " <<
		  m_mediaCatalog.at(i)->GetTitle() << " by " <<
		  m_mediaCatalog.at(i)->GetArtist() << endl;
		count += 1;
	      }
	  }
      }
    return count;
}

//Name: AddMedia
//Precondition: m_mediaCatalog is populated
//Postcondition: Displays the current list and adds media
//               to the m_playList
void MediaPlayer::AddMedia()
{
  unsigned int number = 0;
    
  DisplayPlaylist();
  cout << "Choose the media you would like to add to the playlist" << endl;
  int amount = DisplayMedia();
  //amount is number of media in that year, if > 0 then can be added to playlist
  if(amount > 0)
    {
      cout << amount << " Media found." << endl;
      while(number == 0){
	do {
	  cout << "Enter the number of media you would like to add" << endl;
	  cin >> number;
	  if(cin.fail()){
	    cout << "Please enter number within range" << endl;
	    cin.clear();
	    cin.ignore(256,'\n');
	  }
	}while(number < 1 or number > m_mediaCatalog.size()) ;
      }
      //invoking copy constructor
      Media* copyMedia = m_mediaCatalog.at(number-1);
      m_playList.Enqueue(copyMedia);
      
      cout << m_mediaCatalog.at(number-1)->GetTitle() << " by "
	   << m_mediaCatalog.at(number-1)->GetArtist() << " added to the playlist" << endl;
    }
  else
    {
      cout << "No matching media with selected criteria" << endl;
    }
}
  
//Name: DisplayPlaylist
//Precondition: None (will indicate if list is empty)
//Postcondition: Displays the playlist
void MediaPlayer::DisplayPlaylist()
{
  if(m_playList.IsEmpty() == 1)
    {
      cout << "Playlist currently empty" << endl;
    }
  else
    {
      //iterating through playlist and dereferencing to access items 
      for(int i = 0; i < m_playList.Size(); i++)
	{
	  cout << i+1 << ". " << *m_playList.At(i) << endl; 
	}
    }
}

//Name: SortPlaylist
//Precondition: None (will indicate if list is empty)
//Postcondition: Sorts the playlist by year
void MediaPlayer::SortPlaylist()
{
  if(m_playList.IsEmpty() == 1)
    {
      cout << "Playlist is empty" << endl;
    }
  else
    {
      m_playList.Sort();
      cout << "Done sorting by year." << endl;
      cout << m_playList.Size() << " items sorted." << endl;
    }
}

