/*
 *Title: Media.cpp
 *Author: Hamza Qureshi
 *Email: hamz1@umbc.edu
 *Description: Member function implementation for the Media.h file for project 5 CMSC 202
 */

#include "Media.h"

//Name: Media - Default Constructor
//Precondition: None
//Postcondition: Creates a default media
Media::Media()
{

}

//Name: Media - Overloaded Constructor
//Precondition: Requires title, artist, type, year and rank
//Postcondition: Creates a media entry based on passed parameters
Media::Media(string title, string artist, string type, int year, int rank )
{
  m_title = title;
  m_artist = artist;
  m_type = type;
  m_year = year;
  m_rank = rank;
}

//Name: Mutators and Accessors
//Precondition: None
//Postcondition: Sets and Gets private member variables
string Media::GetTitle()const
{
  return m_title;
}

string Media::GetArtist()const
{
  return m_artist;
}

string Media::GetType()const
{
  return m_type;
}

int Media::GetYear()const
{
  return m_year;
}

int Media::GetRank()const
{
  return m_rank;
}

void Media::SetTitle(string title)
{
  m_title = title;
}

void Media::SetArtist(string artist)
{
  m_artist = artist;
}

void Media::SetType(string type)
{
  m_type = type;
}

void Media::SetYear(int year)
{
  m_year = year;
}

void Media::SetRank(int rank)
{
  m_rank = rank;
}

//Name: Overloaded << operator
//Precondition: media available
//Postcondition: Returns output stream including title by artist from year
ostream& operator<<(ostream& out, Media& m)
{
  //creating output stream and returning it 
  out << m.m_title << " by " << m.m_artist << " from " << m.m_year << endl;
  return out;
}

//Name: Overloaded Relational Operator (<)
//Precondition: Two media objects required
//Postcondition: if passed media's year is less than first, return true else false
bool Media::operator<(const Media& m)
{
  if(m.m_year < m_year)
    {
      return true;
    }
  else
    {
      return false;
    }
}

